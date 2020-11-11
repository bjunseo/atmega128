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
	DDRA = 0xFF;
	DDRC = 0x00;
	DDRB = 0xFF;

	PORTB = 0x01;
	_delay_ms(3000);
	
    while (1) 
    {
		PORTA = 0x01;	
		if((PINC & 0x01) == 0x00)
		{
			PORTB = 0x04;
			uart_write(1);
		}
		else
		{
			PORTB = 0x02;
			uart_write(2);
		}
		_delay_ms(1000);
    }
}