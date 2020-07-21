#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRE = 0x00;
	int btn1 = 0;
	int btn2 = 0; 
	while (1)
	{
		
		if((PINE & 0x01) == 0x00)
		{
			btn1 = 1;
		}
		else
		{
			btn1 = 0;
		}
		if((PINE & 0x02) == 0x00)
		{
			btn2 = 1;
		}
		else
		{
			btn2 = 0;
		}
		
		if(btn1 == 1 && btn2 == 1)
		{
			/*
			PORTA = 0xFF;
			*/
			PORTA = 0xAA;
			_delay_ms(500);
			PORTA = 0x55;
			_delay_ms(500);
			
		}
		
		else if(btn2 == 1)
		{
			/*
			PORTA = 0x0F;
			*/	
			PORTA = 0xF0;
			_delay_ms(500);
			PORTA = 0x0F;
			_delay_ms(500);
			
		}
		
		else if(btn1 == 1)
		{
			/*
			PORTA = 0x03;
			*/
			PORTA = 0xCC;
			_delay_ms(500);
			PORTA = 0x33;
			_delay_ms(500);
			
		}
		
		else if(btn1 == 0 && btn2 == 0)
		{
			/*
			PORTA = 0x00;
			*/
			PORTA = 0xFF;
			_delay_ms(500);
			PORTA = 0x00;
			_delay_ms(500);
			
		}
		
		
	}
	return 0;
}