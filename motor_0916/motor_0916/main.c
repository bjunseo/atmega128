#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile char _speed=0;

char rx_flag=1;

void USART_Init(void)
{
	UCSR0A=0x00; // clear
	UCSR0B=(1<<RXEN1) | (1<<TXEN1); // Rx, Tx Enable
	UCSR0C=(0<<UCSZ02) | (1<<UCSZ01) | (1<<UCSZ00); // Tx data len : 8-bit
	
	UBRR0H=0;
	UBRR0L=51; // baudrate 19200
}

unsigned char USART_Receive(void)
{
	while(!(UCSR0A & (1<<RXC0))) // Wait for data to be received
	;
	return UDR0; // Get and return received data form buffer
}

void USART_Transmit(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE))) // Wait for empty transmit buffer
	;
	UDR0=data; // Put data into buffer, sends the  data
}

int main(void)
{	
	unsigned char rx_buf;
	USART_Init();
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
		_speed = USART_Receive();
		
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