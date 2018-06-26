#ifndef __KALMAN__
#define __KALMAN__

struct Kalman {
	float Q_angle;
	float Q_bias;
	float R_measure;
	
	float angle;
	float bias;
	float rate;
	float P[2][2];
};

//newAngle in degrees, newRate in degrees per second, dt in seconds
float getAngle(float newAngle, float newRate, float dt);
void setAngle(float angle); // Angle in degrees, used to set initial angle
float getRate(); //Return unbiased rate

//Used to tune the Kalman filter:

void setQangle(float Q_angle);

/*
setQbias(float Q_bias)
Default value (0.003f) is in Kalman.cpp
Raise value to follow input more closely, trust it more
Lower this to smooth result of Kalman filter, trust input less
*/

void setQbias(float Q_bias);
void setRmeasure(float R_measure);

float getQangle();
float getQbias();
float getRmeasure();


#endif __KALMAN__