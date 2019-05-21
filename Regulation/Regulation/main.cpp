/*
 * Regulation.cpp
 *
 * Created: 23/04/2019 15:16:37
 * Author : Felix Abeln
 */ 

#define F_CPU 16000000 

//----------AVR Gnu Header---------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

//----------Custom Headers---------------//
#include "L298N.h"

Ln298n_Motor Motor1, Motor2; 
int isoff;
void OnButton();
int CheckOnButton();
void WaitForMiddleSensor();
void WaitStop(void);
void Bandgape(void);
void Stop(void);
void Turn90Degrees_corner(void);
void Turn90Degrees_T(void);


float speed_lower = 0;
float speed_higher = .4;
int stop_flag = 0;
int Counter = 0;
	


int main(void)
{
	isoff = 1;
	DDRD = 0; // Set entire D-bank to input.
	DDRB |= (1 << DDB5); // Sets the internal LED to output
	DDRB &= ~(1 << DDB4);
	PCICR |= (1 << PCIE0); // Enables the disable/enable interrupt
	PCMSK0 |= (1 << PCINT4); //Enables the enable pin in the interupt mask
	sei();
	DDRD |= (1 << DDD7);
	PORTD |= (1 << PORTD7);
	
	Setup_L298N_PWM();
	Motor1.Attach(1);
	Motor1.SetDirection(2);
	Motor1.Calibrate(.60);
	Motor2.Attach(2);
	Motor2.Calibrate(.70);
	Motor2.SetDirection(2);
	
	OnButton();
	
	while (1)
	{	
		if (!isoff)
		{
			if ((PINC & (1 << PINC4)) || (PINC & (1 << PINC5)))
			{
				stop_flag = 1;
			}
			
			if (stop_flag)
			{
				switch (Counter)
				{
					case 0:Bandgape(); break;
					case 1: Turn90Degrees_corner(); break;
					case 2: Turn90Degrees_T(); break;
					case 3: Stop();
				}
				
				stop_flag = 0;
				Counter ++;
			}
// 			if (PIND & (1 << PIND6) && !stop_flag)
// 			{
// 				Motor1.SetSpeedPercent(1);
// 				Motor2.SetSpeedPercent(1);
// 				
// 			}
			if (PIND & (1 << PIND4) && !stop_flag)
			{
				Motor1.SetSpeedPercent(speed_higher);
				Motor2.SetSpeedPercent(speed_lower);
			}
			else if (PIND & (1 << PIND2) && !stop_flag)
			{
				Motor1.SetSpeedPercent(speed_lower);
				Motor2.SetSpeedPercent(speed_higher);
			}
		}
		else
		{
			Motor1.Off();
			Motor2.Off();
		}
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
	}
	else
	{
		PORTB &= ~(1 << PORTB5);
		isoff = 1;
	}
}
int CheckOnButton()
{
	if (PINB & (1 << PINB4)) {return 1;}
	else {return 0;}
}
void WaitStop(void)
{
	Motor1.Off();
	Motor2.Off();
	_delay_ms(1000);
}
void Bandgape(void)
{
	WaitStop();
	while (!(PINC & (1 << PINC4)))
	{
		Motor2.Off();
		Motor1.SetSpeedPercent(speed_higher);
	}
	while (!(PINC & (1 << PINC5)))
	{
		Motor1.Off();
		Motor2.SetSpeedPercent(speed_higher);
	}
	WaitStop();
	Motor2.SetSpeedPercent(.24);
	Motor1.SetSpeedPercent(.3);
	_delay_ms(500);
	
	int sensor = 0;
	while (!(PIND & (1 << PIND6)))
	{
		if ((PIND & (1 << PIND2)) || (PIND & (PIND4)))
		{
			return;
		}
		if (PINC & (1 << PINC4)){sensor = 1;}
		else if (PINC & (1 << PINC5)){sensor = 2;}
			
		if (sensor == 1)
		{
			Motor1.Off();
			Motor2.SetSpeedPercent(.3);
		}
		else if (sensor == 2)
		{
			Motor2.Off();
			Motor1.SetSpeedPercent(.35);
		}
		
	}
	Motor1.Off();
	Motor2.Off();
	
}
void Turn90Degrees_corner(void)
{
	int count = 0;
	
	WaitStop();
	while (!(PINC & (1 << PINC5)))
	{
		Motor1.Off();
		Motor2.SetSpeedPercent(speed_higher);
	}
	WaitStop();
	
	while (!(PIND & (1 << PIND6)))
	{
		Motor1.Off();
		Motor2.SetSpeedPercent(speed_higher);
	}
}
void Turn90Degrees_T(void)
{
	WaitStop();
	
	Motor1.Off();
	Motor2.SetSpeedPercent(speed_higher);
	_delay_ms(1000);
	
	WaitStop();
	
	while (!(PIND & (1 << PIND6)))
	{
		Motor1.Off();
		Motor2.SetSpeedPercent(speed_higher);
	}
	
}
void Stop(void)
{
	WaitStop();
	while (!(PINC & (1 << PINC4)))
	{
		Motor2.Off();
		Motor1.SetSpeedPercent(speed_higher);
	}
	while (!(PINC & (1 << PINC5)))
	{
		Motor1.Off();
		Motor2.SetSpeedPercent(speed_higher);
	}
	
	WaitStop();
	
	Motor1.SetSpeedPercent(.25);
	Motor2.SetSpeedPercent(.2);
	_delay_ms(2000);
	
	WaitStop();
	PORTD &= ~(1 << PORTD7);
	_delay_ms(500);
	
	Motor2.SetDirection(0);
	Motor1.SetDirection(0);

}