#include <Wire.h>

#define ButtonOne 2
#define ButtonTwo 4
#define slaveAddress 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ButtonOne, INPUT_PULLUP);
  pinMode(ButtonTwo, INPUT_PULLUP);

  Wire.begin();  // start the communication using I2C protocol 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Wire.beginTransmission(slaveAddress);

  int ValueFromButtonOne = digitalRead(ButtonOne);
  int ValueFromButtonTwo = digitalRead(ButtonTwo);
  
  if(ValueFromButtonOne == HIGH && ValueFromButtonTwo == HIGH)
  {
    Wire.write(0);
  }
  else if(ValueFromButtonOne == LOW && ValueFromButtonTwo == HIGH)
  {
    Wire.write(50);
  }
  else if(ValueFromButtonOne == HIGH && ValueFromButtonTwo == LOW)
  {
    Wire.write(75);
  }
  else if(ValueFromButtonOne == LOW && ValueFromButtonTwo == LOW)
  {
    Wire.write(100);
  }
  
  Wire.endTransmission();
  delay(50);

}
