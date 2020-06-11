#include <Servo.h>

Servo smallArmServo;
Servo largeArmServo;
Servo baseServo;
Servo claw;


int smallArmPotValue;
int  largeArmPotValue;
int smallArmPrevPot;
int largeArmPrevPot;
int baseServoPotValue;

const int baseTolerance = 10;
const int smallArmPotPin = A0;
const int smallArmLowerBound = 40;
const int smallArmUpperBound = 150;

const int largeArmPotPin = A1;
const int largeArmLowerBound = 50;
const int largeArmUpperBound = 150;

const int basePotPin = A2;
const int switchPin = 6;
int switchState = 0;

void setup() {
  //Begin serial communication
  Serial.begin(9600);
  
  //set up motors
  smallArmServo.attach(3);
  largeArmServo.attach(11);
  claw.attach(10);
  baseServo.attach(9);
  
  
  //set up sensor pin modes
  pinMode(smallArmPotPin, INPUT);
  pinMode(largeArmPotPin, INPUT);
  pinMode(switchPin, INPUT);
  pinMode(basePotPin, INPUT);
  
  //write motr to current position
  smallArmPrevPot = analogRead(smallArmPotPin);
  largeArmPrevPot = analogRead(largeArmPotPin);
  smallArmPrevPot =  map(smallArmPrevPot, 0, 1023, smallArmLowerBound,smallArmUpperBound);
  largeArmPrevPot = map(largeArmPrevPot, 0, 1023, largeArmLowerBound,largeArmUpperBound);
  smallArmServo.write(smallArmPrevPot);
  delay(20);
  largeArmServo.write(largeArmPrevPot);
  delay(200);
}

void loop() {
  //check claw switch state
  switchState = digitalRead(switchPin);
  if (switchState == HIGH){
    claw.write(0);
    Serial.println("Claw to 0");
    delay(20);
  }
  else{
    claw.write(180);
    Serial.println("Claw to 180");
    delay(20);
  }

  //check base potentiometer value
  pinMode(basePotPin, INPUT);
  baseServoPotValue = analogRead(basePotPin);
  pinMode(basePotPin, OUTPUT);
  baseServoPotValue = map(baseServoPotValue, 0, 1023, 0,180);
  baseServo.write(baseServoPotValue);
  Serial.println("write base servo to");
  Serial.println(baseServoPotValue);
  delay(20);

  //check secondary arm potentiometer value
  pinMode(smallArmPotPin, INPUT);
  smallArmPotValue = analogRead(smallArmPotPin);
  pinMode(smallArmPotPin, OUTPUT);
  smallArmPotValue = map(smallArmPotValue, 0, 1023, smallArmLowerBound,smallArmUpperBound);

  
  Serial.println("small Arm pot:");
  Serial.println(smallArmPotValue);
  delay(20);

  //check primary arm potentiometer value
  pinMode(largeArmPotPin, INPUT);
  largeArmPotValue = analogRead(largeArmPotPin);
  pinMode(largeArmPotPin, OUTPUT);
  largeArmPotValue = map(largeArmPotValue, 0, 1023, largeArmLowerBound,largeArmUpperBound);
  Serial.println("large Arm pot:");
  Serial.println(largeArmPotValue);


  //write motor values
  if (abs(smallArmPrevPot - smallArmPotValue)>20){ //changes too much
    if (smallArmPotValue > smallArmPrevPot){
      smallArmPotValue = smallArmPrevPot + 5;
    }
    else{
      smallArmPotValue = smallArmPrevPot - 5;
    }
  }
  if (abs(largeArmPrevPot - largeArmPotValue)>20){ //changes too much
    if (largeArmPotValue > largeArmPrevPot){
      largeArmPotValue = largeArmPrevPot +5;
    }
    else{
      largeArmPotValue = largeArmPrevPot - 5;
    }
  }

  //update previous potentiometer values
  smallArmPrevPot = smallArmPotValue;
  largeArmPrevPot = largeArmPotValue;
  smallArmServo.write(smallArmPotValue);
  delay(40);
  largeArmServo.write(largeArmPotValue);
  delay(40);
  delay(200);
  
}
