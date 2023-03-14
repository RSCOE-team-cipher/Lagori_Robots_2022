//pico libs - included in pico-sdk 
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "tusb.h" 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#include "hardware/timer.h"

#define pin0 0
#define pin1 1
#define pin2 2
#define pin3 3
#define pin4 4
#define pin5 5
#define pin6 6
#define pin7 7
#define pin8 8
#define pin9 9
#define pin10 10
#define pin11 11
#define pin12 12
#define pin13 13

#define limit 15

#define PI 3.14159265
#define pin_a 16
#define pin_b 17
#define pin_sw 18

// led pin for debugging
const uint LED_PIN = 25;

int angle;
int default_angle_value = 90;
int counter = 0;

void set_pin(int pin, bool direction){
    gpio_init(pin);
    gpio_set_dir(pin, direction);
}

void setup(){
    set_pin(pin0, GPIO_OUT);
    set_pin(pin1, GPIO_OUT);
    set_pin(pin2, GPIO_OUT);
    set_pin(pin3, GPIO_OUT);
    set_pin(pin4, GPIO_OUT);
    set_pin(pin5, GPIO_OUT);
    set_pin(pin6, GPIO_OUT);
    set_pin(pin7, GPIO_OUT);
    set_pin(pin8, GPIO_OUT);
    set_pin(pin9, GPIO_OUT);
    set_pin(pin10, GPIO_OUT);
    set_pin(pin11, GPIO_OUT);
    set_pin(pin12, GPIO_OUT);
    set_pin(pin13, GPIO_OUT);

    set_pin(pin_sw, GPIO_IN);
    gpio_disable_pulls(pin_sw);

    set_pin(pin_a,GPIO_IN);
	gpio_disable_pulls(pin_a);

    set_pin(pin_b,GPIO_IN);
	gpio_disable_pulls(pin_b);

    set_pin(limit, GPIO_IN);
    gpio_pull_up(limit);

    gpio_put(pin0, 1);
    gpio_put(pin1, 1);
    gpio_put(pin2, 1);
    gpio_put(pin3, 1);
    gpio_put(pin4, 1);
    gpio_put(pin5, 1);
    gpio_put(pin6, 1);
    gpio_put(pin7, 1);
    gpio_put(pin8, 1);
    gpio_put(pin9, 1);
    gpio_put(pin10, 1);
    gpio_put(pin11, 1);
    gpio_put(pin12, 1);
    gpio_put(pin13, 1);

}
    int num_array[100][14] = {  { 1,1,1,1,1,1,1  ,1,0,0,0,0,0,0 },    // 0
                          { 1,0,0,0,0,0,0,  1,1,1,0,1,1,0 },    // 01
                          { 1,0,0,0,0,0,0,  0,1,0,0,0,0,1 },    // 02
                          { 1,0,0,0,0,0,0,  0,1,0,0,1,0,0 },    // 03
                          { 1,0,0,0,0,0,0,  0,0,1,0,1,1,0 },    // 04
                          { 1,0,0,0,0,0,0,  0,0,0,1,1,0,0 },    // 05
                          { 1,0,0,0,0,0,0,  0,0,0,1,0,0,0 },    // 06
                          { 1,0,0,0,0,0,0,  1,1,0,0,1,1,0 },    // 07
                          { 1,0,0,0,0,0,0,  0,0,0,0,0,0,0 },    // 08
                          { 1,0,0,0,0,0,0,  0,0,0,0,1,1,0 },    // 09
                          { 1,1,1,0,1,1,0,  1,0,0,0,0,0,0 },    // 10
                          { 1,1,1,0,1,1,0,  1,1,1,0,1,1,0 }, // 11
                          { 1,1,1,0,1,1,0,  0,1,0,0,0,0,1 }, //12
                          { 1,1,1,0,1,1,0,  0,1,0,0,1,0,0 }, //13
                          { 1,1,1,0,1,1,0,  0,0,1,0,1,1,0 },//14
                          { 1,1,1,0,1,1,0,  0,0,0,1,1,0,0 },//15
                          { 1,1,1,0,1,1,0,  0,0,0,1,0,0,0 },//16
                          { 1,1,1,0,1,1,0,  1,1,0,0,1,1,0 },//17
                          { 1,1,1,0,1,1,0,  0,0,0,0,0,0,0 },//18
                          { 1,1,1,0,1,1,0,  0,0,0,0,1,1,0 },//19
                          { 0,1,0,0,0,0,1,  1,0,0,0,0,0,0 },//20
                          { 0,1,0,0,0,0,1,  1,1,1,0,1,1,0 },//21
                          { 0,1,0,0,0,0,1,  0,1,0,0,0,0,1 },//22
                          { 0,1,0,0,0,0,1,  0,1,0,0,1,0,0 },//23
                          { 0,1,0,0,0,0,1,  0,0,1,0,1,1,0 },//24
                          { 0,1,0,0,0,0,1,  0,0,0,1,1,0,0 },//25
                          { 0,1,0,0,0,0,1,  0,0,0,1,0,0,0 },//26
                          { 0,1,0,0,0,0,1,  1,1,0,0,1,1,0 },//27
                          { 0,1,0,0,0,0,1,  0,0,0,0,0,0,0 },//28
                          { 0,1,0,0,0,0,1,  0,0,0,0,1,1,0 },//29
                          { 0,1,0,0,1,0,0,  1,0,0,0,0,0,0 },//30
                          { 0,1,0,0,1,0,0,  1,1,1,0,1,1,0 },//31
                          { 0,1,0,0,1,0,0,  0,1,0,0,0,0,1 },//32
                          { 0,1,0,0,1,0,0,  0,1,0,0,1,0,0 },//33
                          { 0,1,0,0,1,0,0,  0,0,1,0,1,1,0 },//34
                          { 0,1,0,0,1,0,0,  0,0,0,1,1,0,0 },//35
                          { 0,1,0,0,1,0,0,  0,0,0,1,0,0,0 },//36
                          { 0,1,0,0,1,0,0,  1,1,0,0,1,1,0 },//37
                          { 0,1,0,0,1,0,0,  0,0,0,0,0,0,0 },//38
                          { 0,1,0,0,1,0,0,  0,0,0,0,1,1,0 },//39
                          { 0,0,1,0,1,1,0,  1,0,0,0,0,0,0 },//40
                          { 0,0,1,0,1,1,0,  1,1,1,0,1,1,0 },//41
                          { 0,0,1,0,1,1,0,  0,1,0,0,0,0,1 },//42
                          { 0,0,1,0,1,1,0,  0,1,0,0,1,0,0 },//43
                          { 0,0,1,0,1,1,0,  0,0,1,0,1,1,0 },//44
                          { 0,0,1,0,1,1,0,  0,0,0,1,1,0,0 },//45
                          { 0,0,1,0,1,1,0,  0,0,0,1,0,0,0 },//46
                          { 0,0,1,0,1,1,0,  1,1,0,0,1,1,0 },//47
                          { 0,0,1,0,1,1,0,  0,0,0,0,0,0,0 },//48
                          { 0,0,1,0,1,1,0,  0,0,0,0,1,1,0 },//49
                          { 0,0,0,1,1,0,0,  1,0,0,0,0,0,0 },//50
                          { 0,0,0,1,1,0,0,  1,1,1,0,1,1,0 },//51
                          { 0,0,0,1,1,0,0,  0,1,0,0,0,0,1 },//52
                          { 0,0,0,1,1,0,0,  0,1,0,0,1,0,0 },//53
                          { 0,0,0,1,1,0,0,  0,0,1,0,1,1,0 },//54
                          { 0,0,0,1,1,0,0,  0,0,0,1,1,0,0 },//55
                          { 0,0,0,1,1,0,0,  0,0,0,1,0,0,0 },//56
                          { 0,0,0,1,1,0,0,  1,1,0,0,1,1,0 },//57
                          { 0,0,0,1,1,0,0,  0,0,0,0,0,0,0 },//58
                          { 0,0,0,1,1,0,0,  0,0,0,0,1,1,0 },//59
                          { 0,0,0,1,0,0,0,  1,0,0,0,0,0,0 },//60
                          { 0,0,0,1,0,0,0,  1,1,1,0,1,1,0 },//61
                          { 0,0,0,1,0,0,0,  0,1,0,0,0,0,1 },//62
                          { 0,0,0,1,0,0,0,  0,1,0,0,1,0,0 },//63
                          { 0,0,0,1,0,0,0,  0,0,1,0,1,1,0 },//64
                          { 0,0,0,1,0,0,0,  0,0,0,1,1,0,0 },//65
                          { 0,0,0,1,0,0,0,  0,0,0,1,0,0,0 },//66
                          { 0,0,0,1,0,0,0,  1,1,0,0,1,1,0 },//67
                          { 0,0,0,1,0,0,0,  0,0,0,0,0,0,0 },//68
                          { 0,0,0,1,0,0,0,  0,0,0,0,1,1,0 },//69
                          { 1,1,0,0,1,1,0,  1,0,0,0,0,0,0 },//70
                          { 1,1,0,0,1,1,0,  1,1,1,0,1,1,0 },//71
                          { 1,1,0,0,1,1,0,  0,1,0,0,0,0,1 },//72
                          { 1,1,0,0,1,1,0,  0,1,0,0,1,0,0 },//73
                          { 1,1,0,0,1,1,0,  0,0,1,0,1,1,0 },//74
                          { 1,1,0,0,1,1,0,  0,0,0,1,1,0,0 },//75
                          { 1,1,0,0,1,1,0,  0,0,0,1,0,0,0 },//76
                          { 1,1,0,0,1,1,0,  1,1,0,0,1,1,0 },//77
                          { 1,1,0,0,1,1,0,  0,0,0,0,0,0,0 },//78
                          { 1,1,0,0,1,1,0,  0,0,0,0,1,1,0 },//79
                          { 0,0,0,0,0,0,0,  1,0,0,0,0,0,0 },//80
                          { 0,0,0,0,0,0,0,  1,1,1,0,1,1,0 },//81
                          { 0,0,0,0,0,0,0,  0,1,0,0,0,0,1 },//82
                          { 0,0,0,0,0,0,0,  0,1,0,0,1,0,0 },//83
                          { 0,0,0,0,0,0,0,  0,0,1,0,1,1,0 },//84
                          { 0,0,0,0,0,0,0,  0,0,0,1,1,0,0 },//85
                          { 0,0,0,0,0,0,0,  0,0,0,1,0,0,0 },//86
                          { 0,0,0,0,0,0,0,  1,1,0,0,1,1,0 },//87
                          { 0,0,0,0,0,0,0,  0,0,0,0,0,0,0 },//88
                          { 0,0,0,0,0,0,0,  0,0,0,0,1,1,0 },//89
                          { 0,0,0,0,1,1,0,  1,0,0,0,0,0,0 },//90
                          { 0,0,0,0,1,1,0,  1,1,1,0,1,1,0 },//91
                          { 0,0,0,0,1,1,0,  0,1,0,0,0,0,1 },//92
                          { 0,0,0,0,1,1,0,  0,1,0,0,1,0,0 },//93
                          { 0,0,0,0,1,1,0,  0,0,1,0,1,1,0 },//94
                          { 0,0,0,0,1,1,0,  0,0,0,1,1,0,0 },//95
                          { 0,0,0,0,1,1,0,  0,0,0,1,0,0,0 },//96
                          { 0,0,0,0,1,1,0,  1,1,0,0,1,1,0 },//97
                          { 0,0,0,0,1,1,0,  0,0,0,0,0,0,0 },//98
                          { 0,0,0,0,1,1,0,  0,0,0,0,1,1,0 },//99
                          };   

    // int num_array[10][7] = {  { 1,0,0,0,0,0,0 },    // 0
    //                       { 1,1,1,0,1,1,0 },    // 1
    //                       { 0,1,0,0,0,0,1 },    //2
    //                       { 0,1,0,0,1,0,0 },    //3
    //                       { 0,0,1,0,1,1,0 },    //4
    //                       { 0,0,0,1,1,0,0 },    //5
    //                       { 0,0,0,1,0,0,0 },    //6
    //                       { 1,1,0,0,1,1,0 },    //7
    //                       { 0,0,0,0,0,0,0 },    //8
    //                       { 0,0,0,0,1,1,0 },    //9

void num_write(int number) 
{
    int pin_disp_1 = 0; //0 - 6
    int pin_disp_2 = 7; // 7 - 13

    for(int j=0; j < 7; j++){
        gpio_put(pin_disp_1, num_array[number][j]);
        pin_disp_1++;
    }
    
    for(int j=7; j < 14; j++){
        gpio_put(pin_disp_2, num_array[number][j]); 
        pin_disp_2++;
    }
}

// Function to concatenate
// two integers into one
int concat(int a, int b, int c)
{
 
    char s1[10];
    char s2[10];
    char s3[10];
 
    // Convert both the integers to string
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
    sprintf(s3, "%d", c);
 
    // Concatenate both strings
    strcat(s1, s2);
    strcat(s1, s3);
 
    // Convert the concatenated string
    // to integer
    int cd = atoi(s1);
 
    // return the formed integer
    return cd;
}

void encoder_callback(uint gpio, uint32_t events) 
{	
    gpio_put(LED_PIN, 1);
	uint32_t gpio_state = 0;

	//gpio_state = (gpio_get_all() >> 10) & 0b0111;  	// get all GPIO them mask out all but bits 10, 11, 12
													// This will need to change to match which GPIO pins are being used.

    gpio_state = concat(gpio_get(pin_a), gpio_get(pin_b), gpio_get(pin_sw));
    

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
            angle = counter;
		}
        //gpio_put(LED_PIN, 1);
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
            angle = counter;
		}
        //gpio_put(LED_PIN, 0);
	}
    
}

int main() {
    stdio_init_all();
    setup();

	
        gpio_set_irq_enabled_with_callback(pin_sw, GPIO_IRQ_EDGE_FALL, true, &encoder_callback);
        gpio_set_irq_enabled(pin_a, GPIO_IRQ_EDGE_FALL, true);
	    gpio_set_irq_enabled(pin_b, GPIO_IRQ_EDGE_FALL, true);

    if(gpio_get(limit) == 0){
            angle = default_angle_value;
            counter = 0;
        }

        num_write(angle);
}


	




