#include <Stepper.h>

#include <Servo.h>


//here we will write some motor drivers

//----for Servo
const byte servoMin = 20;
const byte servoMax = 160;
  const byte ClawServoPin = 3;
  const byte  SmallArmServoPin = 6;
  const byte MainArmServoPin = 5;
  Servo MainArmServo;
  Servo SmallArmServo;
  Servo ClawServo;
//---for Stepper motor
#define STEPS_PER_DEGREE  5.688889
#define STEPS_PER_REV 2048
#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11
int step_number = 0;
int currentStep = 0;
int targetStep = 0;
int stepsNeeded = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initialize");
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  //servo code

  MainArmServo.attach(MainArmServoPin);

  SmallArmServo.attach(SmallArmServoPin);

  ClawServo.attach(ClawServoPin);
  delay (1000);
}

void loop() {
  Serial.println("stepper to position");
  // put your main code here, to run repeatedly:
//driveStep(StepperStepsandDirection(20));
  MainArmServo.write(60);
 delay (1000);
}

int StepperStepsandDirection(int degree){
  targetStep =round(degree * STEPS_PER_DEGREE);
  if (targetStep > currentStep  && targetStep <=currentStep+180){
    stepsNeeded = targetStep - currentStep;
    Serial.println(stepsNeeded);
    return stepsNeeded;
  }
  else if (targetStep < currentStep || targetStep > currentStep+180){
    stepsNeeded = -1 * (currentStep + STEPS_PER_REV-targetStep);
    Serial.println(stepsNeeded);
    return stepsNeeded;
  }
  else{
    stepsNeeded = 0;
    Serial.println(stepsNeeded);
    return stepsNeeded;
  }
}

void driveStep (int stepsNeeded){
  if (stepsNeeded > 0){
    //positive direction
    for (int i = 0; i< stepsNeeded; i++){
      Serial.println(currentStep);
      OneStep(true);
      delay(3);
    }
   return;
  }
  else if (stepsNeeded < 0){
    //negative direction
  for (int i = 0; i< abs(stepsNeeded); i++){
    Serial.println(currentStep);
    OneStep(false);
    delay(3);
  }
  return;
}
  else{
    return;
  }
}






void OneStep(bool dir){
    if(dir){
      currentStep++;
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
} 
  }else{
    currentStep--;
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
 
  
} 
  }
step_number++;

  if(step_number > 3){ //to cyclethrough the pin sequence
    step_number = 0;
  }
  if(currentStep >=2048){//keep track of the current position and make sure it's within 0 to 2048
    currentStep =0;
  }
  if (currentStep < 0){
    currentStep =2047;
  }
}
