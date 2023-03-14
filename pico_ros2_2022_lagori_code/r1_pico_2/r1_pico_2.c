#include <stdio.h>    
#include <math.h>
#include <unistd.h>

//ros2
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

// ros2 custom msg
#include "lagori_robot_msgs/msg/robot_one_controls.h"

//pico
#include "pico/stdlib.h"
#include "pico_uart_transports.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "pico/multicore.h"

/* Ros Pub Sub names */
rcl_subscription_t robot_controls_subscriber;
lagori_robot_msgs__msg__RobotOneControls robot_controls_msgs;
char robot_controls_pub_name[] = "robot_1_controls";

/* Configs */
int sweep_time = 1000; // 100 ms,  lower the value faster sweep

/* DEFINE */
#define FEEDER_UP 4
#define FEEDER_DOWN 5

#define ANGLE_UP 3
#define ANGLE_DOWN 2

#define SWEEP_UP 13
#define SWEEP_DOWN 12

// limit switch pins
#define DOWN_SWITCH 6 
#define UP_SWITCH 7

#define ANGLE_SWITCH 15
#define SWEEP_SWITCH 14

const uint LED_PIN = 25;

/* FUNCTIONS */
void pwm_write(int pin,int pwm) {
    pwm_clear_irq(pwm_gpio_to_slice_num(pin));
    pwm_set_gpio_level(pin, pwm);
}

void led(bool i){
    (i) ? gpio_put(LED_PIN, 1) : gpio_put(LED_PIN, 0);
}

void shoot(){
    led(true);
    feeder_down();//feeder down to initial position (uncomment only if limit switch is present)
    sleep_ms(100);
    sweep();
    sleep_ms(500);
    feeder_up();
    sleep_ms(500);
    led(false);
}
void feeder_idle(){
    gpio_put(FEEDER_UP, 0);
    gpio_put(FEEDER_DOWN, 0);
    led(false);
}
void sweep_idle(){
    gpio_put(SWEEP_DOWN, 0);
    gpio_put(SWEEP_UP, 0);
    led(false);
}
void angle_idle(){
    gpio_put(ANGLE_UP, 0);
    gpio_put(ANGLE_DOWN, 0);
    led(false);
}

void feeder_up(){
    if(gpio_get(UP_SWITCH)!=0){
        gpio_put(FEEDER_UP, 0);
        gpio_put(FEEDER_DOWN, 1);
        led(true);

        // sleep_ms(100);
        // gpio_put(FEEDER_UP, 0);
        // gpio_put(FEEDER_DOWN, 0);
        // led(false);
    }
    else{
        gpio_put(FEEDER_DOWN, 0);
        gpio_put(FEEDER_UP, 0);
        led(false);
        //sleep_ms(50);
    }
}
void feeder_down(){    
    if(gpio_get(DOWN_SWITCH)!=0){
        gpio_put(FEEDER_DOWN, 0);
        gpio_put(FEEDER_UP, 1);
        led(true);

        // sleep_ms(100);
        // gpio_put(FEEDER_UP, 0);
        // gpio_put(FEEDER_DOWN, 0);
        // led(false); 
    }
    else{
        gpio_put(FEEDER_UP, 0);
        gpio_put(FEEDER_DOWN, 0);
        led(false);          
    }
}

void angle_down(){
    if(gpio_get(DOWN_SWITCH)!=0){
        gpio_put(ANGLE_UP, 0);
        gpio_put(ANGLE_DOWN, 1);
        led(true);

        // sleep_ms(100);
        // gpio_put(ANGLE_UP, 0);
        // gpio_put(ANGLE_DOWN, 0);
        // led(false);
    }else{
        gpio_put(ANGLE_UP, 0);
        gpio_put(ANGLE_DOWN, 0);
        led(false);
    }    
}
void angle_up(){
    if(gpio_get(ANGLE_SWITCH)!=0){
        gpio_put(ANGLE_DOWN, 0);
        gpio_put(ANGLE_UP, 1);
        led(true);

        // sleep_ms(100);
        // gpio_put(ANGLE_UP, 0);
        // gpio_put(ANGLE_DOWN, 0);
        // led(false);
    }else{
        gpio_put(ANGLE_UP, 0);
        gpio_put(ANGLE_DOWN, 0);
        led(false);
    }    
}

void sweep(){
        led(true);
        gpio_put(SWEEP_UP, 0);
        gpio_put(SWEEP_DOWN, 1);
        sleep_ms(sweep_time);
        
        gpio_put(SWEEP_UP, 1);
        gpio_put(SWEEP_DOWN, 0);
        sleep_ms(sweep_time);
        //go up for sweep time
        gpio_put(SWEEP_DOWN, 0);
        gpio_put(SWEEP_UP, 0);
        led(false);
}

void r1_controls_callback(const void * msgin){
    const lagori_robot_msgs__msg__RobotOneControls * msg = (const lagori_robot_msgs__msg__RobotOneControls *)msgin;

    while(msg->feeder_up == 1){
        feeder_up();
        break;
    }
    while(msg->feeder_down == 1){
        feeder_down();
        break;
    }
    while(msg->angle_down == 1){
        angle_down();
        break;
    }
    while(msg->angle_up == 1){
        angle_up();
        break;
    }
    while(msg->shoot == 1){
        shoot();
        break;
    }
    while(msg->servo == 1){
        sweep();
        sleep_ms(50);
        break;
    }
    ////////////
    while(msg->feeder_up == 0 && msg->feeder_down == 0){
        feeder_idle();
        break;
    }
    
    while(msg->angle_down == 0 && msg->angle_up == 0){
        angle_idle();
        break;
    }
    while(msg->servo == 0){
        sweep_idle();
        break;
    }
}
/* Core 1 interrupt handler */
void core1_interrupt_handler(){
    while(multicore_fifo_rvalid()){
        sweep();
    }    
    multicore_fifo_clear_irq();
}
/* Core 1 */
void core1_entry() {
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
    irq_set_enabled(SIO_IRQ_PROC1, true);
    while(1){
        tight_loop_contents();
    }
} 
/* Core 0 */
int main() {
    stdio_init_all();
    //multicore_launch_core1(core1_entry);
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(SWEEP_UP);
    gpio_set_dir(SWEEP_UP, GPIO_OUT);

    gpio_init(SWEEP_DOWN);
    gpio_set_dir(SWEEP_DOWN, GPIO_OUT);

    gpio_init(ANGLE_UP);
    gpio_set_dir(ANGLE_UP, GPIO_OUT);
    
    gpio_init(ANGLE_DOWN);
    gpio_set_dir(ANGLE_DOWN, GPIO_OUT);

    gpio_init(FEEDER_UP);
    gpio_set_dir(FEEDER_UP, GPIO_OUT);	
    
    gpio_init(FEEDER_DOWN);
    gpio_set_dir(FEEDER_DOWN, GPIO_OUT);

    //limit switch 
    gpio_init(DOWN_SWITCH);
    gpio_set_dir(DOWN_SWITCH, false);
	gpio_pull_up(DOWN_SWITCH);
	
	gpio_init(UP_SWITCH);
	gpio_set_dir(UP_SWITCH, false);
	gpio_pull_up(UP_SWITCH);

    gpio_init(SWEEP_SWITCH);
    gpio_set_dir(SWEEP_SWITCH, false);
	gpio_pull_up(SWEEP_SWITCH);
	
	gpio_init(ANGLE_SWITCH);
	gpio_set_dir(ANGLE_SWITCH, false);
	gpio_pull_up(ANGLE_SWITCH);

    //Check if micro-ROS Agent answers to micro-ROS client
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

    //Wait for agent successful ping for 2 minutes.
    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;
    rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);
    if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

    //create init_options
    rclc_support_init(&support, 0, NULL, &allocator);
    
    // create node
    rclc_node_init_default(&node, "cmd_vel_node", "", &support);

    // create subscriber - r1_controls
    rclc_subscription_init_default(
        &robot_controls_subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, RobotOneControls),
        &robot_controls_pub_name);

    // create executor
    rclc_executor_init(&executor, &support.context, 4, &allocator);
    rclc_executor_add_subscription(&executor, &robot_controls_subscriber, &robot_controls_msgs, &r1_controls_callback, ON_NEW_DATA);

    while (true){
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(0.01));
    }
    return 0;
}
    // int fd = msg->feeder_down; 
    // int fu = msg->feeder_up;   
    // int ad = msg->angle_down;   
    // int aup = msg->angle_up;
    // int se = msg->servo;
    // int sh = msg->shoot;       

    // (fu == 1)  ? led(1): led(0);//feeder_up() : led(0); //idle();
    // (fd == 1)  ? led(1): led(0);//feeder_down() : led(0); //idle();
    // (ad == 1)  ? led(1): led(0);//angle_down() : led(0); //idle();
    // (aup == 1) ? led(1): led(0);//angle_up() : led(0); //idle();
    // (se == 1)  ? led(1): led(0);//sweep() : false; //idle();
    // (sh == 1)  ? led(1): led(0);//shoot() : false; //idle();
