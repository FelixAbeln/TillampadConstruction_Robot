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

#define Increment_Overflow_counter Overflow_counter_Ultarsound ++

volatile int Overflow_counter_Ultarsound;
volatile double Signal_stop_Ultarsound;
volatile double Signal_start_Ultarsound;

// General Inline Functions
void StartUltrasoundSensor(void){
	//Send the signal to start the measurement. A fifteen us signal will be sent over the trigger pin. This will alert the Ultrasound unit to make a measurement.
	PORTB |= (1 << PORTB1);
	_delay_us(15);
	PORTB &= ~(1 << PORTB1);
}
void Setup_16bit_timer_ICU(){
/*
This function sets up the 16bit timer for use with the ICU unit. It assumes that the registers are all empty to begin with. If this is
not the case, please call Registername = 0; before calling this function.

It also defines the echo and trigger pins. Should the default pins not be used, please modify them below. They will also have to be modified in the measure distance function.
*/

	
	// Sets up Echo and trigger pins.
	DDRB |= (1 << DDB1); //Trigger pin
	DDRB &= ~(1 << DDB0); //Echo pin
			
	//Setup the 16-bit timer in the correct way
	TCCR1B |= (1 << ICNC1) | (1 << ICES1);
	TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
	TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
	TIMSK1 |= (1 << ICIE1) | (1 << TOIE1); // Enables the input capture interrupt (ICIE1) and the timer 1 overflow interrupt (TOIE1) in the timer 1 interrupt control register
	TCCR1B |= (1 << CS11); // Sets the clock to the timer
}	
double Measure_Distance(){

	//Clear variables
	Overflow_counter_Ultarsound = 0;
	TCNT1 = 0;
	TCCR1B |= (1 << CS11);
	TCCR1B |= (1 << ICES1);
	
	StartUltrasoundSensor();
	
	while (TCCR1B & (1 << CS11));
	
	// This returns the timer count and not a distance. As this is a measure of timer a modifier will have to be called to convert it to a distance.
	return Signal_stop_Ultarsound-Signal_start_Ultarsound;
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

// Interrupt service routine functions for the 16bit ICU module. (To be called from the ISR(TIMER1_CAPT_vect).)
void Switch_ICU_Mode(){
	/* This function will switch the reading mode from "low to high" to "High to low" after a "high to low" has been detected.
	Thus it will trigger once when the start of the pulse comes in, and once when the pulse stops. Thus a difference between the two times can be calculated.
	
	Once the "falling edge" has been detected, the clock feeding the timer will be disabled, to prevent the timer from continusly counting/ incrementing the overflow counter. When MeasureDistance() is called,
	both the overflow counter and the current count are cleared. Then the clock is restored. This occours slightly before a start signal is sent to the Ultrasound sensor
	*/
	if (TCCR1B & (1 << ICES1))
	{
		Signal_start_Ultarsound = ICR1 + (65536 * Overflow_counter_Ultarsound);
		TCCR1B &= ~(1 << ICES1);
		return;
	}
	else if(!(TCCR1B & (1 << ICES1)))
	{
		Signal_stop_Ultarsound = ICR1 + (65536 * Overflow_counter_Ultarsound);
		TCCR1B &= ~(1 << CS11);
		return;
	}
}