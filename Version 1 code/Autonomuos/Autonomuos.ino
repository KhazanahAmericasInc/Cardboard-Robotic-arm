#include <Servo.h>

#include <SoftwareSerial.h>


#include <math.h>

  const byte BaseServoPin = 3;
  const byte  SmallArmServoPin = 6;
  const byte MainArmServoPin = 5;

  Servo MainArmServo;
  Servo SmallArmServo;
  Servo BaseServo;


//====for the potentiometer=====
const byte PotBasePin = A0;
int PotBaseValue;
const byte PotArmPin = A1;
int PotArmValue;
const byte PotSmallArmPin = A2;
int PotSmallArmValue;

//====== for the switch ====
const byte button = 2;
byte buttonstate;

//======for user question========
const char question[] = "Please type gcode in the form of x,y,z and press ENTER";


//=====for user response=========
char inChar[32];
unsigned int index=0;
int GcodeX=0;
int GcodeY=0;
int GcodeZ= 0;
int GcodeClaw = 0; //0 for closed

//====inverse kinematics====
float smallArmLength = 7.5;
float mainArmLength = 7.7;
int MainArmServoAngle;
int SecondaryArmServoAngle;
int SecondaryArnAngleOffset = 15;
float origin = 0; //which is true for both X, and Y coordinate, (0,0)
float CenterDistance = 0;
float a = 0;
float b = 0;
float h = 0;
float P2X = 0;
float P2Y = 0;
float P3X = 0;
float P3Y = 0;
float distanceP3toOrigin;
float distanceP3toP1; 
float hypoAngle; 


void GetPotentiometerState(){
  PotBaseValue = analogRead(PotBasePin);
  PotArmValue = analogRead(PotArmPin);
  PotSmallArmValue = analogRead(PotSmallArmPin);
}

void parse (char tempChar[]){
  
  if(!sscanf(tempChar, "%d,%d,%d", &GcodeX, &GcodeY, &GcodeZ)){
    Serial.println("Wrong format, please try again");
    return;
  }
  sscanf(tempChar, "%d,%d,%d", &GcodeX, &GcodeY, &GcodeZ);
  Serial.println("Gcode entered are:");
  Serial.println(GcodeX);
  Serial.println(GcodeY);
  Serial.println(GcodeZ);  

}

void getUserResponse() {
  index = 0;
  inChar[0]='e';
  while (Serial.available()){
    delay(10);
   inChar[index] = Serial.read();
    Serial.print(inChar[index]);
    index++;
  }

  
  if (inChar[0]!='e'){
    char temp[index-1];
    Serial.println("You have entered");
    for (int i =0; i< index; i++){ //we will only care about the part that has the index
      temp[i] = inChar[i]; //temp will only have the digits that are important
      Serial.print(temp[i]);
      
    }
    
    parse (temp);//pass string to gcode and store as gcode
  }
  inChar [0] = 'e';
  index = 0; 
  }


void inverseKinematics(int GcodeX, int GcodeY){
  CenterDistance = sqrt(square(GcodeX)+square(GcodeY));
  if (CenterDistance > smallArmLength + mainArmLength){
    Serial.println("out of bound, cannot reach, please enter another gcode");
    return;
  }
  if (CenterDistance < fabs(smallArmLength - mainArmLength)){
    Serial.println("out of bound, to close to the origin, please enter another gcode");
    return;
  }
  if (CenterDistance == 0 && smallArmLength == mainArmLength){ //normally never reach since armlength differ
    Serial.println("out of bound, coincident, please enter another gcode");
    return;
  }
  if (CenterDistance ==0){
    Serial.println("out of bound, gcode at origin, please enter another gcode");
    return; //center distance at origin
  }

  
  a = (square(mainArmLength)- square(smallArmLength)+square(CenterDistance))/2/CenterDistance;
  h = sqrt(square(mainArmLength)-square(a));

  P2X = origin + a*(GcodeX - origin)/CenterDistance;
  P2Y = origin + a*(GcodeY - origin)/CenterDistance;
  P3X = P2X - h*(GcodeY - origin)/CenterDistance;
  P3Y = P2Y + h*(GcodeX - origin)/CenterDistance;

  Serial.print("Intersect found, at ");
  Serial.print(P3X);
  Serial.print(" , ");
  Serial.println(P3Y);

  MainArmServoAngle = 180/M_PI*atan2(P3Y, P3X);
  //to find angle for the 2nd arm, first find distance between p3 to origin and gcode
  //then cosine law it to find angle across from hyponteneuse
  //then angle to change = 180 - angle

  distanceP3toOrigin = sqrt(square(P3X) + square(P3Y));
  distanceP3toP1 = sqrt(square(P3X-GcodeX)+square(P3Y-GcodeY));
  
  hypoAngle = 180/M_PI*acos((square(distanceP3toOrigin) + square(distanceP3toP1) - square(CenterDistance))/2/distanceP3toOrigin/distanceP3toP1);
  Serial.println("Hypoangle is ");
  Serial.println(hypoAngle);
  SecondaryArmServoAngle = hypoAngle - SecondaryArnAngleOffset;
  
  Serial.println("Main Arm Angle is");
  Serial.println(MainArmServoAngle);
  Serial.println("Secondary Arm Angle is");
  Serial.println(SecondaryArmServoAngle);

  motorOutput();
}

void motorOutput(){
   pinMode(BaseServoPin, OUTPUT);
  pinMode(SmallArmServoPin, OUTPUT);
  pinMode( MainArmServoPin, OUTPUT);
  MainArmServo.write(MainArmServoAngle);
  SmallArmServo.write(SecondaryArmServoAngle);
  BaseServo.write(GcodeZ);
delay(3000);
 pinMode(BaseServoPin, INPUT);
  pinMode(SmallArmServoPin, INPUT);
  pinMode( MainArmServoPin, INPUT);
}
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
  Serial.println("Initialize");
  
  MainArmServo.attach(MainArmServoPin);

  SmallArmServo.attach(SmallArmServoPin);

  BaseServo.attach(BaseServoPin);


    // put your setup code here, to run once:
Serial.begin(9600);
Serial.flush();
Serial.println("starting Gcode parser");
Serial.println(question);
inChar[0] = 'e'; //set flag to empty
     pinMode(BaseServoPin, INPUT);
  pinMode(SmallArmServoPin, INPUT);
  pinMode( MainArmServoPin, INPUT);
  delay (1000);
}

void loop() {
  // put your main code here, to run repeatedly:
//turn the servo pin off first
    
    if(Serial.available()>0){
      
    
    getUserResponse();
    inverseKinematics(GcodeX, GcodeY);
    
    }
    delay(30);


}
