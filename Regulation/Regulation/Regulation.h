#include "Time.h"

int LastError = 0;
int SumError = 0;
float Kp = 1;
float Ki = 1;
float Kd = 1;

int FindError(int Sensor_Output)
{
	switch (Sensor_Output)
	{
		case 0b00000 : return 0;
		case 0b00100 : return 0;
		case 0b01100 : return 1;
		case 0b01000 : return 2;
		case 0b11000 : return 3;
		case 0b10000 : return 4;
		case 0b00110 : return -1;
		case 0b00010 : return -2;
		case 0b00011 : return -3;
		case 0b00001 : return -4;
		default: return 0;
	}
}

float GetSpeedPercent(int error)
{	
	error = abs(error);
	switch (error)
	{
		case 1 : return 1.0;
		case 2 : return 0.5;
		case 3 : return 0.3;
		case 4 : return 0;
	}
	return 1;
}

/* Reserved For potential future use
int Proprtional(int Error)
{
	return Error;
}
int Intergral(int Error)
{
	int ElapsedTime_count = OCR0A;
	float ElapsedTime = ElapsedTime_count / 12000000;
	
	SumError = SumError + (Error * ElapsedTime);
	return (1 / Ki) * SumError;
}
int Derivative(int Error)
{
	int ElapsedTime_count = OCR0A;
	float ElapsedTime = ElapsedTime_count / 12000000;
	
	float dev = (Error - LastError)/ElapsedTime;
	LastError = Error;
	return dev; 
}
float regulate(int Error)
{
	return Kp * (Proprtional(Error) + Intergral(Error) + Derivative(Error));
}
*/ 