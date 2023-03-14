#include <PS4Controller.h>
#include <analogWrite.h>
#include <HardwareSerial.h>
//#include <SoftwareSerial.h>


#define PI 3.14159265
// free pin 12 13
#define PWM_RIGHT_1 26 
#define PWM_LEFT_1 25

#define PWM_RIGHT_2 27     
#define PWM_LEFT_2 14 

#define PWM_RIGHT_3 32 
#define PWM_LEFT_3 33

//////////////////

// free pin NULL
#define G_1_OPEN 22  
#define G_1_CLOSE 23

#define S_1_UP 19
#define S_1_DOWN 21

#define G_2_OPEN 18
#define G_2_CLOSE 5

#define S_2_UP 15
#define S_2_DOWN 4

#define RXD2 12
#define TXD2 13

// uart to a pico
int s3_up = 100;
int s3_down = 101;
int g3_open = 110;
int g3_close = 111;
int g3_idle = 0;
int s3_idle = 1;

/*#define G_3_OPEN 
#define G_3_CLOSE

#define S_3_UP 
#define S_3_DOWN 
*/
int LED_BUILTIN = 2;

uint32_t u1Pwm, u2Pwm, u3Pwm;

/* Robots Params */
float wheel_radius = 0.1;
float d = 0.36;

/* Configurations */
int PWM_MIN = 10;
int PWMRANGE = 255;
int min_speed = 4;
int max_speed = 1000;

HardwareSerial SerialUART(RXD2, TXD2) ;
void setup() {
  SerialUART.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(S_1_UP, OUTPUT);
  pinMode(S_2_UP, OUTPUT);
  //pinMode(S_3_UP, OUTPUT);

  pinMode(S_1_DOWN, OUTPUT);
  pinMode(S_2_DOWN, OUTPUT);
  //pinMode(S_3_DOWN, OUTPUT);

  pinMode(G_1_OPEN, OUTPUT);
  pinMode(G_2_OPEN, OUTPUT);
  //pinMode(G_3_OPEN, OUTPUT);

  pinMode(G_1_CLOSE, OUTPUT);
  pinMode(G_2_CLOSE, OUTPUT);
  //pinMode(G_3_CLOSE, OUTPUT);

  pinMode(PWM_RIGHT_1, OUTPUT);
  pinMode(PWM_RIGHT_2, OUTPUT);
  pinMode(PWM_RIGHT_3, OUTPUT);
  pinMode(PWM_LEFT_1, OUTPUT);
  pinMode(PWM_LEFT_2, OUTPUT);
  pinMode(PWM_LEFT_3, OUTPUT);
  
  PS4.begin("02:02:02:02:02:02");  
  
  Serial.println("Ready.");
  

}

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

// 1 = close,  0 = open
void gripper_one(int dir){
    if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(G_1_OPEN, LOW);
        digitalWrite(G_1_CLOSE, HIGH);
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(G_1_OPEN, HIGH);
        digitalWrite(G_1_CLOSE, LOW);
    }
}
void gripper_two(int dir){
    if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(G_2_OPEN, LOW);
        digitalWrite(G_2_CLOSE, HIGH);
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(G_2_OPEN, HIGH);
        digitalWrite(G_2_CLOSE, LOW);
    }
}
void gripper_three(int dir){
    if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println(SerialUART.write(g3_close));
       // SerialUART.write(g3_close);
        /*digitalWrite(G_3_OPEN, LOW);
        digitalWrite(G_3_CLOSE, HIGH);*/
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        SerialUART.write(g3_open);
        /*digitalWrite(G_3_OPEN, HIGH);
        digitalWrite(G_3_CLOSE, LOW);*/
    }
}
// 1 = up, 0 = down
void stepper_one(int dir){
  if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(S_1_UP, LOW);
        digitalWrite(S_1_DOWN, HIGH);
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(S_1_UP, HIGH);
        digitalWrite(S_1_DOWN, LOW);
    }
}
void stepper_two(int dir){
  if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(S_2_UP, LOW);
        digitalWrite(S_2_DOWN, HIGH);
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(S_2_UP, HIGH);
        digitalWrite(S_2_DOWN, LOW);
    }
}
void stepper_three(int dir){
  if(dir == 1){
        digitalWrite(LED_BUILTIN, HIGH);
        SerialUART.write(s3_up);
        /*digitalWrite(S_3_UP, LOW);
        digitalWrite(S_3_DOWN, HIGH);*/
    }
    else{
        digitalWrite(LED_BUILTIN, HIGH);
        SerialUART.write(s3_down);
        /*digitalWrite(S_3_UP, HIGH);
        digitalWrite(S_3_DOWN, LOW);*/
    }
}

void velocityCb(float x, float y, float z){
    float u1 = (d*(z) - (y/2) + (x)*sin(PI/3))/wheel_radius;
    float u2 = (d*(z) - (y/2) - (x)*sin(PI/3))/wheel_radius;
    float u3 = (d*(z) + (y))/wheel_radius;

    u1Pwm = mapPwm(u1, PWM_MIN, PWMRANGE);
    u2Pwm = mapPwm(u2, PWM_MIN, PWMRANGE);
    u3Pwm = mapPwm(u3, PWM_MIN, PWMRANGE);
    
    if(u1 != 0){
        if(u1>0){
            analogWrite(PWM_RIGHT_1, u1Pwm);
        }else{
            analogWrite(PWM_LEFT_1, u1Pwm);
        }
    }
    else {
        analogWrite(PWM_RIGHT_1, 0);
        analogWrite(PWM_LEFT_1, 0);
    }

    if(u2 != 0){
        if(u2>0){
            analogWrite(PWM_RIGHT_2, u2Pwm);
        }else{
            analogWrite(PWM_LEFT_2, u2Pwm);
        }
    }
    else {
        analogWrite(PWM_RIGHT_2, 0);
        analogWrite(PWM_LEFT_2, 0);
    }

    if(u3 != 0){
        if(u3>0){
            analogWrite(PWM_RIGHT_3, u3Pwm);
        }else{
            analogWrite(PWM_LEFT_3, u3Pwm);
        }
    }
    else {
        analogWrite(PWM_RIGHT_3, 0);
        analogWrite(PWM_LEFT_3, 0);
    }
    
    
}

void loop() {
    SerialUART.write(0);
    float x, y, z;
    if (PS4.isConnected()){
        x = PS4.LStickY();
        y = PS4.LStickX();
        z = PS4.RStickX();
        
        if(x<10 && x> -10){
            x=0;
        }
        if(y<10 && y> -10){
            y=0;
        }
        if(z<10 && z>-10){
            z=0;
        }
        
        velocityCb(x, y, z);

        // Gripper Stepper 1
        if(PS4.Left() && PS4.Triangle()){
            stepper_one(1);
            Serial.println("stepper one up");
        }else if(PS4.Left() && PS4.Cross()){
            stepper_one(0);
            Serial.println("stepper one down");
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(S_1_UP, LOW);
            digitalWrite(S_1_DOWN, LOW);
        }
        
        if(PS4.Left() && PS4.Square()){
            gripper_one(1);
            Serial.println("gripper one open");
        }else if(PS4.Left() && PS4.Circle()){
            gripper_one(0);
            Serial.println("gripper one close");
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(G_1_OPEN, LOW);
            digitalWrite(G_1_CLOSE, LOW);
        }

        // Gripper Stepper 2
        if(PS4.Up() && PS4.Triangle()){
            stepper_two(1);
            Serial.println("stepper two up");
        }else if(PS4.Up() && PS4.Cross()){
            stepper_two(0);
            Serial.println("stepper two down");
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(S_2_UP, LOW);
            digitalWrite(S_2_DOWN, LOW);
        }
        
        if(PS4.Up() && PS4.Square()){
            gripper_two(1);
            Serial.println("gripper two open");
        }else if(PS4.Up() && PS4.Circle()){
            gripper_two(0);
            Serial.println("gripper two close");
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(G_2_OPEN, LOW);
            digitalWrite(G_2_CLOSE, LOW);
        }

        // UART 2 at a pico / esp32
        // Gripper Stepper 3
        if(PS4.Right() && PS4.Triangle()){
            stepper_three(1);
           
        }else if(PS4.Right() && PS4.Cross()){
            stepper_three(0);
            
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            SerialUART.write(g3_idle);
            /*digitalWrite(S_3_UP, LOW);
            digitalWrite(S_3_DOWN, LOW);*/
        }
        
        if(PS4.Right() && PS4.Square()){
            gripper_three(1);
            
        }else if(PS4.Right() && PS4.Circle()){
            gripper_three(0);
            
        }else{
            digitalWrite(LED_BUILTIN, LOW);
            SerialUART.write(s3_idle);
            /*digitalWrite(G_3_OPEN, LOW);
            digitalWrite(G_3_CLOSE, LOW);*/
        }
 
    }
  
}
