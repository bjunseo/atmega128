#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile char _speed=0;

char rx_flag=1;

void US_init(unsigned int UB)
{
	UBRR0H=(unsigned char)(UB>>8);
	UBRR0L=(unsigned char)UB;
	UCSR0B=(1<<RXEN0);
}

unsigned char RX0_CH()
{
	while(!(UCSR0A&(1<<RXC0)));
	rx_flag=1;
	return UDR0;
}

int main(void)
{	
	unsigned char rx_buf;
	US_init(103);
	DDRF=0xFF;
	DDRB=0x60;
	DDRE=0x00;
	TCCR1A=0x82;
	TCCR1B=0x1A;
	OCR1A=0;
	OCR1B=0;
	ICR1=100;
	
	while(1)
	{	
		rx_buf = RX0_CH();
		
		if(rx_buf)
		{
			rx_flag = 0;
			_speed = rx_buf;
		}
		if((PINE & 0x01)==0x00)
		{
			if(_speed == 0)
			{
				_speed = 80;
			}
			else
				_speed = _speed + 20; 
			if(_speed > 160)
			{
				_speed = 160;
			}
		}
		if((PINE & 0x02)==0x00)
		{
			if(_speed < 80)
			{
				_speed = 0;
			}
			else
				_speed = _speed - 20;
		}
		if((PINE & 0x04)==0x00)
		{
			_speed = 0;
		}
		OCR1A = _speed;
		if(_speed == 0) PORTF = 0x01;	
		if(_speed == 80) PORTF = 0x02;
		if(_speed == 100) PORTF = 0x04;
		if(_speed == 120) PORTF = 0x08;
		if(_speed == 140) PORTF = 0x10;
		if(_speed == 160) PORTF = 0x20;
		_delay_ms(1000);
	}
}