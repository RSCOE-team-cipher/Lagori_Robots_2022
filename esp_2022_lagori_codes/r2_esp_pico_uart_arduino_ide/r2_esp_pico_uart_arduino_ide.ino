#define LED_PIN 25
byte incomingValue;

#define s3_up 14 
#define s3_down 15

#define g3_open 2
#define g3_close 3

void gripper_three(int dir){
    if(dir == 1){
        digitalWrite(LED_PIN, 1);
        digitalWrite(g3_close, 0);
        digitalWrite(g3_open, 1);
    }
    else{
        digitalWrite(LED_PIN, 1);
        digitalWrite(g3_close, 1);
        digitalWrite(g3_open, 0);
    }
}
// 1 = close,  0 = open
void stepper_three(int dir){
    if(dir == 1){
        digitalWrite(LED_PIN, 1);
        digitalWrite(s3_down, 0);
        digitalWrite(s3_up, 1);
    }
    else{
        digitalWrite(LED_PIN, 1);
        digitalWrite(s3_down, 1);
        digitalWrite(s3_up, 0);
    }
}

void setup(){
  Serial.begin(9600);
  Serial1.begin(115200);  
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  if(Serial1.available() > 0){
    incomingValue = Serial1.read();
    delay(5);
    switch (incomingValue){
      case 100:
         // s3 up
         stepper_three(1);
        break;
       case 101:
         //s3_down
         stepper_three(0);
         break;
       case 110:
         //g3_open
         gripper_three(0);
         break;
       case 111:
         //g3_close
         gripper_three(1);
         break;
       case 0:
         digitalWrite(LED_PIN, 0);
         digitalWrite(g3_close, 0);
         digitalWrite(g3_open, 0);
         digitalWrite(s3_down, 0);
         digitalWrite(s3_up, 0);
         break;
                
    }
  }
}
