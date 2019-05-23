#include <Arduino.h>

#include <Servo.h>

Servo Lift;
bool LiftIsUp = 0;

void StartServo(void)
{
	Lift.write(0);
}
void StopServo(void)
{
	Lift.write(90);
}
bool SensorOn(void)
{
	if (PIND & (1 << PIND2))
	{
		return false;
	}
	else {return true;}
};
 
void setup() {
  // put your setup code here, to run once:
  Lift.attach(9);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(12, INPUT);
  digitalWrite(6, HIGH);
  Lift.write(88);
}

void loop()
{
	if (digitalRead(12) == HIGH)
	{digitalWrite(6, HIGH);}
	else {digitalWrite(6, LOW);}
		
	if (SensorOn() && !LiftIsUp)
	{
		Serial.println("Ball Found");
		_delay_ms(500);
		Lift.write(180);
		_delay_ms(4000);
		Lift.detach();
		LiftIsUp = true;
	}
	_delay_ms(500);
}

