/*
 * Regulation.cpp
 *
 * Created: 23/04/2019 15:16:37
 * Author : Felix Abeln
 */ 

#define F_CPU 12000000 

//----------AVR Gnu Header---------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

//----------Custom Headers---------------//
#include "Regulation.h"
#include "L298N.h"
#include "SensorHeader.h"

Ln298n_Motor Motor1, Motor2; 
int isoff;
void OnButton();
int main(void)
{
	isoff = 1;
	DDRD = 0; // Set entire D-bank to input.
	DDRB |= (1 << DDB5); // Sets the internal LED to output
	DDRB &= ~(1 << DDB4);
	PCICR |= (1 << PCIE0); // Enables the disable/enable interrupt
	PCMSK0 |= (1 << PCINT4); //Enables the enable pin in the interupt mask
	PCICR |= (1 << PCIE2); // Enables the pin interrupt 2 vector
	PCMSK2 =  0b01111100; // Enables the interrupt pins in the interrupt mask
	sei();
	
	Setup_L298N_PWM();
	Motor1.Attach(1);
	Motor1.SetDirection(1);
	Motor2.Attach(2);
	Motor2.SetDirection(1);
	
	OnButton();
	
	while (1)
	{	
	}
}

ISR(PCINT2_vect)
{
	if (isoff == 1){return;}
		
	int Sensor_Output = CheckIrSensors();
	int Error = FindError(Sensor_Output);
	float SpeedPercent = GetSpeedPercent(Error);
	
	if (Error < 0)
	{
		Motor2.SetSpeedPercent(SpeedPercent);
		Motor1.SetSpeedPercent(1);
	}
	else
	{
		Motor2.SetSpeedPercent(1);
		Motor1.SetSpeedPercent(SpeedPercent);
	}
}
ISR(PCINT0_vect)
{
	OnButton();	
}

void OnButton()
{
	if (CheckOnButton())
	{
		PORTB |= (1 << PORTB5);
		isoff = 0;
		Motor2.FullSpeed();
		Motor1.FullSpeed();
	}
	else
	{
		PORTB &= ~(1 << PORTB5);
		isoff = 1;
		Motor2.Off();
		Motor1.Off();
	}
}