class LightDependentResistor
{
public:
void Attatch(int pin){
	ADCSRA |= (1<<ADEN); 
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	def_pin = pin;
}
float Read(){
	ADC_Read();
	while(ADCSRA & (1<<ADSC)){};
	DIDR0 |= (1<<def_pin);
	double Voltage = (ADC * 5)/1024;
	return Voltage;
}
protected:
private:

void ADC_Read(){
	switch (def_pin){ // Select the input pin
		case 0 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0); DIDR0 &= ~(1<<ADC0D); break;
		case 1 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1); ADMUX |= (1<<MUX0); DIDR0 &= ~(1<<ADC1D); break;
		case 2 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0); ADMUX |= (1<<MUX1); DIDR0 &= ~(1<<ADC2D); break;
		case 3 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX2); ADMUX |= (1<<MUX1) | (1<<MUX0); DIDR0 &= ~(1<<ADC3D); break;
		case 4 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX1) & ~(1<<MUX0); ADMUX |= (1<<MUX2);  DIDR0 &= ~(1<<ADC4D); break;
	case 5 : ADMUX &= ~(1<<MUX3) & ~(1<<MUX1); ADMUX |= (1<<MUX2) |(1<<MUX0); DIDR0 &= ~(1<<ADC5D); break;}
	
	ADCSRA |= (1<<ADSC); // Start the conversion
}

int def_pin;
};
