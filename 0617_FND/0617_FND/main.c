#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int j = 0;
	int i = 0;
	
	int d10;
	int d1;
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRF = 0x03;

	DDRE = 0x00;
	char FND_font[] = {
		0b00000011,
		0b10011111,
		0b00100101,
		0b00001101,
		0b10011001,
		0b01001001,
		0b01000001,
		0b00011011,
		0b00000001,
		0b00001001
	};
    /* Replace with your application code */
    while (1) 
    {
		int btn1 = 0;
		int btn2 = 0;
		
		if((PINE & 0x01) == 0x00)
		{
			btn1 = 1;
			btn2 = 0;
		}
	
		if((PINE & 0x02) == 0x00)
		{
			btn2 = 1;
			btn1 = 0;
		}

		
		if(btn1 == 1)
		{
			for(i ; i < 100; i++) {
				if((PINE & 0x02) == 0x00)
				{
					btn1 = 0;
					btn2 = 1;
					break;
				}
				
				d10 = i / 10;
				d1 = i % 10;
									
				for(j = 0; j < 50; j++)
				{
					_delay_ms(5);
					PORTF = 0x02;
					PORTA =FND_font[d10];
					_delay_ms(5);
					PORTF = 0x01;
					PORTA =FND_font[d1];
				}
					
				
				if(i == 99) i = 0;
			}		
		}
	
		else if(btn2 == 1)
		{
			for(i ; i > 0; i--) {
				if((PINE & 0x01) == 0x00)
				{
					btn1 = 1;
					btn2 = 0;
					break;
				}
				
				d10 = i / 10;
				d1 = i % 10;

				for(j = 0; j < 50; j++)
				{
					_delay_ms(5);
					PORTF = 0x02;
					PORTA =FND_font[d10];
					_delay_ms(5);
					PORTF = 0x01;
					PORTA =FND_font[d1];
				}
				
				if(i == 1) i = 100;
			}
		}
	
		else if(btn1 == 0 && btn2 == 0)
		{
			PORTA = 0x00;
		}
    }
}

