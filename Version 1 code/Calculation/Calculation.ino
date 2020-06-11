#include <math.h>
//in this one, we will test caculations
float smallArmLength = 30.0;
float mainArmLength = 26.0;
int MainArmServoAngle;
int SecondaryArmServoAngle;
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
  SecondaryArmServoAngle = 180 - hypoAngle;
  
  Serial.println("Main Arm Angle is");
  Serial.println(MainArmServoAngle);
  Serial.println("Secondary Arm Angle is");
  Serial.println(SecondaryArmServoAngle);

  
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  inverseKinematics(27,15);
delay(10000);
}
