/*
 * pwm.h
 *
 * FOR: ATmega 328p
 *
 * Created: 03/04/2019 12:00:01
 * Author : Felix Abeln
 * 
 * A simple PWM routine for inverted fast PWM, using a 16bit hardware timer.
 * Channel 1 is wired to: PB1 (PDIP) /  9 (Arduino UNO) -- (OC1A)
 * Channel 2 is wired to: PB2 (PDIP) / 10 (Arduino UNO) -- (OC1B)
 */ 

#define MinPulseDuration_Seconds .00090
#define MaxPulseDuration_Seconds .00200
#define SignalFrequency_Hz 50.0

#define DutyPeriod (MaxPulseDuration_Seconds - MinPulseDuration_Seconds)/2
#define StopDuty (MinPulseDuration_Seconds + MaxPulseDuration_Seconds)/2

void PWM_Init(int channel){
	
	// Sets the specified channel to an output pin.
	switch (channel){
		case 1 : DDRB |= (1<<DDB1); return;
		case 2 : DDRB |= (1<<DDB2); return;}
	
	// Sets up all the relevant registers, if they are already set from a previous channel, the values wont change.
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);
	TCCR1B |= (1<<CS11);
	
	ICR1 = (F_CPU/(SignalFrequency_Hz*8))-1; //Amount of counts during 1 period. Period is 1/freq - 1, 8 is the prescaler. 
}

void Set_16BIT_PWM(double Pulselenght_seconds, int channel){
	// Calculates counts that the signal has to be on for
	double Period = 1.0/SignalFrequency_Hz;
	double Tiks_Per_Second = ICR1 / Period;
	double  duty = Tiks_Per_Second * (Pulselenght_seconds);
	
	// Updates the OCR1A with the tics to count. Signal at the end of duty cycle
	
	switch (channel){
		case 1 : OCR1A = ICR1 - duty; return;
		case 2 : OCR1B = ICR1 - duty; return;}
}