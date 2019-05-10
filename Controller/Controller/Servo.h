class Servo
{
public:
float DutyPeriod(){return (def_MaxPulseDuration_Seconds - def_MinPulseDuration_Seconds)/2;}
float StopDuty(){return (def_MinPulseDuration_Seconds + def_MaxPulseDuration_Seconds)/2;}

void Attatch(int pin, char bank)
{
	def_pin = pin;
	def_bank = bank;

	if (def_bank == 'B')
	{
		switch (def_pin)
		{
			case 7: SetupTimer0(); DDRB |= (1 << DDB7); break;
			case 6: SetupTimer1(); DDRB |= (1 << DDB6); break;
			case 5: SetupTimer1(); DDRB |= (1 << DDB5); break;
			case 4: SetupTimer2(); DDRB |= (1 << DDB4); break;
		}
	}
	else if (def_bank == 'H')
	{
		switch (def_pin)
		{
			case 6: SetupTimer2(); DDRH |= (1 << DDH6); break;
			case 5: SetupTimer4(); DDRH |= (1 << DDH5); break;
			case 4: SetupTimer4(); DDRH |= (1 << DDH4); break;
			case 3: SetupTimer4(); DDRH |= (1 << DDH3); break;
		}
	}
	else if (def_bank == 'E')
	{
		switch (def_pin)
		{
			case 3: SetupTimer3(); DDRE |= (1 << DDE3); break;
			case 5: SetupTimer3(); DDRE |= (1 << DDE5); break;
			case 4: SetupTimer3(); DDRE |= (1 << DDE4); break;
		}
	}
	else if (def_bank == 'G')
	{
		switch (def_pin)
		{
			case 5: SetupTimer0(); DDRG |= (1 << DDG5); break;
		}
	}
	
}
void Set_Servo_Duty(double Pulselenght_seconds)
{
	// Calculates counts that the signal has to be on for
	double tot_count;
	if (def_bank == 'B')
	{
		switch (def_pin)
		{
			case 7: return;
			case 6: tot_count = ICR1; break;
			case 5: tot_count = ICR1; break;
			case 4: return;
		}
	}
	else if (def_bank == 'H')
	{
		switch (def_pin)
		{
			case 6: return;
			case 5: tot_count = ICR4; break;
			case 4: tot_count = ICR4; break;
			case 3: tot_count = ICR4; break;
		}
	}
	else if (def_bank == 'E')
	{
		switch (def_pin)
		{
			case 3: tot_count = ICR3; break;
			case 5: tot_count = ICR3; break;
			case 4: tot_count = ICR3; break;
		}
	}
	else if (def_bank == 'G')
	{
		switch (def_pin)
		{
			case 5: return;
		}
	}
	
	
	
	double Period = 1.0/def_SignalFrequency_Hz;
	double Tiks_Per_Second = tot_count / Period;
	double  duty = Tiks_Per_Second * (Pulselenght_seconds);
	
	SetPWM(duty);
}
void SetPWM(int count)
{
	if (def_bank == 'B')
	{
		switch (def_pin)
		{
			case 7: break;
			case 6: OCR1B = ICR1 - count; break;
			case 5: OCR1A = ICR1 - count; break;
			case 4: break;
		}
	}
	else if (def_bank == 'H')
	{
		switch (def_pin)
		{
			case 6: break;
			case 5: OCR4C = ICR4 - count; break;
			case 4: OCR4B = ICR4 - count; break;
			case 3: OCR4A = ICR4 - count; break;
		}
	}
	else if (def_bank == 'E')
	{
		switch (def_pin)
		{
			case 3: OCR3A = ICR3 - count; break;
			case 5: OCR3C = ICR3 - count; break;
			case 4: OCR3B = ICR3 - count; break;
		}
	}
	else if (def_bank == 'G')
	{
		switch (def_pin)
		{
			case 5: break;
		}
	}
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
void SetupTimer0(){}
void SetupTimer1()
{
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);
	TCCR1A |= (1<<COM1B1)|(1<<COM1B0);
	TCCR1B |= (1<<CS11);
	
	def_bits = 16;
	ICR1 = (F_CPU/(def_SignalFrequency_Hz*8))-1; //Amount of counts during 1 period. Period is 1/freq - 1, 8 is the prescaler.
}
void SetupTimer3()
{
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM32) | (1<<WGM33);
	TCCR3A |= (1<<COM3A1)|(1<<COM3A0);
	TCCR3A |= (1<<COM3B1)|(1<<COM3B0);
	TCCR3B |= (1<<CS31);
	
	def_bits = 16;
	ICR3 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;	
}
void SetupTimer2(){}
void SetupTimer4()
{
	TCCR4A |= (1<<WGM41);
	TCCR4B |= (1<<WGM42) | (1<<WGM43);
	TCCR4A |= (1<<COM4A1)|(1<<COM4A0);
	TCCR4A |= (1<<COM4B1)|(1<<COM4B0);
	TCCR4B |= (1<<CS41);
	
	def_bits = 16;
	ICR4 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;
}
void SetupTimer5()
{
	TCCR5A |= (1<<WGM51);
	TCCR5B |= (1<<WGM52) | (1<<WGM53);
	TCCR5A |= (1<<COM5A1)|(1<<COM5A0);
	TCCR5A |= (1<<COM5B1)|(1<<COM5B0);
	TCCR5B |= (1<<CS51);
	
	def_bits = 16;
	ICR5 =  (F_CPU/(def_SignalFrequency_Hz*8))-1;
}

float def_SignalFrequency_Hz = 50.0;
float def_MinPulseDuration_Seconds = .0009;
float def_MaxPulseDuration_Seconds = .0021;
int def_bits;
int def_pin;
char def_bank;
};
