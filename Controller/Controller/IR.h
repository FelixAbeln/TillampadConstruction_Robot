class IR_Sensor
{
	public:
	void Attatch(int pin, char bank)
	{
		def_bank = bank;
		def_pin = pin;
		
		if (def_bank == 'A'){DDRA &= ~(1 << def_pin);}
		else if(def_bank == 'B'){DDRB &= ~(1 << def_pin);}
		else if(def_bank == 'C'){DDRC &= ~(1 << def_pin);}
		else if(def_bank == 'D'){DDRD &= ~(1 << def_pin);}
		else if(def_bank == 'E'){DDRE &= ~(1 << def_pin);}
		else if(def_bank == 'F'){DDRF &= ~(1 << def_pin);}
		else if(def_bank == 'G'){DDRG &= ~(1 << def_pin);}
		else if(def_bank == 'H'){DDRH &= ~(1 << def_pin);}
		else if(def_bank == 'J'){DDRJ &= ~(1 << def_pin);}
		else if(def_bank == 'K'){DDRK &= ~(1 << def_pin);}
		else if(def_bank == 'L'){DDRL &= ~(1 << def_pin);}
	}
	
	int Value()
	{
		switch (def_bank)
		{
			case 'A': if (PINA & (1 << def_pin)){return 1;} else {return 0;}
			case 'B': if (PINB & (1 << def_pin)){return 1;} else {return 0;}
			case 'C': if (PINC & (1 << def_pin)){return 1;} else {return 0;}
			case 'D': if (PIND & (1 << def_pin)){return 1;} else {return 0;}
			case 'E': if (PINE & (1 << def_pin)){return 1;} else {return 0;}
			case 'F': if (PINF & (1 << def_pin)){return 1;} else {return 0;}
			case 'G': if (PING & (1 << def_pin)){return 1;} else {return 0;}
			case 'H': if (PINH & (1 << def_pin)){return 1;} else {return 0;}
			case 'J': if (PINJ & (1 << def_pin)){return 1;} else {return 0;}
			case 'K': if (PINK & (1 << def_pin)){return 1;} else {return 0;}
			case 'L': if (PINL & (1 << def_pin)){return 1;} else {return 0;}
		}
		return 0;
	}
protected:
private:
	int def_pin;
	char def_bank;
};
