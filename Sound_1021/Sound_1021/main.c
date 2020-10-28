#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	int num = 0;
	DDRD=0x00;          // PD0 = Sound Sensor
	PORTD=0xff;
	DDRB=0xff;
	DDRE=0x00;            // PB = LED
	while(1)
	{
		if(!(PIND & 0x01))
		{
			num++;
			if(num == 16) num = 0;
			_delay_ms(1000);
		}
		if((PINE & 0x01) == 0x00) num = 0;
		if(num == 0) PORTB = 0x00;
		if(num == 1) PORTB = 0x01;
		if(num == 2) PORTB = 0x02;
		if(num == 3) PORTB = 0x03;
		if(num == 4) PORTB = 0x04;
		if(num == 5) PORTB = 0x05;
		if(num == 6) PORTB = 0x06;
		if(num == 7) PORTB = 0x07;
		if(num == 8) PORTB = 0x08;
		if(num == 9) PORTB = 0x09;
		if(num == 10) PORTB = 0x0A;
		if(num == 11) PORTB = 0x0B;
		if(num == 12) PORTB = 0x0C;
		if(num == 13) PORTB = 0x0D;
		if(num == 14) PORTB = 0x0E;
		if(num == 15) PORTB = 0x0F;
	}

}
