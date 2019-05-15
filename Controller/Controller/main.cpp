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
#include "IR.h"

int main(void)
{
	Relay Magnet;
	Magnet.Attatch(0, 'A');
	Magnet.RelayOn();
	
	Servo Lift;
	Lift.Attatch(4, 'H');
	Lift.SetPulseWidth(0.00199, 0.00092);
	
	LightDependentResistor BallSensor;
	BallSensor.Attatch(0);
	
	IR_Sensor LeftSensor, RightSensor;
	LeftSensor.Attatch(2, 'A');
	RightSensor.Attatch(3, 'A');
	
	int Lift_is_upp = 0;
	int counter = 0;
	int On_stop_line = 0;
	
	DDRA |= (1 << DDA1); // The Trigger pin on the second Arduino
	PORTA |= (1 << PA1); // Turn on the Linefollower_controller
	
    while (1) 
    {
		/* Checks if the ball is inplace for the lift
		*/
		if (BallSensor.Read() < .9 && !Lift_is_upp)
		{
			_delay_ms(1000);
			Lift.MaxForward();
			_delay_ms(3000);
			Lift.Off();
			Lift_is_upp = 1;
		}
		
		/* Checks for the stop markings on the floor and takes acording actions
		*/
		if (!On_stop_line)
		{
			if (RightSensor.Value() && LeftSensor.Value())
			{
				if (counter == 1)
				{
					counter ++;
					// Do nothing
				}
				if (counter == 2)
				{
					counter ++;
					PORTA &= ~(1 << PA1); // Off with regulator
					Magnet.RelayOff();	
				}
			}
		}
		else
		{
			if (!RightSensor.Value() && !LeftSensor.Value())
			{
				On_stop_line = 0;
			}
		}
    }
}

