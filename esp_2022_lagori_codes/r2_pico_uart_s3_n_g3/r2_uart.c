#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#define UART_ID uart0
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

static int chars_rxed = 0;

#define s3_up 14 
#define s3_down 15

#define g3_open 2
#define g3_close 3

const uint LED_PIN = 25;

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.

#define UART_TX_PIN 0
#define UART_RX_PIN 1
// 1 = close,  0 = open
void gripper_three(int dir){
    if(dir == 1){
        gpio_put(LED_PIN, 1);
        gpio_put(g3_close, 0);
        gpio_put(g3_open, 1);
    }
    else{
        gpio_put(LED_PIN, 1);
        gpio_put(g3_close, 1);
        gpio_put(g3_open, 0);
    }
}
// 1 = close,  0 = open
void stepper_three(int dir){
    if(dir == 1){
        gpio_put(LED_PIN, 1);
        gpio_put(s3_down, 0);
        gpio_put(s3_up, 1);
    }
    else{
        gpio_put(LED_PIN, 1);
        gpio_put(s3_down, 1);
        gpio_put(s3_up, 0);
    }
}
void on_uart_rx() {
    gpio_put(LED_PIN, 1);
    while (uart_is_readable(UART_ID)) {
        gpio_put(LED_PIN, 1);
        // uint8_t data = uart_getc(UART_ID);
	
        // switch (data){
        //     case 100:
        //         // s3 up
        //         stepper_three(1);
        //         break;
        //     case 101:
        //         //s3_down
        //         stepper_three(0);
        //         break;
        //     case 110:
        //         //g3_open
        //         gripper_three(0);
        //         break;
        //     case 111:
        //         //g3_close
        //         gripper_three(1);
        //         break;
        //     case 0:
        //         gpio_put(LED_PIN, 0);
        //         gpio_put(g3_close, 0);
        //         gpio_put(g3_open, 0);
        //         gpio_put(s3_down, 0);
        //         gpio_put(s3_up, 0);
        //         break;
                
        // }
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(s3_up);
    gpio_set_dir(s3_up, GPIO_OUT);

    gpio_init(s3_down);
    gpio_set_dir(s3_down, GPIO_OUT);

    gpio_init(g3_close);
    gpio_set_dir(g3_close, GPIO_OUT);

    gpio_init(g3_open);
    gpio_set_dir(g3_open, GPIO_OUT);

    // Set up our UART with the required speed.
    uart_init(UART_ID, 115200);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Set UART f0 control CTS/RTS, we don't want these, so turn them off
    //uart_set_hw_f0(UART_ID, false, false);

    // Select correct interrupt for the UART we are using
    int UART_IRQ = (UART_ID == uart0) ? UART0_IRQ : UART1_IRQ;
    
    //set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);
}


