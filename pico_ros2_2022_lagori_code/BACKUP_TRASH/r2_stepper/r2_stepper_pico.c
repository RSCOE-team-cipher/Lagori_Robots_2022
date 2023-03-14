
#include <stdio.h>
#include <math.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

#include "pico/stdlib.h"
#include "pico_uart_transports.h"

// Custom Msg
#include "lagori_robot_msgs/msg/stepper_msg.h"
#include "lagori_robot_msgs/msg/r2_limit_switch_stepper1.h"
#include "lagori_robot_msgs/msg/r2_limit_switch_stepper2.h"
#include "lagori_robot_msgs/msg/r2_limit_switch_stepper3.h"

// #include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper1__functions.h"
// #include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper2__functions.h"
// #include "lagori_robot_msgs/msg/detail/r2_limit_switch_stepper3__functions.h"
// #include "lagori_robot_msgs/msg/detail/stepper_msg__type_support.h"

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define S_1 1//16
#define S_1_PWM 2 //17 
#define S_2 3//18
#define S_2_PWM 3//19
#define S_3 4//20
#define S_3_PWM 5//21 

/* Define Pins of Limit switches */
//stepper 1
#define bottom_level1   6
#define stepper1_level1 7
#define stepper1_level2 8
#define stepper1_level3 9
#define stepper1_level4 10
#define stepper1_level5 11

//setpper 2
#define bottom_level2 12
#define stepper2_level1 13
#define stepper2_level2 14
#define stepper2_level3 15
#define stepper2_level4 16
#define stepper2_level5 17

//stepper 3
#define bottom_level3 18
#define stepper3_level1 19
#define stepper3_level2 20
#define stepper3_level3 21
#define stepper3_level4 22
#define stepper3_level5 23

const uint LED_PIN = 25;

rcl_subscription_t stepper_sub;
lagori_robot_msgs__msg__StepperMsg stepper_msg;

rcl_publisher_t stepper1_limit_switch_publisher;
rcl_publisher_t stepper2_limit_switch_publisher;
rcl_publisher_t stepper3_limit_switch_publisher;

lagori_robot_msgs__msg__R2LimitSwitchStepper1 stepper1_limit_switch_msg;
lagori_robot_msgs__msg__R2LimitSwitchStepper2 stepper2_limit_switch_msg;
lagori_robot_msgs__msg__R2LimitSwitchStepper3 stepper3_limit_switch_msg;

void led(int i){
    (i==1) ? gpio_put(LED_PIN, 1) : gpio_put(LED_PIN, 0);
}

//msg->stepper1_level1, msg->stepper1_level2, msg->stepper1_level3, msg->stepper1_level4, msg->stepper1_level5
void r2_stepper1_limit_switch_pubCb(rcl_timer_t * timer, int64_t last_call_time)
{
    int stepper1_msg[5] = {gpio_get(stepper1_level1), gpio_get(stepper1_level2), 
        gpio_get(stepper1_level3), gpio_get(stepper1_level4), gpio_get(stepper1_level5)};

    for(int i=0; i<(sizeof stepper1_msg / sizeof stepper1_msg[0]); i++){
        if(stepper1_msg[i] != 0){
            stepper1_limit_switch_msg.stepper1_level[i];
            //rcl_publish(&stepper1_limit_switch_publisher, &stepper1_limit_switch_msg, NULL);
            led(1);
            sleep_ms(500);
            led(0);
        }
    }
}
void r2_stepper2_limit_switch_pubCb(rcl_timer_t * timer, int64_t last_call_time)
{
    int stepper2_msg[5] = {gpio_get(stepper2_level1), gpio_get(stepper2_level2), 
        gpio_get(stepper2_level3), gpio_get(stepper2_level4), gpio_get(stepper2_level5)};

    for(int i=0; i<(sizeof stepper2_msg / sizeof stepper2_msg[0]); i++){
        if(stepper2_msg[i] != 0){
            stepper2_limit_switch_msg.stepper2_level[i];
            //rcl_publish(&stepper2_limit_switch_publisher, &stepper2_limit_switch_msg, NULL);
            led(1);
            sleep_ms(500);
            led(0);
        }
    }
}
void r2_stepper3_limit_switch_pubCb(rcl_timer_t * timer, int64_t last_call_time)
{
    int stepper3_msg[5] = {gpio_get(stepper3_level1), gpio_get(stepper3_level2), 
        gpio_get(stepper3_level3), gpio_get(stepper3_level4), gpio_get(stepper3_level5)};

    for(int i=0; i<(sizeof stepper3_msg / sizeof stepper3_msg[0]); i++){
        if(stepper3_msg[i] != 0){
            stepper3_limit_switch_msg.stepper3_level[i];
            //rcl_publish(&stepper3_limit_switch_publisher,&stepper3_limit_switch_msg, NULL);
            led(1);
            sleep_ms(500);
            led(0);
        }
    }
}

void pwm_write(int pin,int pwm) {
    pwm_clear_irq(pwm_gpio_to_slice_num(pin));
    pwm_set_gpio_level(pin, pwm);
}

// if  (gpio_get(SWITCH) == 0) //NOT PRESSED
// else PRESSED

void idle(){led(0);}

/* dir 1 = up/open, dir 0 = down/close */
void stepper1(int dir){
    //(dir == 1) ? /* up */ : /* down */
    
    if(gpio_get(bottom_level1) == 0){ //NOT PRESSED
        (dir == 1) ? /* up */ : /* down */
        //run stepper
        led(1);
    }
    else {// PRESSED
        //stop stepper
        (dir == 1) ? /* up */ : /* no down */
        led(0);
    }
}
void stepper2(int dir){
    //(dir == 1) ? /* up */ : /* down */
    
    if(gpio_get(bottom_level2) == 0){ //NOT PRESSED
        (dir == 1) ? /* up */ : /* down */
        //run stepper
        led(1);
    }
    else {// PRESSED
        //stop stepper
        (dir == 1) ? /* up */ : /* no down */
        led(0);
    }
}
void stepper3(int dir){
    //(dir == 1) ? /* up */ : /* down */
    
    if(gpio_get(bottom_level3) == 0){ //NOT PRESSED
        (dir == 1) ? /* up */ : /* down */
        //run stepper
        led(1);
    }
    else {// PRESSED
        //stop stepper
        (dir == 1) ? /* up */ : /* no down */
        led(0);
    }
}
/* Subscriber Callbacks */
void stepperCb(const void * msgin){
    const lagori_robot_msgs__msg__StepperMsg * msg = (const lagori_robot_msgs__msg__StepperMsg *)msgin;
    //declare array of 1 2 3 stepper
    //on button press 1, else 0
    
    // int one[2] = {msg->one_up, msg->one_down};
    // int two[2] = {msg->two_up, msg->two_down};
    // int three[2] = {msg->three_up, msg->three_down};

    // (one[0] == 1) ? stepper1(1) : (one[1] == 1) ? stepper1(0) : idle();

    // (two[0] == 1) ? stepper2(1) : (two[1] == 1) ? stepper2(0) : idle();

    // (three[0] == 1) ? stepper3(1) : (three[1] == 1) ? stepper3(0) : idle();
}

int main() {
    stdio_init_all();

    /* Pin Config PWM */
    gpio_set_function(S_1_PWM, GPIO_FUNC_PWM); 
    gpio_set_function(S_2_PWM, GPIO_FUNC_PWM); 
    gpio_set_function(S_3_PWM, GPIO_FUNC_PWM); 

    uint slice_num_1 = pwm_gpio_to_slice_num(S_1_PWM);
    uint slice_num_2 = pwm_gpio_to_slice_num(S_2_PWM);
    uint slice_num_3 = pwm_gpio_to_slice_num(S_3_PWM);

    pwm_clear_irq(slice_num_1);
    pwm_clear_irq(slice_num_2);
    pwm_clear_irq(slice_num_3);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);

    pwm_init(slice_num_1, &config, true);
    pwm_init(slice_num_2, &config, true);
    pwm_init(slice_num_3, &config, true);

    /* PIN CONFIGURATIONS GPIO */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, false);

    //Pins for S1
    gpio_init(bottom_level1);
    gpio_set_dir(bottom_level1, false);
    gpio_init(stepper1_level1);
    gpio_set_dir(stepper1_level1, false);
    gpio_init(stepper1_level2);
    gpio_set_dir(stepper1_level2, false);
    gpio_init(stepper1_level3);
    gpio_set_dir(stepper1_level3, false);
    gpio_init(stepper1_level4);
    gpio_set_dir(stepper1_level4, false);
    gpio_init(stepper1_level5);
    gpio_set_dir(stepper1_level5, false);
    
    //Pins for S2
    gpio_init(bottom_level2);
    gpio_set_dir(bottom_level2, false);
    gpio_init(stepper2_level1);
    gpio_set_dir(stepper2_level1, false);
    gpio_init(stepper2_level2);
    gpio_set_dir(stepper2_level2, false);
    gpio_init(stepper2_level3);
    gpio_set_dir(stepper2_level3, false);
    gpio_init(stepper2_level4);
    gpio_set_dir(stepper2_level4, false);
    gpio_init(stepper2_level5);
    gpio_set_dir(stepper2_level5, false);

    //Pins for S3
    gpio_init(bottom_level3);
    gpio_set_dir(bottom_level3, false);
    gpio_init(stepper3_level1);
    gpio_set_dir(stepper3_level1, false);
    gpio_init(stepper3_level2);
    gpio_set_dir(stepper3_level2, false);
    gpio_init(stepper3_level3);
    gpio_set_dir(stepper3_level3, false);
    gpio_init(stepper3_level4);
    gpio_set_dir(stepper3_level4, false);
    gpio_init(stepper3_level5);
    gpio_set_dir(stepper3_level5, false);


    gpio_init(S_1);
    gpio_set_dir(S_1, GPIO_OUT);
    gpio_init(S_2);
    gpio_set_dir(S_2, GPIO_OUT);
    gpio_init(S_3);
    gpio_set_dir(S_3, GPIO_OUT);

    // NODE TIMER ALLOCATOR SUPPORT EXECUTOR
    rcl_node_t node;
    rcl_allocator_t allocator;
    rclc_support_t support;
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();

    rcl_timer_t stepper1_timer;
    rcl_timer_t stepper2_timer;
    rcl_timer_t stepper3_timer;

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

    //lagori_robot_msgs__msg__StepperMsg__create();
    //lagori_robot_msgs__msg__R2LimitSwitchStepper1__create();
    //lagori_robot_msgs__msg__R2LimitSwitchStepper2__create();
    //lagori_robot_msgs__msg__R2LimitSwitchStepper3__create();


    // // Wait for agent successful ping for 2 minutes.
    // const int timeout_ms = 1000; 
    // const uint8_t attempts = 120;
    // rcl_ret_t ret = rmw_uros_ping_agent(timeout_ms, attempts);

    // if (ret != RCL_RET_OK){return ret;} // Unreachable agent, exiting program.

    const rosidl_message_type_support_t * type_support_1 =
    ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, R2LimitSwitchStepper1);

    const rosidl_message_type_support_t * type_support_2 =
    ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, R2LimitSwitchStepper2);

    const rosidl_message_type_support_t * type_support_3 =
    ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, R2LimitSwitchStepper3);

    const rosidl_message_type_support_t * type_support_stepper =
    ROSIDL_GET_MSG_TYPE_SUPPORT(lagori_robot_msgs, msg, R2LimitSwitchStepper3);

    // create subscriber - stepper_sub
    rclc_subscription_init_default(
        &stepper_sub,
        &node,
        &type_support_stepper,
        "r2_stepper"); 

    /* Stepper Limit Switch Publishers*/

    rclc_node_init_default(&node, "r2_stepper1_limit_switch_publisher", "", &support);
    rclc_node_init_default(&node, "r2_stepper2_limit_switch_publisher", "", &support);
    rclc_node_init_default(&node, "r2_stepper3_limit_switch_publisher", "", &support);

    //create publisher - stepper 1 Limit switch
    rclc_publisher_init_default(
		&stepper1_limit_switch_publisher,
		&node,
		&type_support_1,
		"r2_stepper1_limit_switch_publisher");
    
    //timer callback for stepper 1 publisher
	rclc_timer_init_default(
		&stepper1_timer,
		&support,
		RCL_MS_TO_NS(1),
		r2_stepper1_limit_switch_pubCb);


    //create publisher - stepper 2 Limit switch
    rclc_publisher_init_default(
		&stepper2_limit_switch_publisher,
		&node,
		&type_support_2,
		"r2_stepper2_limit_switch_publisher");

    //timer callback for publisher
	rclc_timer_init_default(
		&stepper2_timer,
		&support,
		RCL_MS_TO_NS(1),
		r2_stepper2_limit_switch_pubCb);  


    //create publisher - stepper 3 Limit switch
    rclc_publisher_init_default(
		&stepper3_limit_switch_publisher,
		&node,
		&type_support_3,
		"r2_stepper3_limit_switch_publisher");

    //timer callback for publisher
	rclc_timer_init_default(
		&stepper3_timer,
		&support,
		RCL_MS_TO_NS(1),
		r2_stepper3_limit_switch_pubCb);          

    rclc_executor_init(&executor, &support.context, 1, &allocator);

    rclc_executor_add_subscription(&executor, &stepper_sub, &stepper_msg, &stepperCb, ON_NEW_DATA);
    rclc_executor_add_timer(&executor, &stepper1_timer);
    rclc_executor_add_timer(&executor, &stepper2_timer);
    rclc_executor_add_timer(&executor, &stepper3_timer);

    //gpio_put(LED_PIN, 1);

    stepper1_limit_switch_msg.stepper1_level[0] = 0;
    stepper1_limit_switch_msg.stepper1_level[1] = 0;
    stepper1_limit_switch_msg.stepper1_level[2] = 0;
    stepper1_limit_switch_msg.stepper1_level[3] = 0;
    stepper1_limit_switch_msg.stepper1_level[4] = 0;

    stepper2_limit_switch_msg.stepper2_level[0] = 0;
    stepper2_limit_switch_msg.stepper2_level[1] = 0;
    stepper2_limit_switch_msg.stepper2_level[2] = 0;
    stepper2_limit_switch_msg.stepper2_level[3] = 0;
    stepper2_limit_switch_msg.stepper2_level[4] = 0;
    
    stepper3_limit_switch_msg.stepper3_level[0] = 0;
    stepper3_limit_switch_msg.stepper3_level[1] = 0;
    stepper3_limit_switch_msg.stepper3_level[2] = 0;
    stepper3_limit_switch_msg.stepper3_level[3] = 0;
    stepper3_limit_switch_msg.stepper3_level[4] = 0;
    
    while (true)
    {
        rclc_executor_spin_some(&executor, RCL_S_TO_NS(1));
    }
    return 0;
}


/* Unnecessary */
/*
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
