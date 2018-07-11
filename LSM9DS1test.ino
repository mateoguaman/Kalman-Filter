#include <i2c_t3.h>
#include "LSM9DS1.h"

#define SDAPIN A4
#define SCLPIN A5
#define G_GAIN 0.07 // For 2000 dps/LSB

#define dt 0.02 //Loop time = 20 ms
byte buff[6];
int accRaw[3];
int gyrRaw[3];
int magRaw[3];
float rate_gyr_x = 0.0; //[deg/s]
float rate_gyr_y = 0.0; //[deg/s]
float rate_gyr_z = 0.0; //[deg/s] 
float gyroXangle = 0.0;
float gyroYangle = 0.0;
float gyroZangle = 0.0;
float accXangle = 0.0;
float accYangle = 0.0;
float kalXangle = 0.0;
float kalYangle = 0.0;
float kalZangle = 0.0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(400000); //Set I2C bus speed to 400kHz
  Serial.begin(115200);

  //Enable Gyro
  writeTo(GYR_ADDRESS, CTRL_REG4, 0b00111000); //z, y, x axes enabled
  writeTo(GYR_ADDRESS, CTRL_REG1_G, 0b10111000); //Gyro ODR = 476Hz, 2000 dps
  writeTo(GYR_ADDRESS, ORIENT_CFG_G, 0b00111000); //Swap orientation, needed?

  //Enable Accelerometer
  writeTo(ACC_ADDRESS, CTRL_REG5_XL, 0b00111000); //z, y, x axes enabled
  writeTo(ACC_ADDRESS, CTRL_REG6_XL, 0b00101000); // +/- 16g

  //Enable the magnetometer
  writeTo(MAG_ADDRESS, CTRL_REG1_M, 0b10011100) // Temp compensation enabled,Low power mode mode,80Hz ODR
  writeTo(MAG_ADDRESS, CTRL_REG2_M, 0b01000000);   // +/-12gauss
  writeTo(MAG_ADDRESS, CTRL_REG3_M, 0b00000000);   // continuos update
  writeTo(MAG_ADDRESS, CTRL_REG4_M, 0b00000000);   // lower power mode for Z axis
  

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void writeTo(int device, byte address, byte data) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

void readFrom(int device, byte address, int num_bytes, byte buff[]) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();

  Wire.beginTransmission(device);
  Wire.requestFrom(device, num_bytes);

  int i = 0;
  while(Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }

  Wire.endTransmission();
}

void readACC(byte buff[]) {
  readFrom(ACC_ADDRESS, 0x80 | OUT_X_L_XL, 6, buff);
} 
 
void readMAG(byte buff[]) {
  readFrom(MAG_ADDRESS, 0x80 | OUT_X_L_M, 6, buff);
}

void readGYR(byte buff[]) {
  readFrom(GYR_ADDRESS, 0x80 | OUT_X_L_G, 6, buff);
}

//TODO
void calibrate(){
}
}


