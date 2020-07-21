/*
 * 0527_LED1.c
 *
 * Created: 2020-05-27 오전 10:49:25
 * Author : user
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRE = 0x00;
	int i;
	int flag=0;
	while (1)
	{
		if((PINE & 0x01) == 0x00)
		{
			flag = 1;
		}
		else if((PINE & 0x02) == 0x00)
		{
			flag = 2;
		}
		
		if(flag == 1)
		{
			PORTA = 0x00;
			_delay_ms(500);
			for(i = 0; i < 8; i = i+2)
			{
				PORTA |= 1 << i;
				_delay_ms(500);
				if((PINE & 0x02) == 0x00) 
				{
					flag = 2;
				}
				
			} 
		}
		
		else if(flag == 2)
		{
			PORTA = 0x00;	
			_delay_ms(500);	
			for(i=1; i < 8; i = i+2)
			{
				PORTA |= 1 << i;
				_delay_ms(500);			
				if((PINE & 0x01) == 0x00)
				{
					flag = 1;
				}
				
			}
			
		}
		
	}
	return 0;
}