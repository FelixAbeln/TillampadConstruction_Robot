
#define SignalFrequency_Hz 50.0


void Setup_L298N_PWM()
{
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12) | (1<<WGM13);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);
	TCCR1A |= (1<<COM1B1)|(1<<COM1B0);
	TCCR1B |= (1<<CS11);
	ICR1 = (F_CPU/(SignalFrequency_Hz*8))-1;
}

 class Ln298n_Motor
 {
 public:
  void Attach(int channel)
  {
	  switch  (channel)
	  {
		  case 1 : Pin = DDB1; Outpin1 = DDC0; Outpin2 = DDC1; break;
		  case 2 : Pin = DDB2; Outpin1 = DDC2; Outpin2 = DDC3; break;
		  default:return;
	  }	  
		  
		  DDRB |= (1 << Pin);
		  DDRC |= (1 << Outpin1) | (1 << Outpin2);
		  
		  CalibParam = 1;
  }
  void SetDirection(int mode)
  {
	  switch (mode)
	  {
		  case 0 : PORTC &= ~(1 << Outpin1); PORTC &= ~(1 << Outpin2); break;
		  case 1 : PORTC |= (1 << Outpin1); PORTC &= ~(1 << Outpin2); break;
		  case 2 : PORTC &= ~(1 << Outpin2); PORTC |= (1 << Outpin2); break;
	  }
  }
  void SetPWMCount(int PWMCount)
  {  
	  PWMCount = ICR1 - PWMCount;
	  switch (Pin)
	  {
		  case DDB1 : OCR1A = PWMCount; return;
		  case DDB2 : OCR1B = PWMCount; return;
	  }
  }
  void SetSpeedPercent(float percent)
  {
	  if (percent > 1 || percent < 0){return;}
		  
	  int PWMCount = TotalPwmCount() * percent;
	  SetPWMCount(PWMCount);
  }
  void Calibrate(float CalibrationPercent)
  {
	  if (CalibrationPercent > 1 || CalibrationPercent < 0){return;}
		  
	  CalibParam = CalibrationPercent;
	  
  }
  void Off()
  {
	  SetPWMCount(0);
  }
  void FullSpeed()
  {
	  SetPWMCount(TotalPwmCount());
  }
  int TotalPwmCount()
  {
	  return ICR1 * CalibParam;
  }
 protected:
 
 private:
 float CalibParam;
 int Pin;
 int Outpin1;
 int Outpin2;
 };