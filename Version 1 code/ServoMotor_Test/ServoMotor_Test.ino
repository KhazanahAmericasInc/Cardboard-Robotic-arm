#include <Servo.h>


Servo myservo;

void setup() 
{ 
  myservo.attach(6);
  //myservo.write(90);  // set servo to mid-point
  Serial.begin(9600);
} 

void loop() {
 Serial.println("to80 deg");

  
  myservo.write (80);
  delay (2000);
  Serial.println("to90 deg");
  
  myservo.write(90);  // set servo to mid-point
   delay (2000);
   
  } 
