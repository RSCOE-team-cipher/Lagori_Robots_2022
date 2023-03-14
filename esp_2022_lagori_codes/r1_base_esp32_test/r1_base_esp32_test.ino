#include <PS4Controller.h>
#include <analogWrite.h>

#define FEEDER_UP 22
#define FEEDER_DOWN 23


#define ANGLE_UP 19 
#define ANGLE_DOWN 21

#define SWEEP_UP 18
#define SWEEP_DOWN 5

#define PWM_ROTOR 14

int LEFT_1 = 32;
int RIGHT_1 = 33;
int LEFT_2 = 25;
int RIGHT_2 = 26;

int LED_BUILTIN = 2;
//int wheel_pwm = 15000;
int rotor_pwm = 255;
int sweep_time = 1000; // 100 ms,  lower the value faster sweep
bool runn;

int current_time = 0

void idle_base() {
    analogWrite(LEFT_1, 0);
    analogWrite(RIGHT_2, 0);
    analogWrite(RIGHT_1, 0);
    analogWrite(LEFT_2, 0);
    digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (RIGHT_1, OUTPUT);
  pinMode (RIGHT_2, OUTPUT);
  pinMode (LEFT_1, OUTPUT);
  pinMode (LEFT_2, OUTPUT);
  pinMode (FEEDER_UP, OUTPUT);
  pinMode (FEEDER_DOWN, OUTPUT);
  pinMode (ANGLE_UP, OUTPUT);
  pinMode (ANGLE_DOWN, OUTPUT);
  pinMode (SWEEP_UP, OUTPUT);
  pinMode (SWEEP_DOWN, OUTPUT);
  pinMode (PWM_ROTOR, OUTPUT);
  PS4.begin("01:01:01:01:01:01");  
  
  Serial.println("Ready.");
}

void velocityCb(float x, float z){
  // base cmd_vel
  if(z>-50 && z<50){
    if (x>-50 && x<50){
      idle_base();
    }
    else{
      if (x>50){
        digitalWrite(LED_BUILTIN, HIGH);
        analogWrite(RIGHT_1, 80);
        analogWrite(LEFT_2, 80);
//        Serial.print(x, " ", z);
      }
      else if(x<-50){
        digitalWrite(LED_BUILTIN, HIGH);
        analogWrite(LEFT_1, 80);
        analogWrite(RIGHT_2, 80);
//        Serial.print(x, " ", z);
      }
    }
  }
  else if(x>-50 && x<50){
    if(z>-50 && z<50){
      idle_base();
    }
    else{
      if(z>50){
        digitalWrite(LED_BUILTIN, HIGH);
        analogWrite(LEFT_1, 50);
        analogWrite(LEFT_2, 50);
//        Serial.println(x, " ", z);
      }
      else if(z<-50){
        digitalWrite(LED_BUILTIN, HIGH);
        analogWrite(RIGHT_1, 50);
        analogWrite(RIGHT_2, 50);
//        Serial.println(x, " ", z);
      }
    }
  }
  else{
    idle_base();
  }
}

void rotors(){
    if(!runn){
        digitalWrite(LED_BUILTIN, HIGH);
        for(int i=0; i<=rotor_pwm; i= i+3){    
            analogWrite(PWM_ROTOR, i);
            delay(10);
        }
        runn = true;
        Serial.println("rotor running");
        delay(300);
    }
    else {
        //stop
        digitalWrite(LED_BUILTIN, LOW);
        for(int i=rotor_pwm; i>=0; i=i-3){
            analogWrite(PWM_ROTOR, i);
            delay(10);
        }
        Serial.println("rotor stop");
        runn = false;
    }  
}

void feeder_up(){
    digitalWrite(FEEDER_UP, 0);
    digitalWrite(FEEDER_DOWN, 1);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("feeder up");
}
void feeder_down(){
    digitalWrite(FEEDER_DOWN, 0);
    digitalWrite(FEEDER_UP, 1);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("feeder down");
}

void angle_down(){
    digitalWrite(ANGLE_UP, LOW);
    digitalWrite(ANGLE_DOWN, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("angle down");

}
void angle_up(){
    digitalWrite(ANGLE_DOWN, LOW);
    digitalWrite(ANGLE_UP, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("angle up");
}

void sweep(){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(SWEEP_UP, LOW);
        digitalWrite(SWEEP_DOWN, HIGH);
        delay(sweep_time);
        
        digitalWrite(SWEEP_UP, LOW);
        digitalWrite(SWEEP_DOWN, LOW);
        // if(gpio_get(SWEEP_SWITCH) != 0){
            
        // }
        delay(50);
        digitalWrite(SWEEP_UP, HIGH);
        digitalWrite(SWEEP_DOWN, LOW);
        delay(sweep_time);
        //go up for sweep time
        digitalWrite(SWEEP_DOWN, LOW);
        digitalWrite(SWEEP_UP, LOW);
        digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  	float x, z;
  	// put your main code here, to run repeatedly:
  	if (PS4.isConnected()){
    	x = PS4.LStickY();
    	z = PS4.RStickX();

    	velocityCb(x, z);

    if(PS4.Square()){
      rotors();
    }

    if(PS4.Circle()){
      sweep();
    }
    
		if(PS4.Triangle()){
			feeder_up();
		}
		else if(!PS4.Triangle()){
			digitalWrite(FEEDER_UP, LOW);
			digitalWrite(FEEDER_DOWN, LOW);
			digitalWrite(LED_BUILTIN, LOW);
			//Serial.println("feeder idle");4
		}
		
		if(PS4.Cross()){
			feeder_down();
		}
		else if(!PS4.Cross()){
		digitalWrite(FEEDER_UP, LOW);
			digitalWrite(FEEDER_DOWN, LOW);
			digitalWrite(LED_BUILTIN, LOW);
			//Serial.println("feeder idle");
		}
		
		if(PS4.Down()){
			angle_down();
		}
		else if(!PS4.Down()){
			digitalWrite(ANGLE_UP, LOW);
			digitalWrite(ANGLE_DOWN, LOW);
			digitalWrite(LED_BUILTIN, LOW);
			//Serial.println("angle idle");
		}

		if(PS4.Up()){
			angle_up();
		}
		else if(!PS4.Up()){
			digitalWrite(ANGLE_UP, LOW);
			digitalWrite(ANGLE_DOWN, LOW);
			digitalWrite(LED_BUILTIN, LOW);
			//Serial.println("angle idle");
		}
  	}
  
}
