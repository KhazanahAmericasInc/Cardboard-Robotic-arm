#include <SoftwareSerial.h>


//======for user question========
const char question[] = "Please type gcode in the form of x,y,z,claw (1 for open, 0 for closed) and press ENTER";


//=====for user response=========
char inChar[32];
unsigned int index=0;
int GcodeX=0;
int GcodeY=0;
int GcodeZ= 0;
int GcodeClaw = 0; //0 for closed


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.flush();
Serial.println("starting Gcode parser");
Serial.println(question);
inChar[0] = 'e'; //set flag to empty
}

void loop() {

  
  // put your main code here, to run repeatedly:
    getUserResponse();

}


void parse (char tempChar[]){
  Serial.println("Gcode entered are:");
  if(!sscanf(tempChar, "%d,%d,%d, %d", &GcodeX, &GcodeY, &GcodeZ, &GcodeClaw)){
    Serial.println("Wrong format, please try again");
  }
  sscanf(tempChar, "%d,%d,%d,%d", &GcodeX, &GcodeY, &GcodeZ, &GcodeClaw);
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
