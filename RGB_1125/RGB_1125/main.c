#define F_CPU 16000000UL
#define BAUDRATE(x) ((F_CPU / 16 / x) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
volatile int bright;
char f_table[9] = {0, 10, 30, 50, 100, 150, 180, 200, 255};
	
void uart_init(unsigned int baud)
{
	UBRR0H = (unsigned char)(baud >> 8);
	UBRR0L = (unsigned char)baud;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
}

void uart_read()
{
	while(!(UCSR0B & (1<<RXC0)));
	return UDR0;		
}

ISR(TIMER0_OVF_vect)
{
	PORTB ^= 1 << 4;
	TCNT0 = f_table[bright];
}

int main(void)
{
	char buffer[20] ="";
	char data;
	int sta = 0;
	int i = 0;
	uart_init(BAUDRATE(9600));
	DDRB = 0x10;
	
    TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(0<<COM1B0)|(0<<COM1B0)|(0<<COM1C1)|(0<<COM1C0)|(1<<WGM11)|(0<<WGM10);  
	
	TCCR1B = (0<<ICNC1)     |(0<<ICES1) |                                (1<<WGM13)  |(1<<WGM12 )|(0<<CS12  )|(1<<CS11 )|(0<<CS10 );       // N=8

	
	TCCR1C = 0;
	
	TCNT1 = 0;
    /* Replace with your application code */
    while (1) 
    {
		data = uart_read();
		
		if(data == '\n')
		{
			buffer[i] = '\0';
			sta = 1;	
		}
		else
		{
			if(data == 'R') sta = 1;
			if(data == 'B') sta = 2;
			if(data == 'G') sta = 3;
		}
		if(sta = 1)
		{
			while(buffer[i] == 'B')					
		}
		else if(sta = 2)
		{
			
		}
		else if(sta = 3)
		{
			
		}
    }
	
}

