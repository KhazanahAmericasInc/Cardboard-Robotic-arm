#include <Servo.h>
const byte servoMin = 20;
const byte servoMax = 160;
  const byte BaseServoPin = 3;
  const byte  SmallArmServoPin = 6;
  const byte MainArmServoPin = 5;

  Servo MainArmServo;
  Servo SmallArmServo;
  Servo BaseServo;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  Serial.println("Initialize");
  
  MainArmServo.attach(MainArmServoPin);

  SmallArmServo.attach(SmallArmServoPin);

  BaseServo.attach(BaseServoPin);
  delay (1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 /*MainArmServo.write(0);
 SmallArmServo.write(60);
 BaseServo.write(90);
delay (1000);
  MainArmServo.write(90);
 SmallArmServo.write(60);
delay (1000);

*/
SmallArmServo.write(0);

delay(1000);


}
