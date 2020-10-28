//#define  F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#define DHT11_PIN 6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void COMMAND(unsigned char byte);
void DATA(unsigned char byte);
void LCD_INIT(void);
void LCD_Str(const unsigned char * cString);
void Request();
void Response();
uint8_t Receive_data();
void MOVE(int y, int x);

int main(void)
{
	char data[5];
	LCD_INIT();			// LCD 초기화
	MOVE(0,0);		 // LCD 표시 위치
	LCD_Str("Humidity =");
	MOVE(1,0);
	LCD_Str("Temp = ");
	
	while(1)
	{
		Request();		 //시작 펄스 신호 보냄
		Response();		 //센서로부터 응답 받음
		I_RH=Receive_data();	 //습도의 정수 부분
		D_RH=Receive_data();	 //습도의 실수 부분
		I_Temp=Receive_data();	 //온도의 정수 부분
		D_Temp=Receive_data();	 //온도의 실수 부분
		CheckSum=Receive_data(); //모든 세그먼트의 체크섬
        if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			MOVE(0,0);
			LCD_Str("Error");
		}		
		else
		{	
			itoa(I_RH,data,10);
			MOVE(0,11);
			LCD_Str(data);
			LCD_Str(".");
			
			itoa(D_RH,data,10);
			LCD_Str(data);
			LCD_Str("%");
            
			itoa(I_Temp,data,10);
			MOVE(1,6);
			LCD_Str(data);
			LCD_Str(".");
			
			itoa(D_Temp,data,10);
			LCD_Str(data);
			DATA(0xDF);
			LCD_Str("C ");
			
			itoa(CheckSum,data,10);
			LCD_Str(data);
			LCD_Str(" ");			
		}
		
		_delay_ms(10);
	}
}


void Request(){
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);
	_delay_ms(20);
	PORTD |= (1<<DHT11_PIN);
}
void Response()				
{
	DDRD &= ~(1<<DHT11_PIN); // PD4 LOW
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()
{
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0); //비트가 0인지 1인지 체크
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN)) //HIGH가 30ms보다 크면
		c = (c<<1)|(0x01);	 //HIGH 상태
		else
		c = (c<<1); //LOW 상태
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}

void MOVE(int y, int x)     //커서 이동
{
	unsigned char data;
	if(y==1) 	data = 0x80 + x - 1;           //1행
	else     	data = 0xc0 + x - 1;            //2행
	COMMAND(data);
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
	_delay_ms(30);	// 전원 투입 후 30ms 이상 지연
	
	//Function set
	COMMAND(0b00101000);
	// 인터페이스(DL)=0(4bit), 라인(N)=1(2라인), 폰트(F)=0(5*8 dot)
	_delay_us(39);	// 39us 이상 지연

	//Display ON/OFF Control
	COMMAND(0b00001100);
	// 화면 표시(D)=1(on), 커서(C)=0(off), 블링크(B)=0(off)
	_delay_us(39);	// 39us 이상 지연

	//Clear Display
	COMMAND(0b00000001);
	// 화면을 클리어하고 , 커서가 홈위치인 0번지로 돌아감.
	_delay_ms(1.53);	// 1.53ms 이상 지연

	//Entry Mode Set
	COMMAND(0b00000110);
	// 커서방향(I/D)=1(address증가), 표시이동(S)=0(이동하지 않음)
}

void LCD_Str(const unsigned char * cString)
{
	while(0 != *cString)
	{
		DATA(*cString);
		++cString;
	}
}

