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

int main(void)
{
	Relay Magnet;
	Magnet.Attatch(0, 'A');
	
	Servo Lift;
	Lift.Attatch(5, 'B');
	
    while (1) 
    {
		
    }
}

