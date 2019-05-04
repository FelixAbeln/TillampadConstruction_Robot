#include "Time.h"

int LastError = 0;
int SumError = 0;
float Kp = 1;
float Ki = 1;
float Kd = 1;

float GetSpeedPercent(int error)
{	
	error = abs(error);
	switch (error)
	{
		case 0 : return 1.0;
		case 2 : return 0.5;
		case 3 : return 0.3;
		case 4 : return 0;
	}
	return 1;
}

/* Reserved For potential future use
*/

int Proprtional(int Error)
{
	return Error;
}
int Intergral(int Error)
{
	SumError = SumError + Error;
	return (1 / Ki) * SumError;
}
int Derivative(int Error)
{	
	float dev = (Error - LastError);
	LastError = Error;
	return dev; 
}
float regulate(int Error)
{
	return Kp * (Proprtional(Error) + Intergral(Error) + Derivative(Error));
}
