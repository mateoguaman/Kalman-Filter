#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

Adafruit_9DOF dof = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

int count = 1;
float roll;
float pitch;
float heading;
float accelX;
float accelY;
float accelZ;
float gyroX;
float gyroY;
float gyroZ;
float magX;
float magY;
float magZ;

void initSensors()
{

    accel.enableAutoRange(true);
    if(!accel.begin())
    {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
        while(1);
    }

    mag.enableAutoRange(true);
    if(!mag.begin())
    {
        /* There was a problem detecting the LSM303 ... check your connections */
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while(1);
    }

    gyro.enableAutoRange(true);
    if(!gyro.begin())
    {
        /* There was a problem detecting the L3GD20 ... check your connections */
        Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
        while(1);
    }
}

void setup()
{
    Serial.begin(57600);
    
    initSensors();
    Serial.println("SampleNumber MagX MagY MagZ AccX AccY AccZ GyroX GyroY GyroZ");
}

void loop()
{
    sensors_event_t accel_event;
    sensors_event_t mag_event;
    sensors_event_t gyro_event;
    sensors_vec_t orientation;
    
    accel.getEvent(&accel_event);
    accelX = accel_event.acceleration.x;
    accelY = accel_event.acceleration.y;
    accelZ = accel_event.acceleration.z;
    
    gyro.getEvent(&gyro_event);
    gyroX = gyro_event.gyro.x;
    gyroY = gyro_event.gyro.y;
    gyroZ = gyro_event.gyro.z;
    
    mag.getEvent(&mag_event);
    magX = mag_event.magnetic.x;
    magY = mag_event.magnetic.y;
    magZ = mag_event.magnetic.z;
    
    if (dof.accelGetOrientation(&accel_event, &orientation))
    {
        roll = orientation.roll;
        pitch = orientation.pitch;
    }
    
    if (dof.magGetOrientation(SENSOR_AXIS_Z, &mag_event, &orientation))
    {
        heading = orientation.heading;
    }

    Serial.print(count);
    Serial.print(" ");
    Serial.print(magX);
    Serial.print(" ");
    Serial.print(magY);
    Serial.print(" ");
    Serial.print(magZ);
    Serial.print(" ");
    Serial.print(accelX);
    Serial.print(" ");
    Serial.print(accelY);
    Serial.print(" ");
    Serial.print(accelZ);
    Serial.print(" ");
    Serial.print(gyroX);
    Serial.print(" ");
    Serial.print(gyroY);
    Serial.print(" ");
    Serial.println(gyroZ);
    count = count + 1;
    
}


