/*
 * pwm.h
 *
 * FOR: ATmega 328p
 *
 * Created: 03/04/2019 12:00:01
 * Author : Felix Abeln
 * 
 * A simple PWM routine for inverted fast PWM using two 8bit hardware timers. The points of this routine is to provide a clock for stepper motor drivers.
 * Through frequency modulation, the clock is regulated, while the pulse width is kept constant, to ensure registration of the signal.
 *
 * Channel 1 is wired to: PB1 (PDIP) /  9 (Arduino UNO) -- (OC1A)
 * Channel 2 is wired to: PB2 (PDIP) / 10 (Arduino UNO) -- (OC1B)
 */ 

#define SignalFrequencyMin_stepper_Hz_Channel_A 65
#define SignalFrequencyMax_stepper_Hz_Channel_b 100000
#define Pulsewidth 

void Stepper_init(int channel){
	
	switch (channel){
		case 1 : TCCR0A |= (1 << WGM00) | (1 << WGM01); 
				 TCCR0B |= (1 << WGM02);  
				 TCCR0B |= (1 << CS02) | (1 << CS00); 
				 TCCR0B |= (1 << COM0A0) | (1 << COM0A1);
				 OCR0A ;
				 OCR0B = OCR0A * .25;
				 return;
				 
		case 2 : TCCR2A |= (1 << WGM21) | (1 << WGM20); 
				 TCCR2B |= (1 << WGM22); 
				 TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); 
				 TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
				 OCR2A ;
				 OCR2B = OCR2A * .25;
				 return;
		}
		
}

void Stop_Stepper(int channel){
	switch (channel){
		case 1 : TCCR0B &= ~(1 << CS02) & ~(1 << CS00) & ~(1 << CS01); return;
		case 2 : TCCR2B &= ~(1 << CS22) & ~(1 << CS20) & ~(1 << CS21); return;}
}
void Start_Stepper(int channel){
	switch (channel){
		case 1 : TCCR0B |= (1 << CS02) | (1 << CS00); return;
		case 2 : TCCR2B |= (1 << CS22) | (1 << CS20) | (1 << CS21); return;}
}