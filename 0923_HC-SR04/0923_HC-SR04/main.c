#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define TRIG 6
#define ECHO 7
#define SOUND_VELOCITY 340UL

void put(int a)
{
	while(!(UCSR1A & 0x20));
	UDR1 = a;
}

int main(void)
{
	unsigned int distance;
	DDRF = 0x3F;
	DDRE = ((DDRE | (1<<TRIG)) & ~(1<<ECHO));
	UCSR1B = 0b00011000;
	UCSR1C = 0b00000110;
	UBRR1H = 0;
	UBRR1L = 103;
	
	while(1)
	{
		TCCR1B = 0x03;
		PORTE &= ~(1<<TRIG);
		_delay_us(10);
		PORTE |= (1<<TRIG);
		_delay_us(10);
		PORTE &= ~(1<<TRIG);
		while(!(PINE & (1<<ECHO)));
		TCNT1 = 0x0000;
		while(PINE & (1<<ECHO));
		TCCR1B = 0x00;
		distance = (unsigned int)(SOUND_VELOCITY * (TCNT1 * 4 / 2) / 1000);
		if(distance < 30){
			PORTF = 0x01;
		}
		else if(distance > 31 && distance < 70){
			PORTF = 0x02;
		}
		else if(distance > 71 && distance < 100){
			PORTF = 0x04;
		}
		else if(distance > 101 && distance < 130){
			PORTF = 0x08;
		}
		else if(distance > 131 && distance < 200){
			PORTF = 0x10;
		}
		else if(distance >200){
			PORTF = 0x20;
		}
		put(distance);
		_delay_us(1000);
	}
}


