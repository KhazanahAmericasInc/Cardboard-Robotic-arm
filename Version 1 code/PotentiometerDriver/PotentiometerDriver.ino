
//in this code, we will link potentiometer driver to the arduno and get sensor values


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

void GetPotentiometerState(){
  PotBaseValue = analogRead(PotBasePin);
  PotArmValue = analogRead(PotArmPin);
  PotSmallArmValue = analogRead(PotSmallArmPin);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  PotBaseValue = analogRead(PotBasePin);
  PotArmValue = analogRead(PotArmPin);
  PotSmallArmValue = analogRead(PotSmallArmPin);
 if (digitalRead(button) ==HIGH){
    Serial.println("True");
  }
  else{
    Serial.println("False");
  }
  //Serial.println("PotBase");
  //Serial.println(PotBaseValue);
  delay(1000);
}
