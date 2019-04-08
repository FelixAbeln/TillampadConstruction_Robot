/*
 * adc.h
 *
 * FOR: ATmega 328p
 *
 * Created: 03/04/2019 12:00:01
 * Author : Felix Abeln
 * 
 * A simple PWM routine for inverted fast PWM, using a 16bit hardware timer.
 * All analogue Pins can be used using the multiplexer. All pins (1-5) are located in the C register, PC0 - PC5
 * On arduino these are A0 - A5
 */ 

#define ADC_Start_Conversion ADCSRA |= (1<<ADSC);

volatile int setpin;

void Setup_ADC_single_conversion(){
	ADCSRA |= (1<<ADEN); // Enable ADC converter
	ADMUX |= (1 << REFS0);	// Vcc Reference with external capacitor at AREF (standard for arduino). Make sure the circuit contains this.
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Prescaler = 128
}
void ADC_set_multiplexer_pin(int pin){
	switch (pin){ // Select the input pin
		case 0 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0);		DIDR0 &= ~(1<<ADC0D); break;
		case 1 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1); ADMUX |= (1<<MUX0); DIDR0 &= ~(1<<ADC1D); break;
		case 2 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0); ADMUX |= (1<<MUX1); DIDR0 &= ~(1<<ADC2D); break;
		case 3 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2); ADMUX |= (1<<MUX1) | (1<<MUX0);  DIDR0 &= ~(1<<ADC3D); break;
		case 4 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX1) & ~(1<<MUX0); ADMUX |= (1<<MUX2); DIDR0 &= ~(1<<ADC4D); break;
		case 5 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX1); ADMUX |= (1<<MUX2) |(1<<MUX0);   DIDR0 &= ~(1<<ADC5D); break;}
		setpin = pin;
}
float VoltageRead_pin(int pin){
	setpin = pin;
	ADC_set_multiplexer_pin(pin);
	ADC_Start_Conversion;
	while(ADCSRA & (1<<ADSC)); // Waits for the 
	DIDR0 |= (1<<pin);
	double Voltage = (ADC * 5)/1024;
	return Voltage;
}
float VoltageRead(){
	ADC_Start_Conversion;
	while(ADCSRA & (1<<ADSC)); // Waits for the
	DIDR0 |= (1<<setpin);
	double Voltage = (ADC * 5)/1024;
	return Voltage;
}