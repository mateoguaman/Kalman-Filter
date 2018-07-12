#include <i2c_t3.h>
#include "LSM9DS1.h"

#define SDAPIN A4
#define SCLPIN A5
#define G_GAIN 0.07 // For 2000 dps/LSB
#define I2C_TIMEOUT 1000 //To detect I2C timeout

#define dt 0.02 //Loop time = 20 ms
byte buff[6];
/*
int accRaw[3];
int gyrRaw[3];
int magRaw[3];
*/
/* IMU Data */
//Maybe this works better?
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double magX, magY, magZ;
int16_t tempRaw;

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
  writeTo(GYR_ADDRESS, CTRL_REG1_G, 0b10111000); //Gyro ODR = 476Hz, 2000 dps, check rate that works best
  writeTo(GYR_ADDRESS, ORIENT_CFG_G, 0b00111000); //Swap orientation, needed?

  //Enable Accelerometer
  writeTo(ACC_ADDRESS, CTRL_REG5_XL, 0b00111000); //z, y, x axes enabled
  writeTo(ACC_ADDRESS, CTRL_REG6_XL, 0b00101000); // +/- 16g, could less range make it better?

  //Enable the magnetometer
  writeTo(MAG_ADDRESS, CTRL_REG1_M, 0b10011100) // Temp compensation enabled,Low power mode mode,80Hz ODR
  writeTo(MAG_ADDRESS, CTRL_REG2_M, 0b01000000);   // +/-12gauss, need this?
  writeTo(MAG_ADDRESS, CTRL_REG3_M, 0b00000000);   // continuos update
  writeTo(MAG_ADDRESS, CTRL_REG4_M, 0b00000000);   // lower power mode for Z axis
  

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

uint8_t writeTo(int device, byte address, byte data) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(data);
  uint_8 return_code = Wire.endTransmission();
  if (return_code) {
    Serial.print(F("writeTo failed: "));
    Serial.println(return_code);
  }
  return return_code;
}

uint_8 readFrom(int device, byte address, int num_bytes, byte buff[]) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(device);
  Wire.write(address);
  uint8_t return_code = Wire.endTransmission(false); //False so it does not release bus
  if (return_code) {
    Serial.print(F("readFrom failed: "));
    Serial.println(return_code);
    return return_code; // See: http://arduino.cc/en/Reference/WireEndTransmission
  }

  Wire.requestFrom(device, num_bytes, (uint8_t)true);

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


