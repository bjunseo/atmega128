/*
 C port = LCD
 A port = LED
 E port = Button
 F port = FND
 0 = BASIS, 1 = LED, 2 = FND
*/

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <util/delay.h>

char LCD_start[] = {
	"LED_COUNT",
	"FND_CONNT"
};

char LED_font[] = {
	0b00000000,
	0b00000001,
	0b00000011,
	0b00000111,
	0b00001111,
	0b00011111,
	0b00111111,
	0b01111111,
	0b11111111
};

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

void COMMAND(unsigned char byte);	
void DATA(unsigned char byte);		
void LCD_INIT(void);			
void LCD_Num(int ucNum);
void LCD_Str(const unsigned char * cString);
void MOVE(int y,int x);

int main(void)
{
	int i, flag = 0, LED_d = 0, FND_d = 0;
	
	DDRC = 0xff;
	PORTC = 0x00;
	
	DDRA = 0xff;
	PORTA = 0x00;
	
	DDRF = 0xFF;
	PORTF = 0x00;
	
	DDRE = 0x00;
	
	LCD_INIT();
	
    while (1) 
    {
		if(flag == 0)
		{
			PORTA = 0x00;
			PORTF = 0x00;
			
			MOVE(3,1);
			LCD_Str(LCD_start[0]);
			MOVE(3,2);
			LCD_Str(LCD_start[1]);
			
			if(PINE == 0x01)
			{
				i++;
				i = i % 2;
			}
			else if(PINE == 0x02)
			{
				if(i == 1) i--;
				else if(i == 0) i++;
			}
			else if(PINE == 0x04)
			{
				if(i == 0) flag = 1;
				else if(i == 1) flag = 2;
			}
			
			MOVE(1, i+1);
			DATA("-");
		}
		else if(flag == 1)
		{
			if(PINE == 0x03) flag = 0;
			if(PINE == 0x08)
			{
				LED_d++;
			}
			LED_d = LED_d % 9;
			PORTA = LED_font[LED_d];
		}
		else if(flag == 2)
		{
			if(PINE == 0x03) flag = 0;
			if(PINE == 0x08)
			{
				FND_d++;
			}
			FND_d = FND_d % 9;
			PORTF = FND_font[FND_d];
		}
    }
}

void COMMAND(unsigned char byte)
{
	_delay_ms(2);

	PORTC=byte&0xf0;// 상위4비트 명령어 쓰기
	PORTC&=0b11111100;  // RS = 0, RW = 0, 명령어를 쓰도록 설정
	_delay_us(1);
	PORTC|=0b00000100; // E = 1, lcd 동작
	_delay_us(1);
	PORTC&=0b11111011;// E = 0

	PORTC=(byte<<4)&0xf0;// 하위4비트 명령어 쓰기
	PORTC&=0b11111100;// RS = 0, RW = 0, 명령어를 쓰도록 설정
	_delay_us(1);
	PORTC|=0b00000100; // E = 1, lcd 동작
	_delay_us(1);
	PORTC&=0b11111011;// E = 0
}

void DATA(unsigned char byte)
{
	_delay_ms(2);

	PORTC=byte&0xf0;// 상위4비트 명령어 쓰기
	PORTC |= 0b00000001;// RS = 1, 데이터 설정
	PORTC &= 0b11111101;// RW = 0, 쓰기 설정
	_delay_us(1);
	PORTC|=0b00000100; // E = 1, lcd 동작
	_delay_us(1);
	PORTC&=0b11111011;// E = 0

	PORTC=(byte<<4)&0xf0;// 하위4비트 데이터 쓰기
	PORTC |= 0b00000001;// RS = 1, 데이터 설정
	PORTC &= 0b11111101;// RW = 0, 쓰기 설정
	_delay_us(1);
	PORTC|=0b00000100; // E = 1, lcd 동작
	_delay_us(1);
	PORTC&=0b11111011;// E = 0
	
}

void LCD_INIT(void)
{
	_delay_ms(30);	
	
	COMMAND(0b00101000);
	_delay_us(39);	

	COMMAND(0b00001100);
	_delay_us(39);	

	COMMAND(0b00000001);
	_delay_ms(1.53);	
	
	COMMAND(0b00000110);
}

void LCD_Num(int ucNum)
{
	static unsigned char ucBuff[] = "1";  

	//ucBuff[0] = '0' + (ucNum / 1000);
	//ucBuff[1] = '0' + ((ucNum % 1000) / 100);
	//ucBuff[0] = '0' + ((ucNum % 100) / 10);
	ucBuff[0] = '0' + (ucNum % 10);
	//ucBuff[4] =


	LCD_Str(ucBuff);
}

void LCD_Str(const unsigned char * cString) 
{
	while(0 != *cString)
	{
		DATA(*cString);
		++cString;
	}
}

void MOVE(int y, int x)     //move cursor
{
	unsigned char data;
	if(y==1) 	data = 0x80 + x - 1;           
	else     	data = 0xc0 + x - 1;          
	COMMAND(data);
}