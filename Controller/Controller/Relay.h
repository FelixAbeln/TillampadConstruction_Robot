class Relay
{
public:
void Attatch(int pin, char bank)
{
	def_bank = bank;
	def_pin = pin;
	
	if (def_bank == 'A'){DDRA |= (1 << def_pin);}
	else if(def_bank == 'B'){DDRB |= (1 << def_pin);}
	else if(def_bank == 'C'){DDRC |= (1 << def_pin);}
	else if(def_bank == 'D'){DDRD |= (1 << def_pin);}
	else if(def_bank == 'E'){DDRE |= (1 << def_pin);}
	else if(def_bank == 'F'){DDRF |= (1 << def_pin);}
	else if(def_bank == 'G'){DDRG |= (1 << def_pin);}
	else if(def_bank == 'H'){DDRH |= (1 << def_pin);}
	else if(def_bank == 'J'){DDRJ |= (1 << def_pin);}
	else if(def_bank == 'K'){DDRK |= (1 << def_pin);}
	else if(def_bank == 'L'){DDRL |= (1 << def_pin);}
}
void RelayOn()
{
	if (def_bank == 'A'){PORTA |= (1 << def_pin);}
	else if(def_bank == 'B'){PORTB |= (1 << def_pin);}
	else if(def_bank == 'C'){PORTC |= (1 << def_pin);}
	else if(def_bank == 'D'){PORTD |= (1 << def_pin);}
	else if(def_bank == 'E'){PORTE |= (1 << def_pin);}
	else if(def_bank == 'F'){PORTF |= (1 << def_pin);}
	else if(def_bank == 'G'){PORTG |= (1 << def_pin);}
	else if(def_bank == 'H'){PORTH |= (1 << def_pin);}
	else if(def_bank == 'J'){PORTJ |= (1 << def_pin);}
	else if(def_bank == 'K'){PORTK |= (1 << def_pin);}
	else if(def_bank == 'L'){PORTL |= (1 << def_pin);}
		
	stat_on = 1;
}
void RelayOff()
{
	if (def_bank == 'A'){PORTA &= ~(1 << def_pin);}
	else if(def_bank == 'B'){PORTB &= ~(1 << def_pin);}
	else if(def_bank == 'C'){PORTC &= ~(1 << def_pin);}
	else if(def_bank == 'D'){PORTD &= ~(1 << def_pin);}
	else if(def_bank == 'E'){PORTE &= ~(1 << def_pin);}
	else if(def_bank == 'F'){PORTF &= ~(1 << def_pin);}
	else if(def_bank == 'G'){PORTG &= ~(1 << def_pin);}
	else if(def_bank == 'H'){PORTH &= ~(1 << def_pin);}
	else if(def_bank == 'J'){PORTJ &= ~(1 << def_pin);}
	else if(def_bank == 'K'){PORTK &= ~(1 << def_pin);}
	else if(def_bank == 'L'){PORTL &= ~(1 << def_pin);}
		
	stat_on = 0;
}
int IsOn()
{
	return def_pin;
}

protected:

private:
int def_pin;
char def_bank;
int stat_on;
};
