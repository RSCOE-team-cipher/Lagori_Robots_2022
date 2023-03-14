#include <stdio.h>
#include <math.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"

#include <geometry_msgs/msg/twist.h>
//#include <std_msgs/msg/float32.h>
//#include <std_msgs/msg/int32.h>

// Custom Messages
//#include <lagori_robot_msgs/msg/gripper_msg.h>

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

//#include <std_msgs/msg/float32.h>
//#include <std_msgs/msg/int32.h>

/* DEFINE */
#define PI 3.14159265
#define IN_1 7
#define IN_2 9          
#define IN_3 10                
#define ENA 6
#define ENB 8
#define ENC 11               

// #define G_1 7//9
// #define G_1_PWM 8//8
// #define G_2 9//7
// #define G_2_PWM 10//6
// #define G_3 11//5
// #define G_3_PWM 12//4

// #define gripper1_close 13
// #define gripper1_open 14
// #define gripper2_close 15
// #define gripper2_open 16
// #define gripper3_close 17
// #define gripper3_open 18

// 0 to 65025

/* Configurations */
int PWM_MIN = 10;
int PWMRANGE = 65025;
int min_speed = 1;
int max_speed = 31.42;

#define pwm_val 55000

const uint LED_PIN = 25;

uint32_t u1Pwm, u2Pwm, u3Pwm;

/* Robots Params */
float wheel_radius = 0.1;
float d = 0.36;

/* Define Sub Pub */
rcl_subscription_t cmd_vel_sub;
//rcl_subscription_t gripper_sub;

geometry_msgs__msg__Twist cmd_vel_msg;
// lagori_robot_msgs__msg__GripperMsg gripper_msg;

// rcl_publisher_t publisher_u1;
// rcl_publisher_t publisher_u2;
// rcl_publisher_t publisher_u3;

// std_msgs__msg__Float32 msg_float_u1;
// std_msgs__msg__Float32 msg_float_u2;
// std_msgs__msg__Float32 msg_float_u3;

/* Publisher Callbacks */

// void timer_callback_u1(rcl_timer_t * timerx, int64_t last_call_time)
// {
// 	rcl_publish(&publisher_u1, &msg_float_u1, NULL);
// }

// void timer_callback_u2(rcl_timer_t * timery, int64_t last_call_time)
// {
// 	rcl_publish(&publisher_u2, &msg_float_u2, NULL);
// }

// void timer_callback_u3(rcl_timer_t * timerz, int64_t last_call_time)
// {
// 	rcl_publish(&publisher_u3, &msg_float_u3, NULL);
// }

// void timer_callback_check(rcl_timer_t * timer_check, int64_t last_call_time)
// {
// 	rcl_publish(&publisher_check, &int_check, NULL);
// }

// User Defined Functions
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
void led(int i){
    (i==1) ? gpio_put(LED_PIN, 1) : gpio_put(LED_PIN, 0);
}
// void idle(){}
// /* dir 1 = open, dir 0 = close */
// void gripper1(int dir){
//     //(dir == 1) ? /* open */ : /* close */
//     if(gpio_get(gripper1_close) !=0){ //close pressed (closed to max possible)
//         (dir == 1) ? /* open only */ : false; 
//     }
//     else if(gpio_get(gripper1_open) !=0){ //open pressed (open to max possible)
//         (dir == 0) ? /* close only */ : false;
//     }else{
//         (dir == 1) ? /* open */ : /* close */
//     }
// }
// void gripper2(int dir){
//     //(dir == 1) ? /* open */ : /* close */
//     if(gpio_get(gripper2_close) !=0){ //close pressed (closed to max possible)
//         (dir == 1) ? /* open only */ : false; 
//     }
//     else if(gpio_get(gripper2_open) !=0){ //open pressed (open to max possible)
//         (dir == 0) ? /* close only */ : false;
//     }else{
//         (dir == 1) ? /* open */ : /* close */
//     }
// }
// void gripper3(int dir){
//     //(dir == 1) ? /* open */ : /* close */
//     if(gpio_get(gripper3_close) !=0){ //close pressed (closed to max possible)
//         (dir == 1) ? /* open only */ : false; 
//     }
//     else if(gpio_get(gripper3_open) !=0){ //open pressed (open to max possible)
//         (dir == 0) ? /* close only */ : false;
//     }else{
//         (dir == 1) ? /* open */ : /* close */
//     }
// }

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
    gpio_put(IN_2, ((u2>0) ? 1 : 0)); 
    pwm_write(ENB, u2Pwm);
    gpio_put(IN_3, ((u3>0) ? 0 : 1)); 
    pwm_write(ENC, u3Pwm);
    
    //debug purpose
    // msg_float_u1.data = u1Pwm;
    // msg_float_u2.data = u2Pwm;
    // msg_float_u3.data = u3Pwm;  
}

// void gripperCb(const void * msgin){
//     const lagori_robot_msgs__msg__GripperMsg * msg = (const lagori_robot_msgs__msg__GripperMsg *)msgin;
//     //declare array of 1 2 3 gripper 
//     //on button press 1, else 0
//     int one[2] = {msg->one_open, msg->one_close};
//     int two[2] = {msg->two_open, msg->two_close};
//     int three[2] = {msg->three_open, msg->three_close};

//     // (one[0] == 1) ? gripper1(1) : (one[1] == 1) ? gripper1(0) : idle();

//     // (two[0] == 1) ? gripper2(1) : (two[1] == 1) ? gripper2(0) : idle();

//     // (three[0] == 1) ? gripper3(1) : (three[1] == 1) ? gripper3(0) : idle();    
// }

int main() {
    stdio_init_all();

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
    
	// gpio_init(G_1);
    // gpio_set_dir(G_1, GPIO_OUT);
    // gpio_init(G_2);
    // gpio_set_dir(G_2, GPIO_OUT);
    // gpio_init(G_3);
    // gpio_set_dir(G_3, GPIO_OUT);

	// gpio_init(G_1_PWM);
    // gpio_set_dir(G_1_PWM, GPIO_OUT);
    // gpio_init(G_2_PWM);
    // gpio_set_dir(G_2_PWM, GPIO_OUT);
    // gpio_init(G_3_PWM);
    // gpio_set_dir(G_3_PWM, GPIO_OUT);

    //gripper open close limit switches
    // gpio_init(gripper1_open);
    // gpio_set_dir(gripper1_open, false);
    // gpio_init(gripper2_open);
    // gpio_set_dir(gripper2_open, false);
    // gpio_init(gripper3_open);
    // gpio_set_dir(gripper3_open, false);

    // gpio_init(gripper1_close);
    // gpio_set_dir(gripper1_close, false);
    // gpio_init(gripper2_close);
    // gpio_set_dir(gripper2_close, false);
    // gpio_init(gripper3_close);
    // gpio_set_dir(gripper3_close, false);

    //creating node, allocator, support, executor 
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

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
        &cmd_vel_sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
        "robot_2/cmd_vel");

    // create subscriber - gripper_sub
    // rclc_subscription_init_default(
    //     &gripper_sub,
    //     &node,
    //     ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, GripperMsg),
    //     "r2_gripper");   

    rclc_executor_init(&executor, &support.context, 8, &allocator);
    rclc_executor_add_subscription(&executor, &cmd_vel_sub, &cmd_vel_msg, &velocityCb, ON_NEW_DATA);
    //rclc_executor_add_subscription(&executor, &gripper_sub, &gripper_msg, &gripperCb, ON_NEW_DATA);     

    gpio_put(LED_PIN, 1);
    //run the executor in loop     
    while (true)
    {
        // spins every 1 ms, 0.001 s, frequency = 100 Hz
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(1)); 
    }
    return 0;
}




