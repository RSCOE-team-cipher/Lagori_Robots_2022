#include <stdio.h>
#include <math.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/int32.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "tusb.h" 
#include "pico/multicore.h"

/* DEFINE */
#define PI 3.14159265

#define G_3_OPEN 14
#define G_3_CLOSE 15

#define S_1_UP 26
#define S_2_UP 3
#define S_3_UP 6

#define S_1_DOWN 27
#define S_2_DOWN 2
#define S_3_DOWN 7

const uint LED_PIN = 25;

/* Define Sub Pub */
rcl_subscription_t gripper_sub;
std_msgs__msg__Int32 gripper_msg;
char r2_gripper_subscriber_name[] = "robot_2_gripper";

rcl_subscription_t stepper_sub;
std_msgs__msg__Int32 stepper_msg;
char r2_stepper_subscriber_name[] = "robot_2_stepper";

// User Defined Functions
void led(bool i){
    if(i){
        gpio_put(LED_PIN, 1);
    }
    else{
        gpio_put(LED_PIN, 0);
    }
}
void gripper_three_open(){
    led(true);
    gpio_put(G_3_OPEN, 1);
    gpio_put(G_3_CLOSE, 0);
}
void gripper_three_close(){
    led(true);
    gpio_put(G_3_OPEN, 0);
    gpio_put(G_3_CLOSE, 1);
}

void idle_gripper(){
    led(false);
    gpio_put(G_3_OPEN, 0);
    gpio_put(G_3_CLOSE, 0);
}

void stepper1_up(){
    led(true);
    gpio_put(S_1_UP, 1);
    gpio_put(S_1_DOWN, 0);
}
void stepper1_down(){
    led(true);
    gpio_put(S_1_UP, 0);
    gpio_put(S_1_DOWN, 1);
}
void stepper2_up(){
    led(true);
    gpio_put(S_2_UP, 1);
    gpio_put(S_2_DOWN, 0);
}
void stepper2_down(){
    led(true);
    gpio_put(S_2_UP, 0);
    gpio_put(S_2_DOWN, 1);
}

void stepper3_up(){
    led(true);
    gpio_put(S_3_UP, 1);
    gpio_put(S_3_DOWN, 0);
}
void stepper3_down(){
    led(true);
    gpio_put(S_3_UP, 0);
    gpio_put(S_3_DOWN, 1);
}

void stepper_idle(){
    led(false);
    gpio_put(S_1_UP, 0);
    gpio_put(S_1_DOWN, 0);
    gpio_put(S_2_UP, 0);
    gpio_put(S_2_DOWN, 0);
    gpio_put(S_3_UP, 0);
    gpio_put(S_3_DOWN, 0);
}

/* Subscriber Callbacks */
void gripperCb(const void * msgin){
    const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
    switch (msg->data)
    {
        case 310:
            gripper_three_close();
            break;
        case 301:
            gripper_three_open();
            break;  
        default:
            idle_gripper();
            break;
    }
}
void stepperCb(const void * msgin){
    const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
    switch (msg->data)
    {
    case 101:
        stepper1_up();
        break;
    case 110:
        stepper1_down();
        break;
    case 201:
        stepper2_up();
        break;    
    default:
        multicore_fifo_push_blocking(msg->data);
        break;
    }
}

/* Core 1 interrupt handler */
void core1_interrupt_handler(){
    while(multicore_fifo_rvalid()){
        int pop_data = multicore_fifo_pop_blocking();
        switch(pop_data){
            case 210:
                stepper2_down();   
                break;
            case 301:
                stepper3_up();
                break;
            case 310:
                stepper3_down();
                break;    
            default:
                stepper_idle();
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

    // Setup Pins for GP i/o
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

	gpio_init(G_3_CLOSE);
    gpio_set_dir(G_3_CLOSE, GPIO_OUT);

	gpio_init(G_3_OPEN);
    gpio_set_dir(G_3_OPEN, GPIO_OUT);

    gpio_init(S_1_UP);
    gpio_set_dir(S_1_UP, GPIO_OUT);
    gpio_init(S_2_UP);
    gpio_set_dir(S_2_UP, GPIO_OUT);
    gpio_init(S_3_UP);
    gpio_set_dir(S_3_UP, GPIO_OUT);

    gpio_init(S_1_DOWN);
    gpio_set_dir(S_1_DOWN, GPIO_OUT);
    gpio_init(S_2_DOWN);
    gpio_set_dir(S_2_DOWN, GPIO_OUT);
    gpio_init(S_3_DOWN);
    gpio_set_dir(S_3_DOWN, GPIO_OUT);
    
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

    //create subscriber - gripper_sub
    rclc_subscription_init_default(
        &gripper_sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        &r2_gripper_subscriber_name);  
    
    //create subscriber - stepper_sub
    rclc_subscription_init_default(
        &stepper_sub,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        &r2_stepper_subscriber_name); 

    rclc_executor_init(&executor, &support.context, 8, &allocator);
    rclc_executor_add_subscription(&executor, &gripper_sub, &gripper_msg, &gripperCb, ON_NEW_DATA); 
    rclc_executor_add_subscription(&executor, &stepper_sub, &stepper_msg, &stepperCb, ON_NEW_DATA);

    //run the executor in loop     
    while (true)
    {
        // spins every 1 ms, 0.001 s, frequency = 100 Hz
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(0.02)); 
    }
    return 0;
}




// #include <stdio.h>
// #include <math.h>

// #include <rcl/rcl.h>
// #include <rcl/error_handling.h>
// #include <rclc/rclc.h>
// #include <rclc/executor.h>
// #include <rmw_microros/rmw_microros.h>
// #include <geometry_msgs/msg/twist.h>
// #include <std_msgs/msg/float32.h>
// #include <std_msgs/msg/int32.h>

// #include "pico/stdlib.h"
// #include "pico_uart_transports.h"
// #include "hardware/gpio.h"
// #include "hardware/irq.h"
// #include "hardware/pwm.h"
// #include "pico/binary_info.h"
// #include "hardware/uart.h"
// #include "tusb.h" 
// #include "pico/multicore.h"

// /* DEFINE */

// #define S_1_UP 2
// #define S_1_DOWN 3
// #define S_2_UP 4
// #define S_2_DOWN 5
// #define S_3_UP 6
// #define S_3_DOWN 7

// #define G_3_OPEN 14
// #define G_3_CLOSE 15

// /* Define Pins of Limit switches */
// //stepper 1
// #define bottom_level1 17
// // #define stepper1_level1 9
// // #define stepper1_level2 10
// // #define stepper1_level3 11
// // #define stepper1_level4 12
// #define stepper1_level5 20

// //setpper 2
// #define bottom_level2 18
// // #define stepper2_level1 0
// // #define stepper2_level2 0
// // #define stepper2_level3 0
// // #define stepper2_level4 0
// #define stepper2_level5 21

// //stepper 3
// #define bottom_level3 16
// // #define stepper3_level1 0
// // #define stepper3_level2 0
// // #define stepper3_level3 0
// // #define stepper3_level4 0
// #define stepper3_level5 19

// const uint LED_PIN = 25;

// /* Define Sub Pub */
// rcl_subscription_t stepper_sub;
// std_msgs__msg__Int32 stepper_msg;
// char r2_stepper_subscriber_name[] = "robot_2_stepper";

// rcl_subscription_t gripper_sub;
// std_msgs__msg__Int32 gripper_msg;
// char r2_gripper_subscriber_name[] = "robot_2_gripper";

// void led(int i){
//     if(i==1){
//         gpio_put(LED_PIN, 1);
//     }
//     else{
//         gpio_put(LED_PIN, 0);
//     }
// }

// void gripper_idle(){
//     gpio_put(G_3_OPEN, 0);
//     gpio_put(G_3_CLOSE, 0);
//     led(0);
// }

// void stepper_idle(){
//     gpio_put(S_1_UP, 0);
//     gpio_put(S_1_DOWN, 0);
//     gpio_put(S_2_UP, 0);
//     gpio_put(S_2_DOWN, 0);
//     gpio_put(S_3_UP, 0);
//     gpio_put(S_3_DOWN, 0);
//     led(0);
// }

// /* dir 1 = up/open, dir 0 = down/close */
// void stepper1(int one_up, int one_down){
//     if(one_up== 1){
//         if(gpio_get(stepper1_level5) !=0){ // if top not pressed 
//             led(1);
//             gpio_put(S_1_DOWN, 0);
//             gpio_put(S_1_UP, 1);
//         }else{
//             stepper_idle();
//         }
//     }else if(one_down == 1){
//         if(gpio_get(bottom_level1) !=0){ // if bottom not pressed
//             led(1);
//             gpio_put(S_1_DOWN, 1);
//             gpio_put(S_1_UP, 0);
//         }else{
//             stepper_idle();
//         }
//     }
//     else{
//         stepper_idle();
//     }
// }

// void stepper2(int two_up, int two_down){
//     if(two_up== 1){
//         if(gpio_get(stepper2_level5) !=0){ // if top not pressed    
//             led(1);
//             gpio_put(S_2_DOWN, 0);
//             gpio_put(S_2_UP, 1);
//         }else{
//             stepper_idle();
//         }
//     }else if(two_down == 1){
//         if(gpio_get(bottom_level2) !=0){ // if bottom not pressed
//             led(1);
//             gpio_put(S_2_DOWN, 1);
//             gpio_put(S_2_UP, 0);
//         }else{
//             stepper_idle();
//         }
//     }
//     else{
//         stepper_idle();
//     }
// }

// void stepper3(int three_up, int three_down){
//     if(three_up== 1){
//         if(gpio_get(stepper3_level5) !=0){ // if top not pressed 
//             led(1);
//             gpio_put(S_3_DOWN, 0);
//             gpio_put(S_3_UP, 1);
//         }else{
//             stepper_idle();
//         }
//     }else if(three_down == 1){
//         if(gpio_get(bottom_level3) !=0){ // if bottom not pressed
//             led(1);
//             gpio_put(S_3_DOWN, 1);
//             gpio_put(S_3_UP, 0);
//         }else{
//             stepper_idle();
//         }
//     }
//     else{
//         stepper_idle();
//     }
// }

// void gripper_three_open(){
//     led(1);
//     gpio_put(G_3_OPEN, 1);
//     gpio_put(G_3_CLOSE, 0);
         
//     sleep_ms(100);
//     gpio_put(G_3_CLOSE, 0);
//     gpio_put(G_3_OPEN, 0);
//     led(0); 
// }
// void gripper_three_close(){
//     led(1);
//     gpio_put(G_3_OPEN, 0);
//     gpio_put(G_3_CLOSE, 1);

//     sleep_ms(100);
//     gpio_put(G_3_OPEN, 0);
//     gpio_put(G_3_CLOSE, 0);
//     led(0);
// }   
// void gripperCb(const void * msgin){
//     const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
//     // led(1);
//     // sleep_ms(100);
//     // led(0);
// }   

// void stepperCb(const void * msgin){
//     const std_msgs__msg__Int32 * msg = (const std_msgs__msg__Int32 *)msgin;
//     led(1);
//     sleep_ms(100);
//     led(0);
// }

// /* Core 1 interrupt handler */
// void core1_irq_handler(){
//     while(multicore_fifo_rvalid()){
//         int pop_data = multicore_fifo_pop_blocking();
//     }    
//     multicore_fifo_clear_irq();
// }
// /* Core 1 entry */
// void core1_entry() {
//     multicore_fifo_clear_irq();
//     irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_irq_handler);
//     irq_set_enabled(SIO_IRQ_PROC1, true);

//     while(1){
//         tight_loop_contents();
//     }
// } 
// /* Core 0 entry*/
// int main() {
//     stdio_init_all();
//     //multicore_launch_core1(core1_entry);

//     // Setup Pins for GP i/o
//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);

//     gpio_init(S_1_UP);
//     gpio_set_dir(S_1_UP, GPIO_OUT);
//     gpio_init(S_2_UP);
//     gpio_set_dir(S_2_UP, GPIO_OUT);
//     gpio_init(S_3_UP);
//     gpio_set_dir(S_3_UP, GPIO_OUT);

//     gpio_init(S_1_DOWN);
//     gpio_set_dir(S_1_DOWN, GPIO_OUT);
//     gpio_init(S_2_DOWN);
//     gpio_set_dir(S_2_DOWN, GPIO_OUT);
//     gpio_init(S_3_DOWN);
//     gpio_set_dir(S_3_DOWN, GPIO_OUT);

//     gpio_init(G_3_OPEN);
//     gpio_set_dir(G_3_OPEN, GPIO_OUT);
//     gpio_init(G_3_CLOSE);
//     gpio_set_dir(G_3_CLOSE, GPIO_OUT);
    
//     //Pins for S1
//     gpio_init(bottom_level1);
//     gpio_set_dir(bottom_level1, false);
//     gpio_pull_up(bottom_level1);
//     // gpio_init(stepper1_level1);
//     // gpio_set_dir(stepper1_level1, false);
//     // gpio_pull_up(stepper1_level1);
//     // gpio_init(stepper1_level2);
//     // gpio_set_dir(stepper1_level2, false);
//     // gpio_pull_up(stepper1_level2);
//     // gpio_init(stepper1_level3);
//     // gpio_set_dir(stepper1_level3, false);
//     // gpio_pull_up(stepper1_level3);
//     // gpio_init(stepper1_level4);
//     // gpio_set_dir(stepper1_level4, false);
//     // gpio_pull_up(stepper1_level4);
//     gpio_init(stepper1_level5);
//     gpio_set_dir(stepper1_level5, false);
//     gpio_pull_up(stepper1_level5);
    
//     //Pins for S2
//     gpio_init(bottom_level2);
//     gpio_set_dir(bottom_level2, false);
//     gpio_pull_up(bottom_level2);
//     // gpio_init(stepper2_level1);
//     // gpio_set_dir(stepper2_level1, false);
//     // gpio_pull_up(stepper2_level1);
//     // gpio_init(stepper2_level2);
//     // gpio_set_dir(stepper2_level2, false);
//     // gpio_pull_up(stepper2_level2);
//     // gpio_init(stepper2_level3);
//     // gpio_set_dir(stepper2_level3, false);
//     // gpio_pull_up(stepper2_level3);
//     // gpio_init(stepper2_level4);
//     // gpio_set_dir(stepper2_level4, false);
//     // gpio_pull_up(stepper2_level4);
//     gpio_init(stepper2_level5);
//     gpio_set_dir(stepper2_level5, false);
//     gpio_pull_up(stepper2_level5);

//     //Pins for S3
//     gpio_init(bottom_level3);
//     gpio_set_dir(bottom_level3, false);
//     gpio_pull_up(bottom_level3);
//     // gpio_init(stepper3_level1);
//     // gpio_set_dir(stepper3_level1, false);
//     // gpio_pull_up(stepper3_level1);
//     // gpio_init(stepper3_level2);
//     // gpio_set_dir(stepper3_level2, false);
//     // gpio_pull_up(stepper3_level2);
//     // gpio_init(stepper3_level3);
//     // gpio_set_dir(stepper3_level3, false);
//     // gpio_pull_up(stepper3_level3);
//     // gpio_init(stepper3_level4);
//     // gpio_set_dir(stepper3_level4, false);
//     // gpio_pull_up(stepper3_level4);
//     gpio_init(stepper3_level5);
//     gpio_set_dir(stepper3_level5, false);
//     gpio_pull_up(stepper3_level5);
    

//     //creating node, allocator, support, executor 
//     rcl_node_t node;
//     rcl_allocator_t allocator;
//     rclc_support_t support;
//     rclc_executor_t executor;

//     allocator = rcl_get_default_allocator();
    
//     // Check if micro-ROS Agent answers to micro-ROS client
//     rmw_uros_set_custom_transport(
//         true,
//         NULL,
//         pico_serial_transport_open,
//         pico_serial_transport_close,
//         pico_serial_transport_write,
//         pico_serial_transport_read
//     );

//     // Wait for agent successful ping for 2 minutes.
//     const int timeout_ms = 1000; 
//     const uint8_t attempts = 120;
//     rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
//     if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

//     //create init_options
//     rclc_support_init(&support, 0, NULL, &allocator);

//     // create node
//     rclc_node_init_default(&node, "cmd_vel_node", "", &support);

//     // create subscriber - stepper_sub
//     rclc_subscription_init_default(
//         &stepper_sub,
//         &node,
//         ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
//         &r2_stepper_subscriber_name); 

//     //create subscriber - gripper_sub
//     rclc_subscription_init_default(
//         &gripper_sub,
//         &node,
//         ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
//         &r2_gripper_subscriber_name);  

//     rclc_executor_init(&executor, &support.context, 10, &allocator);
//     rclc_executor_add_subscription(&executor, &stepper_sub, &stepper_msg, &stepperCb, ON_NEW_DATA);
//     rclc_executor_add_subscription(&executor, &gripper_sub, &gripper_msg, &gripperCb, ON_NEW_DATA); 

//     //run the executor in loop     
//     while (true)
//     {   
//         // spins every 1 ms, 0.001 s, frequency = 100 Hz
//         rclc_executor_spin_some(&executor, RCL_S_TO_NS(1)); 
//     }
//     return 0;
// }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//msg->stepper1_level1, msg->stepper1_level2, msg->stepper1_level3, msg->stepper1_level4, msg->stepper1_level5
// void r2_stepper1_limit_switch_pubCb(rcl_timer_t * timer, int64_t last_call_time)
// {
//     int stepper1_msg[5] = {gpio_get(stepper1_level1), gpio_get(stepper1_level2), 
//         gpio_get(stepper1_level3), gpio_get(stepper1_level4), gpio_get(stepper1_level5)};

//     for(int i=0; i<(sizeof stepper1_msg / sizeof stepper1_msg[0]); i++){
//         if(stepper1_msg[i] != 0){
//             stepper1_limit_switch_msg.stepper1_level[i];
//             //rcl_publish(&stepper1_limit_switch_publisher, &stepper1_limit_switch_msg, NULL);
//             led(1);
//             sleep_ms(500);
//             led(0);
//         }
//     }
// }

/* Unnecessary */
/*
        switch (pop_data)
        {
        case 10101:
            two_up = 1;
            two_down = 0;
            three_up = 1;
            three_down = 0;
            break;
        case 10011:
            two_up = 1;
            two_down = 0;
            three_up = 0;
            three_down = 1;
            break;
        case 10001:
            two_up = 1;
            two_down = 0;
            three_up = 0;
            three_down = 0;
            break;
        case 1101: 
            two_up = 0;
            two_down = 1;
            three_up = 1;
            three_down = 0; 
            break;
        case 1011:
            two_up = 0;
            two_down = 1;
            three_up = 0;
            three_down = 1;
            break;
        case 1001:
            two_up = 0;
            two_down = 1;
            three_up = 0;
            three_down = 0;
            break;
        case 101: 
            two_up = 0;
            two_down = 0;
            three_up = 1;
            three_down = 0;
            break;
        case 11:
            two_up = 0;
            two_down = 0;
            three_up = 0;
            three_down = 1;
            break;
        default:
            break;
        }



const std_msgs__msg__Int32 * state = (const std_msgs__msg__Int32 *)msgin;
    int r_num = state->data;

    switch(r_num)
    {
    case 10010:
        gripper(1,1,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;
    case 10001:
        gripper(1,0,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;

    case 20010:
        gripper(2,1,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;
    case 20001:
        gripper(2,0,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;

    case 30010:
        gripper(3,1,pwm_val); 
        //gpio_put(LED_PIN, 1); 
        break;
    case 30001:
        gripper(3,0,pwm_val);
        //gpio_put(LED_PIN, 1); 
        break;

    case 11000:
        stepper(1,1,pwm_val);
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
    case 11010:
        stepper(1,1,pwm_val);
        gripper(1,1,pwm_val);
         //gpio_put(LED_PIN, 1);    
        break;
    case 11001:
        stepper(1,1,pwm_val);
        gripper(1,0,pwm_val);
        //gpio_put(LED_PIN, 1);
        break;
    case 10110:
        stepper(1,0,pwm_val);
        gripper(1,1,pwm_val); 
        //gpio_put(LED_PIN, 1); 
        break;  
    case 10101:
        stepper(1,0,pwm_val);
        gripper(1,0,pwm_val);  
        //gpio_put(LED_PIN,pwm_val);
        break;  

    case 21010:
        stepper(2,1,pwm_val);
        gripper(2,1,pwm_val);
         //gpio_put(LED_PIN, 1);    
        break;
    case 21001:
        stepper(2,1,pwm_val);
        gripper(2,0,pwm_val);
        //gpio_put(LED_PIN, 1);
        break;
    case 20110:
        stepper(2,0,pwm_val);
        gripper(2,1,pwm_val); 
       //gpio_put(LED_PIN, 1); 
        break;  
    case 20101:
        stepper(2,0,pwm_val);
        gripper(2,0,pwm_val);  
       //gpio_put(LED_PIN,pwm_val);
        break;

    case 31010:
        stepper(3,1,pwm_val);
        gripper(3,1,pwm_val);
       //gpio_put(LED_PIN, 1);    
        break;
    case 31001:
        stepper(3,1,pwm_val);
        gripper(3,0,pwm_val);
       //gpio_put(LED_PIN, 1);
        break;
    case 30110:
        stepper(3,0,pwm_val);
        gripper(3,1,pwm_val); 
        //gpio_put(LED_PIN, 1); 
        break;  
    case 30101:
        stepper(3,0,pwm_val);
        gripper(3,0,pwm_val);  
        //gpio_put(LED_PIN, 1);
        break;

    default:
        gpio_put(LED_PIN, 0); 
        stop();
        break;
    }


///////////////////////////////////////////////////////////
void stepper(int s, int dir, int pwm){
    switch(s){
        case 1:
            if(dir == 1){
                // high s1
                gpio_put(S_1, 1);
                pwm_write(S_1_PWM, pwm);
                gpio_put(LED_PIN, 1);
            }
            else if(dir == 0){
                //low s1
                if(gpio_get(U1_PIN) !=0){
                    gpio_put(S_1, 0);
                    pwm_write(S_1_PWM, pwm);
                    gpio_put(LED_PIN, 1);
                }else {
                    pwm_write(S_1_PWM, 0);
                    gpio_put(LED_PIN, 0);
                }   
            }
            else {
                stop();
            }
            break;
        case 2:
            if(dir == 1){
                // high s2
                gpio_put(S_2, 1);
                pwm_write(S_2_PWM, pwm);
                gpio_put(LED_PIN, 1);
            }
            else if(dir == 0){
                //low s2
                gpio_put(S_2, 0);
                pwm_write(S_2_PWM, pwm);
                gpio_put(LED_PIN, 1); 
            }
            else {
                stop();
                gpio_put(LED_PIN, 0);
            }
            break;
        case 3:
            if(dir == 1){
                // high s3
                gpio_put(S_3, 1);
                pwm_write(S_3_PWM, pwm);
                gpio_put(LED_PIN, 1);
            }
            else if(dir == 0){
                //low s3
                
                    gpio_put(S_3, 0);
                    pwm_write(S_3_PWM, pwm);
                    gpio_put(LED_PIN, 1);
                
            }
            else {
                stop();
                gpio_put(LED_PIN, 0);
            }
            break;
        default:
            stop();
    }
}

void gripper(int g, int dir, int pwm){
    switch(g){
        case 1:
            if(dir == 1){
                // close g1
                gpio_put(G_1, 1);
                gpio_put(G_1_PWM, 0);
                gpio_put(LED_PIN, 1);      
            }
            else if(dir == 0){
                //open g1
                if(gpio_get(R1_PIN) !=0){
                    gpio_put(G_1_PWM, 1);
                    gpio_put(G_1, 0);
                    gpio_put(LED_PIN, 1);
                }else{
                    gpio_put(G_1, 0);
                    gpio_put(G_1_PWM, 0);
                    gpio_put(LED_PIN, 0);
                    sleep_ms(50);
                }
            }
            else {
                gpio_put(G_1, 0);
                gpio_put(G_1_PWM, 0);
                gpio_put(G_2, 0);
                gpio_put(G_2_PWM, 0);
                gpio_put(G_3, 0);
                gpio_put(G_3_PWM, 0);
                gpio_put(LED_PIN, 0);
            }
            break;
        case 2:
            if(dir == 1){
                // close g2
                gpio_put(G_2, 1);
                gpio_put(G_2_PWM, 0);
                gpio_put(LED_PIN, 1);
            }
            else if(dir == 0){
                //open g2
                if(gpio_get(R2_PIN) !=0){
                    gpio_put(G_2_PWM, 1);
                    gpio_put(G_2, 0);
                    gpio_put(LED_PIN, 1);
                }else {
                    gpio_put(G_2, 0);
                    gpio_put(G_2_PWM, 0);
                    gpio_put(LED_PIN, 0);
                    sleep_ms(50);
                }    
            }
            else {
                gpio_put(G_1, 0);
                gpio_put(G_1_PWM, 0);
                gpio_put(G_2, 0);
                gpio_put(G_2_PWM, 0);
                gpio_put(G_3, 0);
                gpio_put(G_3_PWM, 0);
                gpio_put(LED_PIN, 0);
            }
            break;
        case 3:
            if(dir == 1){
                // close g3
                gpio_put(G_3, 1);
                gpio_put(G_3_PWM, 0);
                gpio_put(LED_PIN, 1);
            }
            else if(dir == 0){
                //open g3
                if(gpio_get(R3_PIN) !=0){
                    gpio_put(G_3_PWM, 1);
                    gpio_put(G_3, 0);
                    gpio_put(LED_PIN, 1);
                }else {
                    gpio_put(G_3, 0);
                    gpio_put(G_3_PWM, 0);
                    gpio_put(LED_PIN, 0);
                    sleep_ms(50);
                }   
            }
            else {
                gpio_put(G_1, 0);
                gpio_put(G_1_PWM, 0);
                gpio_put(G_2, 0);
                gpio_put(G_2_PWM, 0);
                gpio_put(G_3, 0);
                gpio_put(G_3_PWM, 0);
                gpio_put(LED_PIN, 0);
            }
            break;
        default:
            gpio_put(G_1, 0);
            gpio_put(G_1_PWM, 0);
            gpio_put(G_2, 0);
            gpio_put(G_2_PWM, 0);
            gpio_put(G_3, 0);
            gpio_put(G_3_PWM, 0);
            gpio_put(LED_PIN, 0);
            break;
    }
}
*/
