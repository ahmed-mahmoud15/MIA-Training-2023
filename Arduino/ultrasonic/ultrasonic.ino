/*
  i used SEN0008 ultrasonic sensor as it has a wide distance range (from 3 cm to 6 metres) and this is suitable to our problem
   as the dimenseons of the room doesn't exceed 6 metres and it has (+ or -) 0.1 metre error
      https://www.tme.eu/eg/en/details/df-sen0008/distance-sensors/dfrobot/sen0008/
*/

#define TopTrig       2
#define BottomTrig    6
#define RightTrig     4
#define LeftTrig      8

#define TopEcho       3
#define BottomEcho    7
#define RightEcho     5
#define LeftEcho      9

#define width         5
#define hight         6
#define error         0.1

float TopTime = 0;
float TopDist = 0;

float BottomTime = 0;
float BottomDist = 0;

float RightTime = 0;
float RightDist = 0;

float LeftTime = 0;
float LeftDist = 0;

float xCoordinate = 0;
float yCoordinate = 0;

float xGun = -1;
float yGun = -1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(TopTrig, OUTPUT);
  pinMode(BottomTrig, OUTPUT);
  pinMode(RightTrig, OUTPUT);
  pinMode(LeftTrig, OUTPUT);

  pinMode(TopEcho, INPUT);
  pinMode(BottomEcho, INPUT);
  pinMode(RightEcho, INPUT);
  pinMode(LeftEcho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TopTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(TopTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(TopTrig, LOW);
  TopTime    = pulseIn(TopEcho, HIGH);

  digitalWrite(BottomTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(BottomTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(BottomTrig, LOW);
  BottomTime    = pulseIn(BottomEcho, HIGH);

  digitalWrite(RightTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(RightTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(RightTrig, LOW);
  RightTime    = pulseIn(RightEcho, HIGH);

  digitalWrite(LeftTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(LeftTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(LeftTrig, LOW);
  LeftTime    = pulseIn(LeftEcho, HIGH);

  //344 meter per second -> 0.000344 meter per micro second

  TopDist    = TopTime    * 0.00034 / 2;
  BottomDist = BottomTime * 0.00034 / 2;
  RightDist  = RightTime  * 0.00034 / 2;
  LeftDist   = LeftTime   * 0.00034 / 2;
  

  if( ( (LeftDist + RightDist) > (width - error) ) && ( (LeftDist + RightDist) < (width + error) ) )
  {
    xCoordinate = (LeftDist + (width - RightDist) ) / 2.0; 
  }
  else // when sensors catch the gun
  {
    float LostX = width - RightDist - LeftDist; //the distance between gun and the right wall
    xCoordinate = (LeftDist + (width - RightDist - LostX) ) / 2.0; 
    xGun = LeftDist + RightDist;  //approximated value
  }

  if( ( (BottomDist + TopDist) > (hight - error) ) && ( (BottomDist + TopDist) < (hight + error) ) )
  {
    yCoordinate = (BottomDist + (hight - TopDist) ) / 2.0; 
  }
  else // when sensors catch the gun
  {
    float LostY = hight - TopDist - BottomDist; //the distance between gun and the Upper wall
    yCoordinate = (BottomDist + (width - TopDist - LostY) ) / 2.0; 
    yGun = TopDist + BottomDist;  //approximated value
  }


  Serial.print("Robot Coordinates = ( ");
  Serial.print(xCoordinate);
  Serial.print(" , ");
  Serial.print(yCoordinate);
  Serial.println(" )");

  if(xGun == -1 && yGun == -1)
    Serial.println("Can't Localize Gun's absolut Position at this moment");
  else
  {
    Serial.print("Gun Coordinates = ( ");
    Serial.print(xGun);
    Serial.print(" , ");
    Serial.print(yGun);
    Serial.println(" )");
  }
}
