/*
 * Uno2.cpp
 *
 * Created: 16/05/2019 08:54:00
 * Author : Compf
 */ 

#define  F_CPU 16000000

#include <avr/io.h>
#include "Servo.h"
#include <util/delay.h>

Servo Lift;

int main(void)
{
    /* Replace with your application code */
	
	DDRD |= (1 << DDD6);
	PORTD |= (1 << PORTD6);
	
	DDRB |= (1 << DDB1);
	Lift.SetupTimer1();
	
    while (1) 
    {
		Lift.MaxForward();
		_delay_ms(500);
		Lift.Off();
		_delay_ms(500);
    }
}

