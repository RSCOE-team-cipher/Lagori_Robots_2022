/* This Code has 2 Wheel controls, Planetary Motor controls, 2 tf mini s */

#include <stdio.h>    
#include <math.h>

//ros2 
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/float32.h>

//ros2 custom msg
#include <lagori_robot_msgs/msg/robot_one_controls.h>

//pico libs - included in pico-sdk 
#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "tusb.h" 
#include <pico/multicore.h>

/* Ros Pub Sub names */

rcl_subscription_t robot_controls_subscriber;
lagori_robot_msgs__msg__RobotOneControls robot_controls_msgs;
char robot_controls_pub_name[] = "robot_1_controls";

rcl_subscription_t r1_cmd_vel_subscriber;
geometry_msgs__msg__Twist r1_cmd_vel_msg;
char cmd_vel_subscriber_name[] = "robot_1/cmd_vel";

// rcl_publisher_t tf_mini_1_pub;
// std_msgs__msg__Float32 tf_mini_msg_1;
// char tf_mini_1_pub_name[] = "r1_tf_mini_s1";

// rcl_publisher_t tf_mini_2_pub;
// std_msgs__msg__Float32 tf_mini_msg_2;
// char tf_mini_2_pub_name[] = "r1_tf_mini_s2";

/* DEFINE */
// base motor 
#define LEFT_1 7
#define RIGHT_1 6
#define LEFT_2 9
#define RIGHT_2 8

//both planetary rotors same
#define IN_ROTOR 11
#define PWM_ROTOR 10

// //uart pins for tf mini s 
// #define UART0_TX_PIN 0 
// #define UART0_RX_PIN 1 
// #define UART1_TX_PIN 4 
// #define UART1_RX_PIN 5

// #define UART_ID0 uart0
// #define BAUD_RATE 115200
// #define UART_ID1 uart1

// pwm values declare for 2 wheels of R1
uint32_t u1Pwm, u2Pwm;

// led pin for debugging
const uint LED_PIN = 25;

/* Rotor Configs */
int rotor_pwm = 60000;
int wheel_pwm = 8000;
bool running = false; // running status of motor

// // ****************************Structure and Union for handling LiDAR Data***********

// // Dist_L Dist_H Strength_L Strength_H Temp_L Temp_H Checksum
// typedef struct{
// unsigned short Header;
// unsigned short Dist;
// unsigned short Strength;
// }structLidar;

// union unionLidar{
// unsigned char Byte[9];
// structLidar lidar;
// };

// unsigned char lidarCounter=0;

// union unionLidar Lidar_1;
// union unionLidar Lidar_2;

// //****************************Function to read serial data***********

// int isLidar(uart_inst_t * uart, union unionLidar * lidar)
// {
//   int loop;
//   int checksum;
//   unsigned char serialChar;

//   while(uart_is_readable(uart))
//   {
//    if(lidarCounter > 8)
//     {
//       lidarCounter=0;
//       return 0; // something wrong
//     }

//    serialChar = uart_getc(uart); // Read a single character to UART.
//    lidar->Byte[lidarCounter]= serialChar;

//    switch(lidarCounter++)
//    {
//     case 0:
//     case 1:
//     	   if(serialChar !=0x59)
//               lidarCounter=0;
//            break;
//     case 8: // checksum
//             checksum=0;
//             lidarCounter=0;
//             for(loop=0;loop<8;loop++)
//                 checksum+= lidar->Byte[loop];
//             if((checksum &0xff) == serialChar)
//                 {   
//                   lidar->lidar.Dist = lidar->Byte[2] | lidar->Byte[3] << 8;
//                   lidar->lidar.Strength = lidar->Byte[4] | lidar->Byte[5] << 8;
//                   return 1;
//                 }
//     }
//    }
//     return 0;
// }

/* FUNCTIONS */
void pwm_write(int pin,int pwm) {
    pwm_clear_irq(pwm_gpio_to_slice_num(pin));
    pwm_set_gpio_level(pin, pwm);
}
void led(bool i){
    (i) ? gpio_put(LED_PIN, 1) : gpio_put(LED_PIN, 0);
}
void idle() {
    pwm_write(PWM_ROTOR, 0);
}

void idle_base() {
    pwm_write(LEFT_1, 0);
    pwm_write(RIGHT_2, 0);
    pwm_write(RIGHT_1, 0);
    pwm_write(LEFT_2, 0);
    led(false);
}
void rotors(){
    if(!running){
        led(true);
        for(int i=0; i<=rotor_pwm; i= i+5){    
            pwm_write(PWM_ROTOR, i);
            sleep_us(50);
        }
        running = true;
        sleep_ms(100);
    }
    else {
        //stop
        led(false);
        for(int i=rotor_pwm; i>=0; i=i-5){
            pwm_write(PWM_ROTOR, i);
            sleep_us(50);
        }
        running = false;
    }  
}

// /* Publisher callbacks tf mini s 1 & 2 */ 
// void tf_mini_1_Cb(rcl_timer_t * timer, int64_t last_call_time)
// {
//     rcl_publish(&tf_mini_1_pub, &tf_mini_msg_1, NULL);
// }
// void tf_mini_2_Cb(rcl_timer_t * timer, int64_t last_call_time)
// {
//     rcl_publish(&tf_mini_2_pub, &tf_mini_msg_2, NULL);
// }

void rotation_z(int i, int pwm){
    if(i == 1){
        led(true);
        pwm_write(LEFT_1, pwm);
        pwm_write(LEFT_2, pwm);
    }else{
        led(true);
        pwm_write(RIGHT_1, pwm);
        pwm_write(RIGHT_2, pwm);
    }
    
}
void move_x(int i, int pwm){
    if(i == 1){
        led(true);
        pwm_write(LEFT_1, pwm);
        pwm_write(RIGHT_2, pwm);
    }else{
        led(true);
        pwm_write(RIGHT_1, pwm);
        pwm_write(LEFT_2, pwm);
    }
}

//void rotation_x(){}
/* Subscriber Callback robot_1/cmd_vel */
void velocityCb(const void * msgin){

    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;

    float x = msg->linear.x;
    
    float z = msg->angular.z;
    //(x==0) ? idle_base() : ((x>0) ? move_x(1, wheel_pwm) : move_x(0, wheel_pwm));
    if(z==0){
        (x==0) ? idle_base() : ((x>0) ? move_x(0, wheel_pwm) : move_x(1, wheel_pwm));
    }else if(x==0){
        (z==0) ? idle_base() : ((z>0) ? rotation_z(1, wheel_pwm) : rotation_z(0, wheel_pwm));
    }else idle_base();
    
    //multicore_fifo_push_blocking(x*100 + z);
    //(z==0) ? idle_base() : ((z>0) ? rotation_z(1, wheel_pwm) : rotation_z(0, wheel_pwm));
}
/* Custom msg Sub Callback */
void r1_controls_callback(const void * msgin){
    const lagori_robot_msgs__msg__RobotOneControls * msg = (const lagori_robot_msgs__msg__RobotOneControls *)msgin;
    (msg->rotor == 1) ? rotors() : false;
}
/* Core 1 interrupt handler */
void core1_interrupt_handler(){
    while(multicore_fifo_rvalid()){
        led(true);
        int x = multicore_fifo_pop_blocking();

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
    
    // // add binary info for uart0 and uart1
    // bi_decl(bi_1pin_with_name(UART0_TX_PIN, "pin-0 for uart0 TX"));
    // bi_decl(bi_1pin_with_name(UART0_RX_PIN, "pin-1 for uart0 RX"));
    // bi_decl(bi_1pin_with_name(UART1_TX_PIN, "pin-4 for uart1 TX"));
    // bi_decl(bi_1pin_with_name(UART1_RX_PIN, "pin-5 for uart1 RX"));

    // // Set up our UARTs with the required speed.
    // uart_init(UART_ID0, BAUD_RATE);
    // uart_init(UART_ID1, BAUD_RATE);

    // Set the TX and RX pins by using the function
    // Look at the datasheet for more information on function select
    // gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);
    // cdcd_init();

    //set up pwm pins
    gpio_set_function(LEFT_1, GPIO_FUNC_PWM);
    gpio_set_function(LEFT_2, GPIO_FUNC_PWM);
    gpio_set_function(RIGHT_1, GPIO_FUNC_PWM);
    gpio_set_function(RIGHT_2, GPIO_FUNC_PWM);

    gpio_set_function(PWM_ROTOR, GPIO_FUNC_PWM);

    uint slice_num_1 = pwm_gpio_to_slice_num(LEFT_1);
    uint slice_num_2 = pwm_gpio_to_slice_num(LEFT_2);
    uint slice_num_3 = pwm_gpio_to_slice_num(RIGHT_1);
    uint slice_num_4 = pwm_gpio_to_slice_num(RIGHT_2);

    uint slice_num_5 = pwm_gpio_to_slice_num(PWM_ROTOR);

    pwm_clear_irq(slice_num_1);
    pwm_clear_irq(slice_num_2);
    pwm_clear_irq(slice_num_3);
    pwm_clear_irq(slice_num_4);
    pwm_clear_irq(slice_num_5);

    pwm_set_irq_enabled(slice_num_1, true);
    pwm_set_irq_enabled(slice_num_2, true);
    pwm_set_irq_enabled(slice_num_3, true);
    pwm_set_irq_enabled(slice_num_4, true);
    pwm_set_irq_enabled(slice_num_5, true);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);

    pwm_init(slice_num_1, &config, true);
    pwm_init(slice_num_2, &config, true);
    pwm_init(slice_num_3, &config, true);
    pwm_init(slice_num_4, &config, true);
    pwm_init(slice_num_5, &config, true);
    
    //set direction pins
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(IN_ROTOR);
    gpio_set_dir(IN_ROTOR, GPIO_OUT);

    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );

    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    // timer to callback each publisher
    rcl_timer_t timer_tf_mini_1;
    rcl_timer_t timer_tf_mini_2;

    //Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;
    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
    if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

    //create init_options
    rclc_support_init(&support, 0, NULL, &allocator);

    // create node
    rclc_node_init_default(&node, "cmd_vel_node", "", &support);

    // create subscriber - cmd_vel 
    rclc_subscription_init_default(
        &r1_cmd_vel_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        &cmd_vel_subscriber_name);

    // create subscriber - r1_controls
    rclc_subscription_init_default(
        &robot_controls_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, RobotOneControls),
        &robot_controls_pub_name);

    // create subscriber - joy
    // rclc_subscription_init_default(
    //     &joy_subscriber,
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Joy),
    //     "joy");

    // create tf mini s pubs 
    // rclc_publisher_init_default(
	// 	&tf_mini_1_pub,
	// 	&node,
	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
	// 	&tf_mini_1_pub_name);

    // rclc_publisher_init_default(
	// 	&tf_mini_2_pub,
	// 	&node,
	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
	// 	&tf_mini_2_pub_name);
    
    // // after a time each publisher is call backed
	// rclc_timer_init_default(
	// 	&timer_tf_mini_1,
	// 	&support,
	// 	RCL_MS_TO_NS(10),
	// 	tf_mini_1_Cb);

	// rclc_timer_init_default(
	// 	&timer_tf_mini_2,
	// 	&support,
	// 	RCL_MS_TO_NS(10),
	// 	tf_mini_2_Cb);

    // create executor
    rclc_executor_init(&executor, &support.context, 6, &allocator);
    rclc_executor_add_subscription(&executor, &r1_cmd_vel_subscriber, &r1_cmd_vel_msg, &velocityCb, ON_NEW_DATA);
    rclc_executor_add_subscription(&executor, &robot_controls_subscriber, &robot_controls_msgs, &r1_controls_callback, ON_NEW_DATA);

    //add timer
    // rclc_executor_add_timer(&executor, &timer_tf_mini_1);
    // rclc_executor_add_timer(&executor, &timer_tf_mini_2);

    //main loop
    while (true){
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(0.01));
        
        // if(isLidar(UART_ID1,&Lidar_1))
        // {
        //     tf_mini_msg_1.data = Lidar_1.lidar.Dist;
        // }
        // if(isLidar(UART_ID0,&Lidar_2))
        // {
        //     tf_mini_msg_2.data = Lidar_2.lidar.Dist;
        // }
    }
    
    return 0;
}

// old code not needed

///////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <stdio.h>    
// #include <math.h>

// #include <rcl/rcl.h>
// #include <rcl/error_handling.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>
// #include <rmw_microros/rmw_microros.h>

// #include "pico/stdlib.h"
// #include "pico_uart_transports.h"

// #include <geometry_msgs/msg/twist.h>
// #include <std_msgs/msg/float32.h>
// #include <std_msgs/msg/int32.h>

// #include "hardware/gpio.h"
// #include "hardware/irq.h"
// #include "hardware/pwm.h"

// /* DEFINE */
// #define PI 3.14159265

// #define PWM_LEFT_1 15  
// #define PWM_RIGHT_1 14           
// #define PWM_LEFT_2 11 
// #define PWM_RIGHT_2 10             
// #define PWM_LEFT_3 13
// #define PWM_RIGHT_3 12
// #define PWM_LEFT_4 9 
// #define PWM_RIGHT_4 8           

// #define PWM_FEEDER_LEFT 17
// #define PWM_FEEDER_RIGHT 16

// #define PWM_ANGLE_LEFT 19
// #define PWM_ANGLE_RIGHT 18

// #define IN_ROTOR 20
// #define PWM_ROTOR 21

// #define DOWN_SWITCH 0
// #define UP_SWITCH 1

// #define SERVO_BTN 3

// /* angle, rollers, feeder, flap */

// /* CONFIGURATIONS */
// int rotor_pwm = 50000;
// int feeder_pwm = 11500;
// int angle_pwm = 18500;

// // 0 to max 65025.
// int PWM_MIN = 10;
// int PWMRANGE = 50000;
// int min_speed = 4;
// int max_speed = 31.42;
// bool running;
// const uint LED_PIN = 25;

// uint32_t u1Pwm, u2Pwm, u3Pwm, u4Pwm;

// /* ROBOT PARAMS */
// float l = 0.46;
// float w = 0.375;
// float wheel_radius = 0.1;


// rcl_subscription_t subscriber;
// rcl_subscription_t subscriber_twist;

// // rcl_publisher_t publisher_u1;
// // rcl_publisher_t publisher_u2;
// // rcl_publisher_t publisher_u3;
// // rcl_publisher_t publisher_u4;

// // std_msgs__msg__Float32 msg_float_u1;
// // std_msgs__msg__Float32 msg_float_u2;
// // std_msgs__msg__Float32 msg_float_u3;
// // std_msgs__msg__Float32 msg_float_u4;

// geometry_msgs__msg__Twist msg;
// std_msgs__msg__Int32 msg_int;

// /* FUNCTIONS */
// // void timer_callback_u1(rcl_timer_t * timer, int64_t last_call_time)
// // {
// // 	rcl_publish(&publisher_u1, &msg_float_u1, NULL);
// // }
// // void timer_callback_u2(rcl_timer_t * timer, int64_t last_call_time)
// // {
// // 	rcl_publish(&publisher_u2, &msg_float_u2, NULL);
// // }
// // void timer_callback_u3(rcl_timer_t * timer, int64_t last_call_time)
// // {
// // 	rcl_publish(&publisher_u3, &msg_float_u3, NULL);
// // }
// // void timer_callback_u4(rcl_timer_t * timer, int64_t last_call_time)
// // {
// // 	rcl_publish(&publisher_u4, &msg_float_u4, NULL);
// // }

// float mapPwm(float u, float out_min, float out_max)  
// {
//     u = abs(u);
//     if(u<=1){
//         return 0;
//     }
//     else if(out_max*((u+min_speed)/max_speed) < PWMRANGE){
//         return out_max*((u+min_speed)/max_speed);
//     }
//     else{
//       return PWMRANGE-1000;
//     }
// }
// void pwm_write(int pin,int pwm) {
//     pwm_clear_irq(pwm_gpio_to_slice_num(pin));
//     pwm_set_gpio_level(pin, pwm);
// }

// float idle(){
// 	pwm_write(PWM_LEFT_1, 0);
// 	pwm_write(PWM_LEFT_2, 0);
// 	pwm_write(PWM_LEFT_3, 0);
// 	pwm_write(PWM_LEFT_4, 0);
// 	pwm_write(PWM_RIGHT_1, 0);
// 	pwm_write(PWM_RIGHT_2, 0);
// 	pwm_write(PWM_RIGHT_3, 0);
// 	pwm_write(PWM_RIGHT_4, 0);
//     gpio_put(LED_PIN, 0);
// } 
// // forward = 1 , backward = -1, left = -2, right = -2, clock = 3, anticlock = -3

// void backward(int pwm1, int pwm2, int pwm3, int pwm4){
// 	pwm_write(PWM_LEFT_1, 0);
// 	pwm_write(PWM_LEFT_2, pwm2);
// 	pwm_write(PWM_LEFT_3, pwm3);
// 	pwm_write(PWM_LEFT_4, 0);
// 	pwm_write(PWM_RIGHT_1, pwm1);
// 	pwm_write(PWM_RIGHT_2, 0);
// 	pwm_write(PWM_RIGHT_3, 0);
// 	pwm_write(PWM_RIGHT_4, pwm4);
//     gpio_put(LED_PIN, 1);
// }

// void forward(int pwm1, int pwm2, int pwm3, int pwm4){
//     pwm_write(PWM_LEFT_1, pwm1);
// 	pwm_write(PWM_LEFT_2, 0);
// 	pwm_write(PWM_LEFT_3, 0);
// 	pwm_write(PWM_LEFT_4, pwm4);
// 	pwm_write(PWM_RIGHT_1, 0);
// 	pwm_write(PWM_RIGHT_2, pwm2);
// 	pwm_write(PWM_RIGHT_3, pwm3);
// 	pwm_write(PWM_RIGHT_4, 0);
//     gpio_put(LED_PIN, 1);
// }

// void left(int pwm1, int pwm2, int pwm3, int pwm4){
// 	pwm_write(PWM_LEFT_1, pwm1);
// 	pwm_write(PWM_LEFT_2, pwm2);
// 	pwm_write(PWM_LEFT_3, pwm3);
// 	pwm_write(PWM_LEFT_4, pwm4);
// 	pwm_write(PWM_RIGHT_1, 0);
// 	pwm_write(PWM_RIGHT_2, 0);
// 	pwm_write(PWM_RIGHT_3, 0);
// 	pwm_write(PWM_RIGHT_4, 0);
//     gpio_put(LED_PIN, 1);

// }
// void right(int pwm1, int pwm2, int pwm3, int pwm4){
// 	pwm_write(PWM_LEFT_1, 0);
// 	pwm_write(PWM_LEFT_2, 0);
// 	pwm_write(PWM_LEFT_3, 0);
// 	pwm_write(PWM_LEFT_4, 0);
// 	pwm_write(PWM_RIGHT_1, pwm1);
// 	pwm_write(PWM_RIGHT_2, pwm2);
// 	pwm_write(PWM_RIGHT_3, pwm3);
// 	pwm_write(PWM_RIGHT_4, pwm4);
//     gpio_put(LED_PIN, 1);

// }
// void clock(int pwm1, int pwm2, int pwm3, int pwm4){
// 	pwm_write(PWM_LEFT_1, pwm1);
// 	pwm_write(PWM_LEFT_2, pwm2);
// 	pwm_write(PWM_LEFT_3, 0);
// 	pwm_write(PWM_LEFT_4, 0);
// 	pwm_write(PWM_RIGHT_1, 0);
// 	pwm_write(PWM_RIGHT_2, 0);
// 	pwm_write(PWM_RIGHT_3, pwm3);
// 	pwm_write(PWM_RIGHT_4, pwm4);
//     gpio_put(LED_PIN, 1);

// }
// void anticlock(int pwm1, int pwm2, int pwm3, int pwm4){
// 	pwm_write(PWM_LEFT_1, 0);
// 	pwm_write(PWM_LEFT_2, 0);
// 	pwm_write(PWM_LEFT_3, pwm3);
// 	pwm_write(PWM_LEFT_4, pwm4);
// 	pwm_write(PWM_RIGHT_1, pwm1);
// 	pwm_write(PWM_RIGHT_2, pwm2);
// 	pwm_write(PWM_RIGHT_3, 0);
// 	pwm_write(PWM_RIGHT_4, 0);
//     gpio_put(LED_PIN, 1);

// }
// void velocityCb(const void * msgin){
//     const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
    
//     float x = msg->linear.x;
//     float y = msg->linear.y;
//     float z = msg->angular.z;

//     float u1 = (z * (-l - w) + x - y)/wheel_radius;
//     float u2 = (z * (l + w) + x + y)/wheel_radius;
//     float u3 = (z * (l + w) + x - y)/wheel_radius;
//     float u4 = (z * (-l - w) + x + y)/wheel_radius;

  
//     u1Pwm = mapPwm(u1, PWM_MIN, PWMRANGE);
//     u2Pwm = mapPwm(u2, PWM_MIN, PWMRANGE);
//     u3Pwm = mapPwm(u3, PWM_MIN, PWMRANGE);
//     u4Pwm = mapPwm(u4, PWM_MIN, PWMRANGE);


//     if(x==0){
//       	if(y==0){
//         	if(z==0){
//           		idle();
//         	}else if(z<0){
// 		  		//clock
// 				clock(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 	    	}else if(z>0){
// 				//anticlock
// 				anticlock(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 			}else{idle();}
// 		}else if(y<0){
// 			//left
// 			left(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 		}else if(y>0){
// 			//right
// 			right(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 		}else{idle();}	
//     }else if(x>0){
// 		//forward
// 		forward(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 	}else if(x<0){
// 		//backward
// 		backward(u1Pwm, u2Pwm, u3Pwm, u4Pwm);
// 	}else{idle();}

//   	// msg_float_u1.data = u1;
//   	// msg_float_u2.data = u2;
//   	// msg_float_u3.data = u3;   
//   	// msg_float_u4.data = u4;

// }

// // void feeder(int i){

// //     do{
// //          
// //         }
// //     }while(gpio_get(DOWN_SWITCH) == 0);

// // }
// void feeder_up(){
//     if(gpio_get(UP_SWITCH)!=0){
//         gpio_put(PWM_FEEDER_RIGHT, 1);
//         gpio_put(LED_PIN, 1);
//     }
//     else{
//         gpio_put(PWM_FEEDER_RIGHT, 0);
//         gpio_put(PWM_FEEDER_LEFT, 0);
//         gpio_put(LED_PIN, 0);
//         sleep_ms(50);
//     }
//     //sleep_ms(800);
// }
// void feeder_down(){    
//     if(gpio_get(DOWN_SWITCH)!=0){
//         gpio_put(PWM_FEEDER_RIGHT, 0);
//         gpio_put(PWM_FEEDER_LEFT, 1);
//         gpio_put(LED_PIN, 1);
//     }
//     else{
//         gpio_put(PWM_FEEDER_LEFT, 0);
//         gpio_put(PWM_FEEDER_RIGHT, 0);
//         gpio_put(LED_PIN, 0);          
//         sleep_ms(50);
//     }
//     //sleep_ms(800);
// }
// void rotors_on(){
//     if(!running){
//         for(int i=0; i<=rotor_pwm;i++){    
//             pwm_write(PWM_ROTOR, i);       
//         }    
//         gpio_put(LED_PIN, 1);
//         running = true;
//         sleep_ms(200);
//     }
//     else {
//         pwm_write(PWM_ROTOR, rotor_pwm);
//         gpio_put(LED_PIN, 1); 
//     }  
// }
// void rotors_off(){
//     for(int i=rotor_pwm; i>=0; i--){
//         pwm_write(PWM_ROTOR, i);
//     }
//     gpio_put(LED_PIN, 1);
//     running = false;
// }
// void angle_down(){
//     if(gpio_get(DOWN_SWITCH)!=0){
//         gpio_put(PWM_ANGLE_LEFT, 0);
//         gpio_put(PWM_ANGLE_RIGHT, 1);
//         gpio_put(LED_PIN, 1);
//     }else{
//         gpio_put(PWM_ANGLE_LEFT, 0);
//         gpio_put(PWM_ANGLE_RIGHT, 0);
//     }    
// }
// void angle_up(){
//     gpio_put(PWM_ANGLE_RIGHT, 0);
//     gpio_put(PWM_ANGLE_LEFT, 1);
//     gpio_put(LED_PIN, 1);
// }
// void servo(){
//     gpio_put(SERVO_BTN, 0);
// 	gpio_put(LED_PIN, 1);
// }

// void twistoCb(const void * msgin){
//     const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
//     int r_num = msg->data;
    
//     /*
//         angle up - 1 , down - 2       nothing - 3
//         feeder up - 1 nothing - 0, 
//         feeder down - 1 nothing 0,
//         rotor on - 1, nothing - 0 
//         rotor off - 1, nothing - 0
//         servo on - 1, nothing - 0  
//     */

//     switch(r_num){
//         //initial single run
//         case 100000:
//             //angle up
//             angle_up();
//             break;
//         case 200000:
//             //angle down
//             angle_down();
//             break;
//         case 310000:
//             //feeder up
//             feeder_up();
//             break;
//         case 301000:
//             //feeder down
//             feeder_down();
//             break;
//         case 300100:
//             //rotor on
//             rotors_on();
//             break;
//         case 300010:
//             //rotor off
//             rotors_off();
//             break;
//         case 300001:
//             //servo on off
//             servo();
//             break;

//         //while running angle up
//         case 110000:
//             angle_up();
//             feeder_up();
//             //feeder up
//             break;
//         case 101000:
//             angle_up();
//             feeder_down();
//             //feeder down
//             break;
//         case 100100:
//             angle_up();
//             rotors_on();
//             //rotor on
//             break;
//         case 100010:
//             angle_up();
//             rotors_off();
//             //rotor off
//             break;
//         case 100001:
//             angle_up();
//             servo();
//             //servo
//             break;

//         //while running angle down
//         case 210000:
//             angle_down();
//             feeder_up();
//             //feeder up
//             break;
//         case 201000:
//             angle_down();
//             feeder_down();
//             //feeder down
//             break;
//         case 200100:
//             angle_down();
//             rotors_on();
//             //rotor on
//             break;
//         case 200010:
//             angle_down();
//             rotors_off();
//             //rotor off
//             break;
//         case 200001:
//             angle_down();
//             servo();
//             //servo
//             break;

//         //while running feeder up
//         case 310100:
//             feeder_up();
//             rotors_on();
//             //rotor on
//             break;
//         case 310010:
//             feeder_up();
//             rotors_off();
//             //rotor off
//             break;
//         case 310001:
//             feeder_up();
//             servo();
//             //servo
//             break;

//         //while running feeder down
//         case 301100:
//             feeder_down();
//             rotors_on();
//             //rotor on
//             break;
//         case 301010:
//             feeder_down();
//             rotors_off();
//             //rotor off
//             break;
//         case 301001:
//             feeder_down();
//             servo();
//             //servo 
//             break;

//         //while running rotor on
//         case 300101:
//             rotors_on();
//             servo();
//             //servo
//             break;

//         //while running rotor off
//         case 300011:
//             rotors_off();
//             servo();
//             //servo
//             break;

//         default:
//             if(running){
//                 gpio_put(PWM_ANGLE_LEFT, 0);
//                 gpio_put(PWM_ANGLE_RIGHT, 0);
//                 //pwm_write(PWM_ROTOR, 0);
//                 gpio_put(PWM_FEEDER_LEFT, 0);
//                 gpio_put(PWM_FEEDER_RIGHT, 0);
//                 gpio_put(SERVO_BTN, 1);
//                 gpio_put(LED_PIN, 0);
//                 break;
//             }else{
//                 gpio_put(PWM_ANGLE_LEFT, 0);
//                 gpio_put(PWM_ANGLE_RIGHT, 0);
//                 pwm_write(PWM_ROTOR, 0);
//                 gpio_put(PWM_FEEDER_LEFT, 0);
//                 gpio_put(PWM_FEEDER_RIGHT, 0);
//                 gpio_put(SERVO_BTN, 1);
//                 gpio_put(LED_PIN, 0);
//                 break;  
//             }                        
//     }
// }


// int main() {
//     stdio_init_all();

//     gpio_set_function(PWM_LEFT_1, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_LEFT_2, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_LEFT_3, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_LEFT_4, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_RIGHT_1, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_RIGHT_2, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_RIGHT_3, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_RIGHT_4, GPIO_FUNC_PWM);
//     gpio_set_function(PWM_ROTOR, GPIO_FUNC_PWM);

//     uint slice_num_1 = pwm_gpio_to_slice_num(PWM_LEFT_1);
//     uint slice_num_2 = pwm_gpio_to_slice_num(PWM_LEFT_2);
//     uint slice_num_3 = pwm_gpio_to_slice_num(PWM_LEFT_3);
//     uint slice_num_4 = pwm_gpio_to_slice_num(PWM_LEFT_4);
//     uint slice_num_5 = pwm_gpio_to_slice_num(PWM_RIGHT_1);
//     uint slice_num_6 = pwm_gpio_to_slice_num(PWM_RIGHT_2);
//     uint slice_num_7 = pwm_gpio_to_slice_num(PWM_RIGHT_3);
//     uint slice_num_8 = pwm_gpio_to_slice_num(PWM_RIGHT_4); 
//     uint slice_num_9 = pwm_gpio_to_slice_num(PWM_ROTOR);            

    
//     pwm_clear_irq(slice_num_1);
//     pwm_clear_irq(slice_num_2);
//     pwm_clear_irq(slice_num_3);
//     pwm_clear_irq(slice_num_4);
//     pwm_clear_irq(slice_num_5);
//     pwm_clear_irq(slice_num_6);
//     pwm_clear_irq(slice_num_7);
//     pwm_clear_irq(slice_num_8);
//     pwm_clear_irq(slice_num_9);


//     pwm_set_irq_enabled(slice_num_1, true);
//     pwm_set_irq_enabled(slice_num_2, true);
//     pwm_set_irq_enabled(slice_num_3, true);
//     pwm_set_irq_enabled(slice_num_4, true);
//     pwm_set_irq_enabled(slice_num_5, true);
//     pwm_set_irq_enabled(slice_num_6, true);
//     pwm_set_irq_enabled(slice_num_7, true);
//     pwm_set_irq_enabled(slice_num_8, true);
//     pwm_set_irq_enabled(slice_num_9, true);



//     pwm_config config = pwm_get_default_config();
//     pwm_config_set_clkdiv(&config, 4.f);

//     pwm_init(slice_num_1, &config, true);
//     pwm_init(slice_num_2, &config, true);
//     pwm_init(slice_num_3, &config, true);
//     pwm_init(slice_num_4, &config, true);
//     pwm_init(slice_num_5, &config, true);
//     pwm_init(slice_num_6, &config, true);
//     pwm_init(slice_num_7, &config, true);
//     pwm_init(slice_num_8, &config, true);
//     pwm_init(slice_num_9, &config, true);

//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);

//     gpio_init(SERVO_BTN);
//     gpio_set_dir(SERVO_BTN, GPIO_OUT);

//     gpio_init(PWM_ANGLE_LEFT);
//     gpio_set_dir(PWM_ANGLE_LEFT, GPIO_OUT);
    
//     gpio_init(PWM_ANGLE_RIGHT);
//     gpio_set_dir(PWM_ANGLE_RIGHT, GPIO_OUT);

//     gpio_init(PWM_FEEDER_LEFT);
//     gpio_set_dir(PWM_FEEDER_LEFT, GPIO_OUT);	
    
//     gpio_init(PWM_FEEDER_RIGHT);
//     gpio_set_dir(PWM_FEEDER_RIGHT, GPIO_OUT);

//     gpio_init(IN_ROTOR);
//     gpio_set_dir(IN_ROTOR, GPIO_OUT);	

//     gpio_init(DOWN_SWITCH);
//     gpio_set_dir(DOWN_SWITCH, false);
// 	gpio_pull_up(DOWN_SWITCH);
	
// 	gpio_init(UP_SWITCH);
// 	gpio_set_dir(UP_SWITCH, false);
// 	gpio_pull_up(UP_SWITCH);

//     //Check if micro-ROS Agent answers to micro-ROS client
//     rmw_uros_set_custom_transport(
//         true,
//         NULL,
//         pico_serial_transport_open,
//         pico_serial_transport_close,
//         pico_serial_transport_write,
//         pico_serial_transport_read
//     );

//     // rcl_timer_t timer_a;
//     // rcl_timer_t timer_b;
//     // rcl_timer_t timer_c;
//     // rcl_timer_t timer_d;

//     rcl_node_t node;
//     rcl_allocator_t allocator;
//     rclc_support_t support;
//     rclc_executor_t executor;

//     allocator = rcl_get_default_allocator();

//     //Wait for agent successful ping for 2 minutes.
//     const int timeout_ms = 1000; 
//     const uint8_t attempts = 120;
//     rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
//     if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

//     //create init_options
//     rclc_support_init(&support, 0, NULL, &allocator);

//     // create node
//     rclc_node_init_default(&node, "cmd_vel_node", "", &support);

//     running = false;

//     // create subscriber
//     rclc_subscription_init_default(
//         &subscriber,
//         &node,
//         ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
//         "cmd_vel");

//     rclc_subscription_init_default(
//         &subscriber_twist,
//         &node,
//         ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
//         "twisto");

//     // //create publisher u1
//     // rclc_publisher_init_default(
// 	// 	&publisher_u1,
// 	// 	&node,
// 	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
// 	// 	"cmd_vel_pub_u1");

//     // //create publisher u2
//     // rclc_publisher_init_default(
// 	// 	&publisher_u2,
// 	// 	&node,
// 	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
// 	// 	"cmd_vel_pub_u2");    
    
//     // //create publisher u3
//     // rclc_publisher_init_default(
// 	// 	&publisher_u3,
// 	// 	&node,
// 	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
// 	// 	"cmd_vel_pub_u3");

//     // //create publisher u4
//     // rclc_publisher_init_default(
// 	// 	&publisher_u4,
// 	// 	&node,
// 	// 	ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
// 	// 	"cmd_vel_pub_u4");

//     // //timer callback for each publisher
// 	// rclc_timer_init_default(
// 	// 	&timer_a,
// 	// 	&support,
// 	// 	RCL_MS_TO_NS(1000),
// 	// 	timer_callback_u1);

//     // rclc_timer_init_default(
// 	// 	&timer_b,
// 	// 	&support,
// 	// 	RCL_MS_TO_NS(1000),
// 	// 	timer_callback_u2);

//     // rclc_timer_init_default(
// 	// 	&timer_c,
// 	// 	&support,
// 	// 	RCL_MS_TO_NS(1000),
// 	// 	timer_callback_u3);

//     // rclc_timer_init_default(
// 	// 	&timer_d,
// 	// 	&support,
// 	// 	RCL_MS_TO_NS(1000),
// 	// 	timer_callback_u4);

//     // create executor
//     rclc_executor_init(&executor, &support.context, 6, &allocator);
//     // rclc_executor_add_timer(&executor, &timer_a);
//     // rclc_executor_add_timer(&executor, &timer_b);
//     // rclc_executor_add_timer(&executor, &timer_c);
//     // rclc_executor_add_timer(&executor, &timer_d);
//     rclc_executor_add_subscription(&executor, &subscriber, &msg, &velocityCb, ON_NEW_DATA);
//     rclc_executor_add_subscription(&executor, &subscriber_twist, &msg_int, &twistoCb, ON_NEW_DATA);

//     //gpio_put(LED_PIN, 1); 

//     // msg_float_u1.data = 0;
//     // msg_float_u2.data = 0;
//     // msg_float_u3.data = 0; 
//     // msg_float_u4.data = 0;  

//     while (true){
//         rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));
//     }
    
//     return 0;
// }
