int CheckIrSensors()
{
	int Sensor_Output = 0b00000;
	
	for (int x = 1; x <= 5; x++)
	{
		if((PIND & (1 << (x+1))))
		{
			Sensor_Output |= (1 << (x-1));
		}
	}
	return Sensor_Output;
}
int CheckOnButton()
{
	if (PINB & (1 << PINB4)) {return 1;}
	else {return 0;}
}