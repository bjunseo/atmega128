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

void adcInit(void)  //ADC �ʱ�ȭ �Լ�
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); //16Mhz/128 = 125Khz
	ADMUX |= (1<<REFS0);       //AVCC(5V)
	ADCSRA |= (1<<ADEN);      //ADC �ο��̺�
}

uint16_t readAdc(uint8_t channel)  //���� �о���� �Լ�
{
	
	ADMUX &= 0xF0;
	ADMUX |= channel;
	
	ADCSRA |= (1<<ADSC);      //��ȯ ����
	while(ADCSRA&(1<<ADSC));//��ȯ �Ϸ�Ǳ⸦ ��ٸ�.
	
	return ADCW;  //ADC�� ��ȯ
}

int main(void)
{
	int ch_ADC;
    /* Replace with your application code */
	uart_init(BAUDRATE(9600));
	
	DDRA = 0xFF;
	DDRC = 0x00;
	DDRB = 0xFF;

	adcInit();
		
	PORTB = 0x01;
	_delay_ms(3000);
	
    while (1) 
    {
		PORTA = 0x01;
		ch_ADC = readAdc(0);	
		if((PINC & 0x01) == 0x00)
		{
			PORTB = 0x04;
		}
		else
		{
			PORTB = 0x02;
		}
		uart_write(ch_ADC);
    }
}