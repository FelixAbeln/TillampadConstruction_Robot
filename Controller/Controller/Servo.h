class Servo
{
public:
float DutyPeriod(){return (def_MaxPulseDuration_Seconds - def_MinPulseDuration_Seconds)/2;}
float StopDuty(){return (def_MinPulseDuration_Seconds + def_MaxPulseDuration_Seconds)/2;}

void Attatch(int pin, char bank)
{
	def_pin = pin;
	def_bank = bank;
	//Logic Decisions Here
	DDRB |= (1 << DDB5);

	// Timer 0 - 8bit
	
	
	// Timer 1 - 16bit
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);
	TCCR1A |= (1<<COM1B1)|(1<<COM1B0);
	TCCR1B |= (1<<CS11);
	
	def_bits = 16;
	ICR1 = (F_CPU/(def_SignalFrequency_Hz*8))-1; //Amount of counts during 1 period. Period is 1/freq - 1, 8 is the prescaler. 
	
	// Timer 2 - 8bit
	
	// Timer 3 - 16bit
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM32) | (1<<WGM33);
	TCCR3A |= (1<<COM3A1)|(1<<COM3A0);
	TCCR3A |= (1<<COM3B1)|(1<<COM3B0);
	TCCR3B |= (1<<CS31);
	
	def_bits = 16;
	ICR3 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;
	
	// Timer 4 - 16bit
	TCCR4A |= (1<<WGM41);
	TCCR4B |= (1<<WGM42) | (1<<WGM43);
	TCCR4A |= (1<<COM4A1)|(1<<COM4A0);
	TCCR4A |= (1<<COM4B1)|(1<<COM4B0);
	TCCR4B |= (1<<CS41);
	
	def_bits = 16;
	ICR4 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;
	
	// Timer 5 - 16bit
	TCCR5A |= (1<<WGM51);
	TCCR5B |= (1<<WGM52) | (1<<WGM53);
	TCCR5A |= (1<<COM5A1)|(1<<COM5A0);
	TCCR5A |= (1<<COM5B1)|(1<<COM5B0);
	TCCR5B |= (1<<CS51);
	
	def_bits = 16;
	ICR5 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;
	
}
void Set_Servo_Duty(double Pulselenght_seconds)
{
	// Calculates counts that the signal has to be on for
	double Period = 1.0/def_SignalFrequency_Hz;
	double Tiks_Per_Second = ICR1 / Period;
	double  duty = Tiks_Per_Second * (Pulselenght_seconds);
	
	// Updates the OCR1A with the tics to count. Signal at the end of duty cycle
	SetPWM(duty);
}
void SetPWM(int count)
{
	count = ICR1 - count;
	OCR1A = count;
}
void Off()
{
	Set_Servo_Duty(StopDuty());
}
void MaxForward()
{
	Set_Servo_Duty(StopDuty()+DutyPeriod());
}
void MaxBackwards()
{
	Set_Servo_Duty(StopDuty()-DutyPeriod());
}
int GetPWMBits(){return def_bits;}
void SetPulseWidth(float MaxPulse_Seconds, float MinPulse_Seconds)
{
	def_MaxPulseDuration_Seconds = MaxPulse_Seconds;
	def_MinPulseDuration_Seconds = MinPulse_Seconds;
}
void SetFrequency(float Frequency_Hz)
{
	def_SignalFrequency_Hz = Frequency_Hz;
}

protected:

private:
float def_SignalFrequency_Hz = 50.0;
float def_MinPulseDuration_Seconds = .0009;
float def_MaxPulseDuration_Seconds = .0021;
int def_bits;
int def_pin;
char def_bank;
};
