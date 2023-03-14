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

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

/* DEFINE */
#define PI 3.14159265
#define ENA 2               
#define ENB 3               
               
#define IN_1 0              
#define IN_2 1               


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


/* Subscriber Callbacks */
void velocityCb(const void * msgin){
    const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;

    float u1 = (d*(msg->angular.z) - (msg->linear.y/2) + (msg->linear.x)*sin(PI/3))/wheel_radius;
    float u2 = (d*(msg->angular.z) - (msg->linear.y/2) - (msg->linear.x)*sin(PI/3))/wheel_radius;

    // Then map those values to PWM intensities. PWMRANGE = full speed, while PWM_MIN = the minimal amount of power
    u1Pwm = mapPwm(u1, PWM_MIN, PWMRANGE);
    u2Pwm = mapPwm(u2, PWM_MIN, PWMRANGE);
  

    // Set direction pins and PWM
    gpio_put(IN_1, ((u1>0) ? 0 : 1)); 
    pwm_write(ENA, u1Pwm);
    gpio_put(IN_2, ((u2>0) ? 1 : 0)); 
    pwm_write(ENB, u2Pwm);

    
}


int main() {
    stdio_init_all();

    /* PIN CONFIGURATIONS PWM & GPIO */
    gpio_set_function(ENA, GPIO_FUNC_PWM);
    gpio_set_function(ENB, GPIO_FUNC_PWM);

    uint slice_num_1 = pwm_gpio_to_slice_num(ENA);
    uint slice_num_2 = pwm_gpio_to_slice_num(ENB);
 
    pwm_clear_irq(slice_num_1);
    pwm_clear_irq(slice_num_2);
  
    pwm_set_irq_enabled(slice_num_1, true);
    pwm_set_irq_enabled(slice_num_2, true);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);

    // Setup Pins for PWM
    pwm_init(slice_num_1, &config, true);
    pwm_init(slice_num_2, &config, true);

    // Setup Pins for GP i/o
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_init(IN_1);
    gpio_set_dir(IN_1, GPIO_OUT);
    gpio_init(IN_2);
    gpio_set_dir(IN_2, GPIO_OUT);
   
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
        "cmd_vel");

 

    rclc_executor_init(&executor, &support.context, 8, &allocator);
    rclc_executor_add_subscription(&executor, &cmd_vel_sub, &cmd_vel_msg, &velocityCb, ON_NEW_DATA);  

    gpio_put(LED_PIN, 1);   
    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(1)); 
    }
    return 0;
}



