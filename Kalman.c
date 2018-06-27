#include "Kalman.h"

void initVars(struct Kalman rpy, float Q_angle, float Q_bias, float R_measure, float angle, float bias. float P[2][2])
{
	rpy.Q_angle = 0.001f;
	rpy.Q_bias = 0.003f;
	rpy.R_measure= 0.03f;
	
	rpy.angle = 0.0f; //Reset the angle
	rpy.bias = 0.0f; // Reset bias
	
	rpy.P[0][0] = 0.0f;
	rpy.P[0][1] = 0.0f;
	rpy.P[1][0] = 0.0f;
	rpy.P[1][1] = 0.0f;
}

//newAngle in degrees, rate in degrees per second, dt in seconds
float getAngle(struct Kalman rpy, float newAngle, float newRate, float dt) 
{
	//PREDICT stage
	/* Step 1: Predict the state ahead */
	rpy.rate = newRate - rpy.bias;
	rpy.angle += dt * rpy.rate;
	
	/* Step 2: Predict error covariance ahead */
	rpy.P[0][0] += dt * (dt * rpy.P[1][1] - rpy.P[0][1] - rpy.P[1][0] + rpy.Q_angle);
	rpy.P[0][1] -= dt*P[1][1];
	rpy.P[1][0] -= dt*P[1][1];
	rpy.P[1][1] += rpy.Q_bias * dt;
	
	//UPDATE stage
	
	/* Step 4: Calculate innovation covariance */
	float S = rpy.P[0][0] + rpy.R_measure; //Estimate error
	
	/* Step 5: Compute Kalman gain */
	float K[2]; // Kalman gain is a 2x1 vector
	K[0] = P[0][0] / S;
	K[1] = P[1][0] / S;
	
	/* Step 3: Compute difference between angle measurement and a priori state*/
	float y = newAngle - rpy.angle; //Angle difference
	
	/* Step 6: Update the a posteriori estimate of current state*/
	rpy.angle += K[0] * y;
	rpy.bias += K[1] * y;
	
	/* Step 7: Update the error covariance matrix*/
	float P00_temp = P[0][0];
	float P01_temp = P[0][1];
	
	P[0][0] -= K[0] * P00_temp;
	P[0][1] -= K[0] * P01_temp;
	P[1][0] -= K[1] * P00_temp;
	P[1][1] -= K[1] * P01_temp;
	
	return rpy.angle;
}



//Calibrate


//main: return roll, pitch, yaw
int main() 
{
	//Initialize structures for all 3 axes
	struct Kalman K_roll;
	struct Kalman K_pitch;
	struct Kalman K_yaw;
	
	//Variables for raw IMU data
	double accX, accY, accZ;
	double gyroX, gyroY, gyroZ;
	double magX, magY, magZ;
	
	//Angles measured with gyroscope only
	double gyroAngleX, gyroAngleY, gyroAngleZ;
	
	//Angles with Kalman filter
	double kalmanAngleX, kalmanAngleY, kalmanAngleZ;
	
	//OPTIONAL Add complementary filter for comparison purposes
	
	return 0;
}
//Roll: Accelerometer and gyro
//Pitch: Accelerometer and gyro
//Yaw: Gyro and magnetometer

//Write corrected kf data onto file
