#include <SoftwareSerial.h>

#include <Servo.h>

#include <Stepper.h>

/*
 * switch determine driver control or auton
 * driver mode: potentiometer --> convert --> motor degress
 * autonomous mode: user enter gcode (x,y,z) --> calculate degrees --> 
 * reset button --> return to (0,0,0)
 */
//===For Arm Servo ====
Servo MainArmServo;
const byte MainArmServoPin = 5;
Servo SmallArmServo;
const byte  SmallArmServoPin = 6;
Servo ClawServo;
const byte ClawServoPin = 9;
const byte servoMin = 20;
const byte servoMax = 160;


//====for the potentiometer=====
const byte PotBasePin = A0;
int PotBaseValue;
const byte PotArmPin = A1;
int PotArmValue;
const byte PotSmallArmPin = A2;
int PotSmallArmPin;

//====== for the switch ====
const byte button = 11;
byte buttonstate;

//======for user question========
const char question[] = "Please type gcode in the form of x,y,z and press ENTER";
const unsigned long questionInterval = 5000;
unsigned long prevResponseMillis = 0;
boolean waitingForResponse = false;

//=====for user response=========
const byte buffSize = 31;
char userResponse[buffSize];
const char endMarker = '\r';
byte bytesRecvd = 0;
boolean ackResponse = false;

  
void setup() {
  ArmServo.attach(1); //TODO: servo at pin 1
  smallArmServo.attach(2);

  byte servoPosition = servoMin //set servo range to 20 - 160
  Serial.begin(9600);
  Serial.println("starting up);
  bool driverMode = True; //later set this to switch position
  if (driverMode){
    Serial.println("driver mode enabled, control by turning small arm");
  }
  else{
    Serial.println("Autonomous mode enabled, please enter gcode in x,y,z");
    
  }
}

bool isAuton(){
  if (digitalRead(button) ==HIGH){
    return true;
  }
  return false;
}

void askForUserInput(){
  Serial.println("Autonomous mode enabled, please enter gcode in x,y,z");
  bytesRecvd = 0;
  return;
  
}

void getUserResponse(){
  if (Serial.available()==0){
    return;
  }

  char inChar = Serial.read
  if (inChar != endMarker){
    userResponse[bytesRecvd] inChar;
    bytesRecvd ++;
    if (bytesRecvd == buffSize){
      bytesRecvd = buffSize -1;
    }
  }
  else{
    waitingForResponse = false;
  }
}

void readPotentiometer(){
  
}

void setServoPosition(){
  
}

// inverse kinematics

byte getCSVfields(char input_buffer[])
{
    byte _sentencePos = 0;
    byte _comma_count = 0;
    msg_field[_comma_count] = "";
    while (1)
    {
        if (input_buffer[_sentencePos] == NULL) break;
        if (input_buffer[_sentencePos] == 44) //if it is comma
        {
            _comma_count++;
            msg_field[_comma_count] = "";
            _sentencePos++;
        }
        else
        {
            msg_field[_comma_count] += input_buffer[_sentencePos];
            _sentencePos++;
        }
    }
    return _comma_count + 1;
}

void calculateB(float len, float angle) {
  float dx = len * cos(angle);
  float dy = len * sin(angle);



  
}



void loop() {
  // put your main code here, to run repeatedly:

}

void PID (float Kp, float Ki, float Kd, float error, float past_error,   ){
}
