# IMU Sensor Data Fusion

This code demonstrates the fusion of gyroscope and accelerometer data from `MPU-6050` Sensor to calculate roll, pitch, and yaw angles using an Inertial Measurement Unit (IMU) sensor. The IMU sensor is connected to an Arduino board, and the sensor readings are processed to determine the orientation angles.

## Dependencies

- Wire library: Used for I2C communication with the IMU sensor.

## Hardware Setup

1. Connect the IMU sensor to the Arduino board using the I2C interface.
2. Ensure that the IMU sensor has the correct address (0x68) and is powered on.
3. Select pins from Arduino board and edit the Software to sync it.
## Code Overview

- Constants:
  - `IMU_ADDRESS`: The address of the IMU sensor.
  - `PWR_MGMT`, `GYRO_CONFIG`, `ACC_CONFIG`, `GYRO_X_out`, `ACC_X_OUT`: Register addresses for configuring the IMU sensor.

- Variables:
  - `Rate_Yaw`, `Rate_Roll`, `Rate_Pitch`: Gyroscope rate values in degrees per second.
  - `Z_ACC_LSB`, `X_ACC_LSB`, `Y_ACC_LSB`: Accelerometer raw data in LSB (Least Significant Bit).
  - `X_ACC`, `Y_ACC`, `Z_ACC`: Accelerometer values in g (gravity).
  - `Z_GYRO`, `X_GYRO`, `Y_GYRO`: Gyroscope's data.
  - `Angle_Roll`, `Angle_Pitch`, `Angle_Yaw`: Roll, pitch, and yaw angles calculated from sensor data.
  - `Previous_Yaw`, `Current_Yaw`: Variables to track previous and current yaw angles.
  - `Previous_Time`, `Current_Time`: Variables to track previous and current time for calculating yaw angle.
  - `alpha`: Weighting factor for filtering yaw angle.

- Functions:
  - `MPU_INIT()`: Initializes the IMU sensor by configuring the power management register.
  - `MPU_GYRO_CONFIG()`: Configures the gyroscope sensitivity of the IMU sensor.
  - `Read_GYRO()`: Reads gyroscope data from the IMU sensor and converts it to degrees per second.
  - `MPU_ACCEL_CONFIG()`: Configures the accelerometer sensitivity of the IMU sensor.
  - `Read_ACCEL()`: Reads accelerometer data from the IMU sensor and converts it to gravitational units (g).
  - `Fusion()`: Performs sensor data fusion to calculate roll, pitch, and yaw angles using gyroscope and accelerometer data.

- `setup()`: Initializes the Wire library, starts serial communication, and configures the IMU sensor.
- `loop()`: Reads gyroscope and accelerometer data, performs sensor fusion, and prints the yaw angle.

## Usage

1. Connect the Arduino board to your computer.
2. Open the Arduino IDE and upload the code to the Arduino board.
3. Open the serial monitor to view the yaw angle readings.
