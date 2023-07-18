#include <Servo.h>//Inputs the library Servo.h
Servo myservo;//Names the library's variable "Servo" to myservo

unsigned long StartTime = 1;
unsigned long Interval = 5000;

const int RELAY_PIN1 = 8;
const int RELAY_PIN2 = 7;

void setup (){
  myservo.attach(9);//The pin where the servo motor is attached on the arduino
  myservo.write(90);//Makes the servo motor stop  

   pinMode(RELAY_PIN1, OUTPUT);
   pinMode(RELAY_PIN2, OUTPUT);
}

void loop()

 {
  if (millis()>StartTime){
    StartTime = millis()+Interval;
    digitalWrite(RELAY_PIN1, HIGH);
    delay(12000);
    digitalWrite(RELAY_PIN1, LOW);
  }

 if (millis()>StartTime){
    StartTime = millis()+Interval;
    digitalWrite(RELAY_PIN2, HIGH);
    delay(12000);
    digitalWrite(RELAY_PIN2, LOW);
  }
  
  myservo.write(45);//Makes the servo motor goes clockwise 14
  delay(7000);//Continue this for 700 millisecond which is approximately equal to one roation
  myservo.write(90);//Makes the servo motor stop
  delay(10000);//Makes the servo motor stop for 86400000 milliseconds which is equal to one day  
}
