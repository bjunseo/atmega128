/*
 * ballSW_IR_1104.c
 *
 * Created: 2020-11-04 오전 9:07:47
 * Author : user
 */ 

#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)

#include <avr/io.h>
#include <util/delay.h>

void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void uart_write(unsigned char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}


int main(void)
{
    /* Replace with your application code */
	uart_init(BAUDRATE(9600));
	
	
	int status1 = 0 , status2 = 2;
	DDRD = 0x00;
	DDRA = 0xff;
    while (1) 
    {
		PORTA = 0x80;
		if(((PIND & 0x01) == 0x00) && (status1 == 0))
		{
			status1 = 1;
			
			PORTA = 0x01;
			_delay_ms(100);
			PORTA = 0x00;
		}
		else if((PIND & 0x01) == 0x01)
		{
			status1 = 0;
		}
		
		if(((PIND & 0x02) == 0x00) && (status2 == 2))
		{
			status2 = 3;
			PORTA = 0x02;
			_delay_ms(100);
			PORTA = 0x00;
		}
		
		else if((PIND & 0x02) == 0x02)
		{
			status2 = 2;
		} 
		
		_delay_ms(500);
		uart_write(status1);
		uart_write(status2);
	}
}