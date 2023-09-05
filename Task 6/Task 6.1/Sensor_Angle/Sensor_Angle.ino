#include <Wire.h>
#include <math.h>
#define PI 3.14159 
#define ACC_SENSITIVE 8192.0
#define GYRO_SENSITIVE 16.4

#define IMU_ADDRESS 0x68  //signal pass reset
#define PWR_MGMT 0x6B     //power managment 1
#define GYRO_CONFIG 0x1B  //Gyro configuration                   
#define ACC_CONFIG 0x1C   //accelration configuration
#define GYRO_X_out 0x43  //Gyro in X direction high               
#define ACC_X_OUT 0x3B    //accelration in X direction High


float Rate_Yaw = 0, Rate_Roll = 0, Rate_Pitch = 0;

float Z_ACC_LSB = 0, X_ACC_LSB = 0, Y_ACC_LSB = 0;

int16_t Z_ACC = 0, X_ACC = 0, Y_ACC = 0;

int16_t Z_GYRO = 0, X_GYRO = 0, Y_GYRO = 0;

float Angle_Roll = 0, Angle_Pitch = 0, Angle_Yaw = 0;

float Previous_Yaw = 0, Current_Yaw = 0;
unsigned long Previous_Time = 0, Current_Time = 0;
float alpha = 0.99;

void MPU_INIT(void)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(PWR_MGMT);
  Wire.write(0x00);
  Wire.endTransmission();
}

void MPU_GYRO_CONFIG(void)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_CONFIG);
  Wire.write(0x18);                     //only 3 and 4 bits will set to maximum  00011000             //+- 2000 deg/s
  Wire.endTransmission();
}

void Read_GYRO(void)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(GYRO_X_out);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS, 6);

  while(Wire.available() < 6);

  X_GYRO = Wire.read() << 8 | Wire.read();
  Y_GYRO = Wire.read() << 8 | Wire.read();
  Z_GYRO = Wire.read() << 8 | Wire.read();

  // convert LSB sensetivity for 2000 dps (page 31 in datasheet)
  Rate_Roll = (float) X_GYRO / GYRO_SENSITIVE;
  Rate_Pitch = (float) Y_GYRO / GYRO_SENSITIVE;
  Rate_Yaw = (float) Z_GYRO / GYRO_SENSITIVE;
}

void MPU_ACCEL_CONFIG(void)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACC_CONFIG);
  Wire.write(0x08);                     //only 3 and 4 bits will set to 4g  00001000             // 4g = 4 * 9.81
  Wire.endTransmission();
}

void Read_ACCEL(void)
{
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(ACC_X_OUT);
  Wire.endTransmission();

  Wire.requestFrom(IMU_ADDRESS, 6);

  while(Wire.available() < 6);

  X_ACC_LSB = Wire.read() << 8 | Wire.read();
  Y_ACC_LSB = Wire.read() << 8 | Wire.read();
  Z_ACC_LSB = Wire.read() << 8 | Wire.read();

  // convert LSB sensetivity for 4g (page 29 in datasheet)
  X_ACC = (float) X_ACC_LSB / ACC_SENSITIVE;
  Y_ACC = (float) Y_ACC_LSB / ACC_SENSITIVE;
  Z_ACC = (float) Z_ACC_LSB / ACC_SENSITIVE;
}

void Fusion(void)
{
  Angle_Roll = atan( Y_ACC / sqrt( X_ACC * X_ACC + Z_ACC * Z_ACC ) ) *  ( 180 / PI );
  Angle_Pitch = - atan( X_ACC / sqrt( Y_ACC * Y_ACC + Z_ACC * Z_ACC ) ) * ( 180 / PI );

  Current_Time = millis();
  float time = (Current_Time - Previous_Time) / 1000.0; // determin time in seconds

  float YAW = Previous_Yaw + (Rate_Yaw * time);

  Angle_Yaw = alpha * (Previous_Yaw + Rate_Yaw * time) + (1 - alpha) * YAW;

  Previous_Yaw = Angle_Yaw;
  Previous_Time = Current_Time;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);  

  MPU_INIT();
  MPU_GYRO_CONFIG();
  MPU_ACCEL_CONFIG();
}

void loop() {
  Read_GYRO();
  Read_ACCEL();

  Fusion();

  Serial.print("Yaw: ");
  Serial.print(Angle_Yaw);
  Serial.println(" degrees");
  delay(50);
}