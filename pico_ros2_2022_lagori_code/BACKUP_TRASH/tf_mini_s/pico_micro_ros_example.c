#include<stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/uart.h"
#include "tusb.h" // this header file will handle the problem of losing initial output

#include <math.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include <std_msgs/msg/float32.h>
#include "pico_uart_transports.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

rcl_publisher_t publisher;
std_msgs__msg__Float32 msg;

void pubslisherCb(rcl_timer_t * timer, int64_t last_call_time)
{
    rcl_publish(&publisher, &msg, NULL);
    msg.data = 0;
}

const uint LED_PIN = 25;

// which port we want to use uart0 or uart1
#define UART_ID0 uart0
#define BAUD_RATE 115200
#define UART_ID1 uart1

// We are using pins 0 and 1 for uart0 and pins 6 and 7 for uart1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART0_TX_PIN 0 // pin-1
#define UART0_RX_PIN 1 // pin-2

#define UART1_TX_PIN 4 // pin-6
#define UART1_RX_PIN 5 // pin-7

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
union unionLidar Lidar;

//****************************Structure and Union for handling LiDAR Data***********

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
                  //printf("checksum ok\n");
                  lidar->lidar.Dist = lidar->Byte[2] | lidar->Byte[3] << 8;
                  lidar->lidar.Strength = lidar->Byte[4] | lidar->Byte[5] << 8;
                  return 1;
                }
	    //printf("bad checksum %02x != %02x\n",checksum & 0xff, serialChar);
    }
   }
    return 0;
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //******************************************************************
    // add some binary info
    // we need to add pico/binary_info.h for this.
    bi_decl(bi_program_description("This is a program to read from UART!"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));
    // add binary info for uart0 and uart1
    bi_decl(bi_1pin_with_name(UART0_TX_PIN, "pin-0 for uart0 TX"));
    bi_decl(bi_1pin_with_name(UART0_RX_PIN, "pin-1 for uart0 RX"));
    bi_decl(bi_1pin_with_name(UART1_TX_PIN, "pin-5 for uart1 TX"));
    bi_decl(bi_1pin_with_name(UART1_RX_PIN, "pin-6 for uart1 RX"));
    //******************************************************************

    // Set up our UARTs with the required speed.
    uart_init(UART_ID0, BAUD_RATE);
    uart_init(UART_ID1, BAUD_RATE);

    // Set the TX and RX pins by using the function
    // Look at the datasheet for more information on function select
    gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);

    //************************************************************
    cdcd_init();
    printf("waiting for usb host");
    while (!tud_cdc_connected()) {
    printf(".");
    sleep_ms(500);
    }
    
    rmw_uros_set_custom_transport(
        true,
        NULL,
        pico_serial_transport_open,
        pico_serial_transport_close,
        pico_serial_transport_write,
        pico_serial_transport_read
    );
    rcl_timer_t timer;

    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor;
    allocator = rcl_get_default_allocator();

    const int timeout_ms = 1000; 
    const uint8_t attempts = 120;
    rcl_ret_t rett = rmw_uros_ping_agent(timeout_ms, attempts);
    if (rett != RCL_RET_OK){return rett;} // Unreachable agent, exiting program.
    
    rclc_support_init(&support, 0, NULL, &allocator);
    rclc_node_init_default(&node, "cmd_vel_node", "", &support);

    rclc_publisher_init_default(
		&publisher,
		&node,
		ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32),
		"cmd_vel_pub_u1");

    //timer callback for each publisher
	rclc_timer_init_default(
		&timer,
		&support,
		RCL_MS_TO_NS(100),
		pubslisherCb);

    rclc_executor_init(&executor, &support.context, 6, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    msg.data = 0;
    while (true){
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));

        if(isLidar(UART_ID1,&Lidar))
        {
            gpio_put(LED_PIN, 1);
            msg.data = Lidar.lidar.Dist;
        }
    }

}

