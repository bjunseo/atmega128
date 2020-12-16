/*
 * smart_window.c
 * dc motor, 온습도, RGB, CDS
 * Created: 2020-12-09 오전 10:06:35
 * Author : user
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)

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
	int state = 0;
	unsigned int distance;
	DDRD = 0x00;
	DDRC = 0x00;
	DDRA = 0xff;
	//uart_write(3); 
	//PORTA = 0x10;
    /* Replace with your application code */
    while (1) 
    {
			uart_init(BAUDRATE(9600));
			
			if((PINC & 0x01) == 0x00)
			{
				state = 1;
			}
			else
			{
				state = 0;
			}
			
			if(state == 1)
			{
				PORTA = 0x21;
				uart_write(2);
				if((PIND & 0x01) == 0x00)
				{
					PORTA = 0x01;
					_delay_ms(200);
					PORTA = 0x21;
					_delay_ms(200);
					uart_write(1); 
				}
				
			}
			else 
			{
				PORTA = 0x10;
				uart_write(3);
			}
			_delay_ms(500);
    }
}

