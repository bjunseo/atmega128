/*
 * motorControl.c
 *
 * Created: 2020-09-09 오전 9:11:42
 * Author : user
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile char speed=0;

void DC_Motor(int speed)
{
	if(speed< 0) speed= 0;
	if(speed>100) speed=100;
	OCR1A=speed;
}

int main(void)
{
	int i;
	DDRB=0x60;
	TCCR1A=0x82;
	TCCR1B=0x1A;
	OCR1A=0;
	OCR1B=0;
	ICR1=100;
	while(1)
	{
		for(i=0;i<=100;i++) {
			DC_Motor(i); _delay_ms(100);
		}
		for(i=100;i>=0;i--){
			DC_Motor(i); _delay_ms(100);
		}
	}
}

/*
void Port_init()
{
	DDRA = 0xff;
}

void delay_time(long t)
{
	long i;
	for(i = 0; i < t; i++);
}

void MotorGo(long Dist, long Speed)
{
	long i;
	for(i = 0; i< Dist; i++){
		PORTA = 0x01;
		delay_time(Speed);
		PORTA = 0x00;
		delay_time(5);
		PORTA = 0x00;
		delay_time(100-Speed);
	}
}

void MotorSTOP()
{
	PORTA = 0x03;
}

int main(void)
{
    Port_init();
	   
    while (1) 
    {		
		MotorGo(500,20);
		delay_time(30000);
		MotorGo(500,40);
		delay_time(30000);
		MotorGo(500,60);
		delay_time(30000);
		MotorGo(500,80);
		delay_time(30000);
		MotorSTOP();
		delay_time(30000);
    }
}
*/
