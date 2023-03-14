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
#include <std_msgs/msg/float32.h>

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

/* DEFINE */
#define PI 3.14159265
#define pin_a	10
#define pin_b	11
#define pin_sw	12

/* Configurations */

const uint LED_PIN = 25;

/* Robots Params */

/* Define Sub Pub */
rcl_publisher_t publisher;
std_msgs__msg__Float32 msg;

/* Publisher Callbacks */
int counter = 0;

void publisher_callback(rcl_timer_t * timer, int64_t last_call_time)
{
	rcl_publish(&publisher, &msg, NULL);
}
void encoder_callback(uint gpio, uint32_t events) 
{
	
	uint32_t gpio_state = 0;

	gpio_state = (gpio_get_all() >> 10) & 0b0111;  	// get all GPIO them mask out all but bits 10, 11, 12
													// This will need to change to match which GPIO pins are being used.
	static bool ccw_fall = 0;  //bool used when falling edge is triggered
	static bool cw_fall = 0;
	
	uint8_t enc_value = 0;
	enc_value = (gpio_state & 0x03);

	if (gpio == pin_a) 
	{
		if ((!cw_fall) && (enc_value == 0b10)) // cw_fall is set to TRUE when phase A interrupt is triggered
			cw_fall = 1; 

		if ((ccw_fall) && (enc_value == 0b00)) // if ccw_fall is already set to true from a previous B phase trigger, the ccw event will be triggered 
		{
			cw_fall = 0;
			ccw_fall = 0;
            counter++;
            msg.data = counter;
		}
	}	

	if (gpio == pin_b) 
	{
		if ((!ccw_fall) && (enc_value == 0b01)) //ccw leading edge is true
			ccw_fall = 1;

		if ((cw_fall) && (enc_value == 0b00)) //cw trigger
		{
			cw_fall = 0;
			ccw_fall = 0;
            counter--;
            msg.data = counter;
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

int main() {
    stdio_init_all();

    /* PIN CONFIGURATIONS PWM & GPIO */

    // Setup Pins for GP i/o
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

	// GPIO Setup for Encoder
	gpio_init(pin_sw);				
    gpio_set_dir(pin_sw,GPIO_IN);
	gpio_disable_pulls(pin_sw);

	gpio_init(pin_a);
    gpio_set_dir(pin_a,GPIO_IN);
	gpio_disable_pulls(pin_a);

	gpio_init(pin_b);
    gpio_set_dir(pin_b,GPIO_IN);
	gpio_disable_pulls(pin_b);

	gpio_set_irq_enabled_with_callback(pin_sw, GPIO_IRQ_EDGE_FALL, true, &encoder_callback);
    gpio_set_irq_enabled(pin_a, GPIO_IRQ_EDGE_FALL, true);
	gpio_set_irq_enabled(pin_b, GPIO_IRQ_EDGE_FALL, true);

    //creating node, allocator, support, executor 
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;

    allocator = rcl_get_default_allocator();

    rcl_timer_t timer;
    
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
    rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
        "publisher");

	rclc_timer_init_default(
		&timer,
		&support,
		RCL_MS_TO_NS(1),
		publisher_callback);

    rclc_executor_init(&executor, &support.context, 8, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    msg.data = 0;

    gpio_put(LED_PIN, 1);
    //run the executor in loop     
    while (true)
    {
        // spins every 1 ms, 0.001 s, frequency = 100 Hz
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(1)); 
    }
    return 0;
}


/*Encoder GPIO*/
// GPIO 10 is Encoder phase A,  
// GPIO 11 is Encoder phase B,
// GPIO 12 is the encoder push botton switch.


/* Encoder Callback*/
/*
        "LEVEL_LOW",  // 0x1
        "LEVEL_HIGH", // 0x2
        "EDGE_FALL",  // 0x4
        "EDGE_RISE"   // 0x8
*/




