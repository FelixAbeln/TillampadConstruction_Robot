/*
 * Controller.cpp
 *
 * Created: 27/04/2019 11:16:11
 * Author : Compf
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRE |= (1 << DDE4);
    while (1) 
    {
		PORTE |= (1 << DDE4);
		_delay_ms(1000);
		PORTE &= ~(1 << DDE4);
		_delay_ms(1000);
    }
}

