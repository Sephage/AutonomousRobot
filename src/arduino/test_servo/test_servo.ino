#include <Servo.h> 

Servo myservo;
unsigned long time;

void setup(){
  Serial.begin(9600);
  
  myservo.attach(8);
  myservo.write(0);
  delay(3000);
}

void loop(){
    //Serial.println("start");
    myservo.write(175);
    if(myservo.read() != 175){
      Serial.println(millis());
    }
}
