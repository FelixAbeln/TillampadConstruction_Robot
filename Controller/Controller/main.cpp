/*
 * Controller.cpp
 *
 * Created: 27/04/2019 11:16:11
 * Author : Compf
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "Relay.h"
#include "Servo.h"
#include "LDR.h"

int main(void)
{
	Relay Magnet;
	Magnet.Attatch(0, 'A');
	
	Servo Lift;
	Lift.Attatch(4, 'H');
	Lift.SetPulseWidth(0.00199, 0.00092);
	
	LightDependentResistor BallSensor;
	BallSensor.Attatch(0);
	
    while (1) 
    {
		if (BallSensor.Read() < 0.9)
		{
			Lift.MaxForward();
		}	
		else 
		{
			Lift.Off();
		}
    }
}

