/*
 * pwm_servo_timer2.h
 *
 * FOR: ATmega 328p
 *
 * Created: 03/04/2019 12:00:01
 * Author : Felix Abeln
 * 
 * A simple PWM routine for inverted fast PWM, using a 16bit hardware timer. The main purpose of this code is to allow control of servo motors, which
 * require the breadth of the pulse width to be modulated.
 * Channel 1 is wired to: PB1 (PDIP) /  9 (Arduino UNO) -- (OC1A)
 * Channel 2 is wired to: PB2 (PDIP) / 10 (Arduino UNO) -- (OC1B)
 */ 
// for all
#define SignalFrequency_Hz 50.0

// Channel a
#define MinPulseDuration_Seconds_channel_a .00090
#define MaxPulseDuration_Seconds_channel_a .00200
#define DutyPeriod_channel_a (MaxPulseDuration_Seconds_channel_a - MinPulseDuration_Seconds_channel_a)/2
#define StopDuty_channel_a (MinPulseDuration_Seconds_channel_a + MaxPulseDuration_Seconds_channel_a)/2

// Channel b
#define MinPulseDuration_Seconds_channel_b .00090
#define MaxPulseDuration_Seconds_channel_b .00200
#define DutyPeriod_channel_b (MaxPulseDuration_Seconds_channel_a - MinPulseDuration_Seconds_channel_b)/2
#define StopDuty_channel_b (MinPulseDuration_Seconds_channel_a + MaxPulseDuration_Seconds_channel_b)/2

void Setup_16bit_timer_Servo(int channel){
	// Clears the Register form previous settings....Ex....use of the PWM servo library
	TCCR1B = 0;
	TCCR1A = 0;
	TIMSK1 = 0;
	
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
void Set_Servo_Duty(double Pulselenght_seconds, int channel){
	// Calculates counts that the signal has to be on for
	double Period = 1.0/SignalFrequency_Hz;
	double Tiks_Per_Second = ICR1 / Period;
	double  duty = Tiks_Per_Second * (Pulselenght_seconds);
	
	// Updates the OCR1A with the tics to count. Signal at the end of duty cycle
	
	switch (channel){
		case 1 : OCR1A = ICR1 - duty; return;
		case 2 : OCR1B = ICR1 - duty; return;}
}