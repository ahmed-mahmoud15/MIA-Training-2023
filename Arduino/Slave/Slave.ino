#include <Wire.h>

#define LED 11
#define slaveAddress 10

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Wire.begin(slaveAddress); 
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent (int bytes)
{
  int ValueFromMaster = 0;
  
  while(Wire.available())
  {
    ValueFromMaster = Wire.read();
  }
  
  ValueFromMaster = map(ValueFromMaster, 0, 100, 0, 255);
  analogWrite(LED, ValueFromMaster);

  if (ValueFromMaster == 0)
    Serial.println("NO Message");
  else if(ValueFromMaster == 127)
    Serial.println("Vector Focused");
  else if(ValueFromMaster == 191)
    Serial.println("Vector Distracted");
  else if(ValueFromMaster == 255)
    Serial.println("Glitch");
}