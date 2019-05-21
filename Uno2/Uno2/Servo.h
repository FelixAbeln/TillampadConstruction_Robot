class Servo
{
public:
float DutyPeriod(){return (def_MaxPulseDuration_Seconds - def_MinPulseDuration_Seconds)/2;}
float StopDuty(){return (def_MinPulseDuration_Seconds + def_MaxPulseDuration_Seconds)/2;}

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
void Set_PWM(int count)
{
	OCR1A = ICR1 - count;
}
void Set_Servo_Duty(int Pulselenght_seconds)
{
	double Period = 1.0/def_SignalFrequency_Hz;
	double Tiks_Per_Second = ICR1 / Period;
	double  duty = Tiks_Per_Second * (Pulselenght_seconds);
	
	Set_PWM(duty);
}
protected:
private:
int def_bits;
int def_port;
int def_SignalFrequency_Hz = 50;
float def_MinPulseDuration_Seconds = .0009;
float def_MaxPulseDuration_Seconds = .0021;
};