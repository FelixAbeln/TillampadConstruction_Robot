/*
 * Construction.c
 *
 * Created: 03/04/2019 12:00:01
 * Author : Group 1
 */ 

#define  F_CPU 16000000 // sets the Clock speed of an Arduino for all assets (The same for all Arduinos)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Ultrasound_distance.h>


int main(void)
{
	/* Replace with your application code */
	DDRB |= (1 << DDB5);
	sei();
	Setup_16bit_timer_ICU();

	while (1)
	{ 
		if (InCM(Measure_Distance())  > 200)
		{
			PORTB |= (1 << PORTB5);
		}
		else
		{
			PORTB &= ~(1 << PORTB5);
		}
		_delay_ms(100);
	}
}

ISR(TIMER1_CAPT_vect){Switch_ICU_Mode();}
ISR(TIMER1_OVF_vect){Increment_Overflow_counter;}
	