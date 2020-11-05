#define F_CPU 16000000UL
#include <avr/io.h>  // AVR 입출력에 대한 헤더 파일
#include <util/delay.h>  // delay 함수사용을 위한 헤더파일
#include <avr/interrupt.h>

volatile int tone;
int i=0;
char f_table[9] = {17,43,66,77,97,114,127,137,255};

ISR(TIMER0_OVF_vect)
{
	PORTB ^= 1 << 5;
	TCNT0 = f_table[tone];
}

int main()
{
	DDRB = 0x20;
	TCCR0 = 0x03;
	TIMSK = 0x01;
	//OCR0 = 128;
	
	sei();
	//tone = 8;
	while(1){
		while((PIND & 0x01))
		{
			i++;
			tone = i;
			_delay_ms(1000);	
			if(i==9)
			{
				i = 0;		
			}		
			
		}
	}
}
