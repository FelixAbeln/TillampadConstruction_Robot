/*
 * Ultrasound_distance.h
 *
 * FOR: ATmega 328p
 *
 * Created: 03/04/2019 12:00:01
 * Author : Felix Abeln
 * 
 * This header contains code which addresses generic ultrasound distance meters. It sends a 10 us trigger pulse and then uses the inbuilt ICU to detect the pulse length.
 * Additionally it calculates the output value in two different modes:
 * Mode 1: cm
 * Mode 2: mm
 * ICR pin: PB0 (PIDP) / 8 (Arduino uno) -- ICR1
 * This code makes use of the timer interrupts, and therefore interrupts have to be enabled. The ICU interrupts are included in this routine. If these service routine are not to
 * used, they require commenting out.
 */ 

#define Increment_Overflow_counter Overflow_counter ++

volatile int Overflow_counter;
volatile double Signal_stop;
volatile double Signal_start;

// General Inline Functions
void Setup_16bit_timer_ICU(){
	// Clears the Register form previous settings....Ex....use of the PWM servo library
	TCCR1B = 0;
	TCCR1A = 0;
	TIMSK1 = 0;
	
	// Sets up Echo and trigger pins
	DDRB |= (1 << DDB5); //Trigger pin
	DDRB &= ~(1 << DDB0); //Echo pin
			
	//Setup the 16-bit timer in the correct way
	TCCR1B |= (1 << ICNC1) | (1 << ICES1);
	TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
	TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
	TIMSK1 |= (1 << ICIE1) | (1 << TOIE1);
	TCCR1B |= (1 << CS11);
}	
double Measure_Distance(){
	//Clear variables
	Overflow_counter = 0;
	TCNT1 = 0;
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << ICES1);
		
	//Send the signal to start the measurement
	PORTB |= (1 << PORTB5);
	_delay_us(10);
	PORTB &= ~(1 << PORTB5);
	
	while (TCCR1B & (1 << CS11));
		
	return Signal_stop-Signal_start;
}

// Unit Modifiers. TO be used as InXX(Measure_Distance()); Measure_Distance() Gives the PWM output.
double InCM(double PWM_Measure){
	double Pulse_Seconds = PWM_Measure / (F_CPU / 8); 
	double Micro_seconds = Pulse_Seconds * 1000000;
	double CM = Micro_seconds / 58;
	return CM;
}
double InMM(double PWM_Measure){
	double CM = InCM(PWM_Measure);
	double MM = CM * 10;
	return MM;
}

// Interrupt service routine functions for the 16bit ICU module. (To be called from the ISR)
void Switch_ICU_Mode(){
	if (TCCR1B & (1 << ICES1))
	{
		Signal_start = ICR1 + (65536 * Overflow_counter);
		TCCR1B &= ~(1 << ICES1);
		return;
	}
	else if(!(TCCR1B & (1 << ICES1)))
	{
		Signal_stop = ICR1 + (65536 * Overflow_counter);
		TCCR1B &= ~(1 << CS11);
		return;
	}
}