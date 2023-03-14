#include <stdio.h>
#include <math.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/float32.h>
#include <std_msgs/msg/int32.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "tusb.h" 
#include "pico/multicore.h"

/* DEFINE */
#define PI 3.14159265
     
#define IN_1 7
#define IN_2 9          
#define IN_3 10                
#define ENA 6
#define ENB 8
#define ENC 11   

#define G_1_OPEN 12
#define G_1_CLOSE 13
#define G_2_OPEN 15
#define G_2_CLOSE 14

#define gripper1_close_limit 19
#define gripper1_open_limit 18
#define gripper2_close_limit 17
#define gripper2_open_limit 16

//uart pins for tf mini s 
#define UART0_TX_PIN 0
#define UART0_RX_PIN 1 
#define UART1_TX_PIN 4 
#define UART1_RX_PIN 5

#define UART_ID0 uart0
#define BAUD_RATE 115200
#define UART_ID1 uart1

/* Configurations */
int PWM_MIN = 10;
int PWMRANGE = 65025;
int min_speed = 1;
int max_speed = 25;

const uint LED_PIN = 25;

uint32_t u1Pwm, u2Pwm, u3Pwm;

/* Robots Params */
float wheel_radius = 0.1;
float d = 0.36;

/* Define Sub Pub */
rcl_subscription_t r2_cmd_vel_subscriber;
geometry_msgs__msg__Twist r2_cmd_vel_msg;
char cmd_vel_subscriber_name[] = "robot_2/cmd_vel";

rcl_subscription_t gripper_sub;
std_msgs__msg__Int32 gripper_msg;
char r2_gripper_subscriber_name[] = "robot_2_gripper";

rcl_publisher_t tf_mini_1_pub;
std_msgs__msg__Float32 tf_mini_msg_1;
char tf_mini_1_pub_name[] = "r2_tf_mini_s1";

rcl_publisher_t tf_mini_2_pub;
std_msgs__msg__Float32 tf_mini_msg_2;
char tf_mini_2_pub_name[] = "r2_tf_mini_s2";

//****************************Structure and Union for handling LiDAR Data***********

//Dist_L Dist_H Strength_L Strength_H Temp_L Temp_H Checksum
typedef struct{
unsigned short Header;
unsigned short Dist;
unsigned short Strength;
}structLidar;

union unionLidar{
unsigned char Byte[9];
structLidar lidar;
};

unsigned char lidarCounter=0;

union unionLidar Lidar_1;
union unionLidar Lidar_2;

//****************************Function to read serial data***********

int isLidar(uart_inst_t * uart, union unionLidar * lidar)
{
  int loop;
  int checksum;
  unsigned char serialChar;

  while(uart_is_readable(uart))
  {
   if(lidarCounter > 8)
    {
      lidarCounter=0;
      return 0; // something wrong
    }

   serialChar = uart_getc(uart); // Read a single character to UART.
   lidar->Byte[lidarCounter]= serialChar;

   switch(lidarCounter++)
   {
    case 0:
    case 1:
    	   if(serialChar !=0x59)
              lidarCounter=0;
           break;
    case 8: // checksum
            checksum=0;
            lidarCounter=0;
            for(loop=0;loop<8;loop++)
                checksum+= lidar->Byte[loop];
            if((checksum &0xff) == serialChar)
                {   
                  lidar->lidar.Dist = lidar->Byte[2] | lidar->Byte[3] << 8;
                  lidar->lidar.Strength = lidar->Byte[4] | lidar->Byte[5] << 8;
                  return 1;
                }
    }
   }
    return 0;
}

/* Publisher Callbacks */
void tf_mini_1_Cb(rcl_timer_t * timer, int64_t last_call_time)
{
    rcl_publish(&tf_mini_1_pub, &tf_mini_msg_1, NULL);
}
void tf_mini_2_Cb(rcl_timer_t * timer, int64_t last_call_time)
{
    rcl_publish(&tf_mini_2_pub, &tf_mini_msg_2, NULL);
}

// User Defined Functions
void led(int i){
    if(i==1){
        gpio_put(LED_PIN, 1);
    }
    else{
        gpio_put(LED_PIN, 0);
    }
}

void idle_g1(){
    gpio_put(G_1_OPEN, 0);
    gpio_put(G_1_CLOSE, 0);
    led(0);
}
void idle_g2(){
    gpio_put(G_2_OPEN, 0);
    gpio_put(G_2_CLOSE, 0);
    led(0);
}
void idle(){
    gpio_put(G_1_OPEN, 0);
    gpio_put(G_1_CLOSE, 0);
    gpio_put(G_2_OPEN, 0);
    gpio_put(G_2_CLOSE, 0);
    led(0);
}

void gripper_two_open(){
    if(gpio_get(gripper1_open_limit) !=0){ //close pressed (closed to max possible)
        led(1);
        gpio_put(G_2_OPEN, 1);
        gpio_put(G_2_CLOSE, 0);
    }else{
        idle_g2();
    }
}
void gripper_two_close(){
    if(gpio_get(gripper1_close_limit) !=0){ //close pressed (closed to max possible)
        led(1);
        gpio_put(G_2_OPEN, 0);
        gpio_put(G_2_CLOSE, 1);
    }else{
        idle_g2();
    }
}
void gripper_one_open(){
    if(gpio_get(gripper1_open_limit) !=0){ //close pressed (closed to max possible)
        led(1);
        gpio_put(G_1_OPEN, 1);
        gpio_put(G_1_CLOSE, 0);
    }else{
        idle_g1();
    }
}
void gripper_one_close(){
    if(gpio_get(gripper1_close_limit) !=0){ //close pressed (closed to max possible)
        led(1);
        gpio_put(G_1_OPEN, 0);
        gpio_put(G_1_CLOSE, 1);
    }else{
        idle_g1();
    }
}

float mapPwm(float x, float out_min, float out_max)  
{
    x = (x<0)? -x : x ;
    if(x==0){
        return 0;
    }
    else {
        if(out_max*((x+min_speed)/max_speed) <= PWMRANGE){
            return out_max*((x+min_speed)/max_speed);
        }
        else{
            return PWMRANGE;
        }
    }
}

void pwm_write(int pin,int pwm) {
    pwm_clear_irq(pwm_gpio_to_slice_num(pin));
    pwm_set_gpio_level(pin, pwm);
}

/* Subscriber Callbacks */
void velocityCb(const void * msgin){
    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;

    float u1 = (d*(msg->angular.z) - (msg->linear.y/2) + (msg->linear.x)*sin(PI/3))/wheel_radius;
    float u2 = (d*(msg->angular.z) - (msg->linear.y/2) - (msg->linear.x)*sin(PI/3))/wheel_radius;
    float u3 = (d*(msg->angular.z) + (msg->linear.y))/wheel_radius;
 
    // Then map those values to PWM intensities. PWMRANGE = full speed, while PWM_MIN = the minimal amount of power
    u1Pwm = mapPwm(u1, PWM_MIN, PWMRANGE);
    u2Pwm = mapPwm(u2, PWM_MIN, PWMRANGE);
    u3Pwm = mapPwm(u3, PWM_MIN, PWMRANGE);

    // Set direction pins and PWM
    gpio_put(IN_1, ((u1>0) ? 0 : 1)); 
    pwm_write(ENA, u1Pwm);
    gpio_put(IN_2, ((u2>0) ? 0 : 1)); 
    pwm_write(ENB, u2Pwm);
    gpio_put(IN_3, ((u3>0) ? 0 : 1)); 
    pwm_write(ENC, u3Pwm);
}

void gripperCb(const void * msgin){
    const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
    /*  G G G idle | open idle | close idle |
        1,2,3, 4   |   1   0   |  1      0  |
    */
   multicore_fifo_push_blocking(msg->data);
}

/* Core 1 interrupt handler */
void core1_interrupt_handler(){
    while(multicore_fifo_rvalid()){
        int poped_data = multicore_fifo_pop_blocking();
        switch (poped_data)
        {
            case 110:
                gripper_one_close();
                break;
            case 101:
                gripper_one_open();
                break;
            case 210:
                gripper_two_close();
                break;
            case 201:
                gripper_two_open();
                break;  
            default:
                idle();
                break;
        }
    }
    multicore_fifo_clear_irq();
}
/* Core 1 entry */
void core1_entry() {
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
    irq_set_enabled(SIO_IRQ_PROC1, true);
    while(1){
        tight_loop_contents();
    }
} 
/* Core 0 entry*/
int main() {
    stdio_init_all();
    multicore_launch_core1(core1_entry);
    //add binary info for uart0 and uart1
    bi_decl(bi_1pin_with_name(UART0_TX_PIN, "pin-0 for uart0 TX"));
    bi_decl(bi_1pin_with_name(UART0_RX_PIN, "pin-1 for uart0 RX"));
    bi_decl(bi_1pin_with_name(UART1_TX_PIN, "pin-4 for uart1 TX"));
    bi_decl(bi_1pin_with_name(UART1_RX_PIN, "pin-5 for uart1 RX"));

    //Set up our UARTs with the required speed.
    uart_init(UART_ID0, BAUD_RATE);
    uart_init(UART_ID1, BAUD_RATE);

    //Set the TX and RX pins by using the function
    //Look at the datasheet for more information on function select
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);
    cdcd_init();

    /* PIN CONFIGURATIONS PWM & GPIO */
    gpio_set_function(ENA, GPIO_FUNC_PWM);
    gpio_set_function(ENB, GPIO_FUNC_PWM);
    gpio_set_function(ENC, GPIO_FUNC_PWM); 

    uint slice_num_1 = pwm_gpio_to_slice_num(ENA);
    uint slice_num_2 = pwm_gpio_to_slice_num(ENB);
    uint slice_num_3 = pwm_gpio_to_slice_num(ENC);

    pwm_clear_irq(slice_num_1);
    pwm_clear_irq(slice_num_2);
    pwm_clear_irq(slice_num_3);

    pwm_set_irq_enabled(slice_num_1, true);
    pwm_set_irq_enabled(slice_num_2, true);
    pwm_set_irq_enabled(slice_num_3, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);

    // Setup Pins for PWM
    pwm_init(slice_num_1, &config, true);
    pwm_init(slice_num_2, &config, true);
    pwm_init(slice_num_3, &config, true);


    // Setup Pins for GP i/o
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_init(IN_1);
    gpio_set_dir(IN_1, GPIO_OUT);
    gpio_init(IN_2);
    gpio_set_dir(IN_2, GPIO_OUT);
    gpio_init(IN_3);
    gpio_set_dir(IN_3, GPIO_OUT);
    
	gpio_init(G_1_CLOSE);
    gpio_set_dir(G_1_CLOSE, GPIO_OUT);
    gpio_init(G_2_CLOSE);
    gpio_set_dir(G_2_CLOSE, GPIO_OUT);

	gpio_init(G_1_OPEN);
    gpio_set_dir(G_1_OPEN, GPIO_OUT);
    gpio_init(G_2_OPEN);
    gpio_set_dir(G_2_OPEN, GPIO_OUT);

    //gripper open close limit switches
    gpio_init(gripper1_open_limit);
    gpio_set_dir(gripper1_open_limit, false);
    gpio_pull_up(gripper1_open_limit);

    gpio_init(gripper2_open_limit);
    gpio_set_dir(gripper2_open_limit, false);
    gpio_pull_up(gripper2_open_limit);

    gpio_init(gripper1_close_limit);
    gpio_set_dir(gripper1_close_limit, false);
    gpio_pull_up(gripper1_close_limit);

    gpio_init(gripper2_close_limit);
    gpio_set_dir(gripper2_close_limit, false);
    gpio_pull_up(gripper2_close_limit);

    //creating node, allocator, support, executor 
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();
    
    // timer to callback each publisher
    rcl_timer_t timer_tf_mini_1;
    rcl_timer_t timer_tf_mini_2;
    
    // Check if micro-ROS Agent answers to micro-ROS client
    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );

    // Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;
    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
    if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

    //create init_options
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rclc_node_init_default(&node, "cmd_vel_node", "", &support);

    // create subscriber - cmd_vel_sub
    rclc_subscription_init_default(
        &r2_cmd_vel_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        &cmd_vel_subscriber_name);

    //create subscriber - gripper_sub
    rclc_subscription_init_default(
        &gripper_sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        &r2_gripper_subscriber_name);  

    // create tf mini s pubs 
    rclc_publisher_init_default(
		&tf_mini_1_pub,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
		&tf_mini_1_pub_name);

    rclc_publisher_init_default(
		&tf_mini_2_pub,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
		&tf_mini_2_pub_name);
    
    //after a time each publisher is call backed
	rclc_timer_init_default(
		&timer_tf_mini_1,
		&support,
		RCL_MS_TO_NS(20),
		tf_mini_1_Cb);

	rclc_timer_init_default(
		&timer_tf_mini_2,
		&support,
		RCL_MS_TO_NS(20),
		tf_mini_2_Cb);

    rclc_executor_init(&executor, &support.context, 8, &allocator);
    rclc_executor_add_subscription(&executor, &r2_cmd_vel_subscriber, &r2_cmd_vel_msg, &velocityCb, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &gripper_sub, &gripper_msg, &gripperCb, ON_NEW_DATA); 

    //add timer
    rclc_executor_add_timer(&executor, &timer_tf_mini_1);
    rclc_executor_add_timer(&executor, &timer_tf_mini_2);
    //run the executor in loop     
    while (true)
    {
        // spins every 1 ms, 0.001 s, frequency = 100 Hz
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(0.02)); 
        if(isLidar(UART_ID1,&Lidar_1))
        {
            tf_mini_msg_1.data = Lidar_1.lidar.Dist;
        }
        if(isLidar(UART_ID0,&Lidar_2))
        {
            tf_mini_msg_2.data = Lidar_2.lidar.Dist;
        }
    }
    return 0;
}






/* 
case 11000:
        stepper(1,1);
        //gpio_put(LED_PIN, 1); 
        break;
    case 10100:
        stepper(1,0,pwm_val); 
        //gpio_put(LED_PIN, 1);  
        break; 

    case 21000:
        stepper(2,1,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;
    case 20100:
        stepper(2,0,pwm_val);  
        gpio_put(LED_PIN, 1); 
        break;  

    case 31000:
        stepper(3,1,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;
    case 30100:
        stepper(3,0,pwm_val);
        gpio_put(LED_PIN, 1);   
        break;

    case 30010:
        gripper3(3,1); 
        led(true); 
        break;
    case 30001:
        gripper3(3,0);
        led(true); 
        break;



    // const std_msgs__msg__Int32 * state = (const std_msgs__msg__Int32 *)msgin;
    // int r_num = state->data;

    // switch(r_num)
    // {
    // case 10010:
    //     //led(1);
    //     gripper1(1);
    //     break;
    // case 10001:
    //     //led(1);
    //     gripper1(0);
    //     break;
    // case 20010:
    //     //led(1);
    //     gripper2(1);
    //     break;
    // case 20001:
    //     //led(1);
    //     gripper2(0);
    //     break;
    // default:
    //     idle(1);
    //     idle(2);
    //     break;   
    // }
*/
