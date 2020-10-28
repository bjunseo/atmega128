#define  F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#define DHT11_PIN 6
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

#define LCD_WDATA PORTA     //LCD데이터 포트 정의

#define LCD_WINST PORTA    //

#define LCD_CTRL PORTG    //LCD 제어 포트 정의

#define LCD_EN 0         //LCD 제어(PING0~2)를 효과적으로 하기위한 정의

#define LCD_RW 1

#define LCD_RS 2

#define Byte unsigned char //자주쓰이는 무부호 문자형 자료형을 Byte로 선언


void LCD_Data(Byte ch)

{

	LCD_CTRL |=  (1 << LCD_RS);    //RS=1, R/W=0 으로 데이터 쓰기 싸이클

	LCD_CTRL &= ~(1 << LCD_RW);

	LCD_CTRL |=  (1 << LCD_EN);    //LCD 사용

	_delay_us(50);

	LCD_WDATA = ch;                //데이터 출력

	_delay_us(50);

	LCD_CTRL &= ~(1 << LCD_EN);    //LCD 사용안함



}

//  0         1      2

void LCD_Comm(Byte ch)			   //PG0-EN , PG1-RW, PG2-RS , PG4-TOSC1핀(사용안함)

{							       //LCD_CTRL = LCD제어부 포트(4핀인데 실질적인 사용3핀)

	LCD_CTRL &= ~(1 << LCD_RS);    // RS=0, RW=0 으로 정의함.

	LCD_CTRL &= ~(1 << LCD_RW);

	LCD_CTRL |=  (1 << LCD_EN);    //LCD 사용허가

	_delay_us(50);

	LCD_WINST = ch;                //명령어 쓰기

	_delay_us(50);

	LCD_CTRL &= ~(1 << LCD_EN);    //LCD 사용안함

}



void LCD_CHAR(Byte c)  //한문자 출력 함수

{

	LCD_Data(c);		//CGROM 문자코드의 0x31 ~ 0xFF 는 아스키코드와 일치함!

	_delay_ms(1);

}



void LCD_Str(Byte *str)    //↑문자열을 한문자씩 출력함수로 전달

{	while(*str !=0)

	{

		LCD_CHAR(*str);

		str++;

	}

}





void MOVE(unsigned char col, unsigned char row)  //LCD 포지션 설정
{

	LCD_Comm(0x80 | (row+col*0x40));  // row=행 / col=열 ,DDRAM주소설정

}



void LCD_Clear(void)  // 화면 클리어

{

	LCD_Comm(0x01);

	_delay_ms(2); //1.6ms이상의 실행시간소요로 딜레이필요

}





void LCD_Init(void)   //LCD 초기화

{

	LCD_Comm(0x38);   //데이터 8비트 사용, 5X7도트 , LCD2열로 사용(6)

	_delay_ms(2);

	LCD_Comm(0x38);   //데이터 8비트 사용, 5X7도트 , LCD2열로 사용(6)

	_delay_ms(2);

	LCD_Comm(0x38);   //데이터 8비트 사용, 5X7도트 , LCD2열로 사용(6)

	_delay_ms(2);

	LCD_Comm(0x0e);   //Display ON/OPFF

	_delay_ms(2);

	LCD_Comm(0x06);   //주소 +1 , 커서를 우측으로 이동 (3)

	_delay_ms(2);

	LCD_Clear();

}


void Request();
void Response();
uint8_t Receive_data();

int main(void)
{
	DDRA=0xFF;
	DDRG=0x0F;
	char data[5];
	
	LCD_Init();			// LCD 초기화
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
			LCD_Data(0xDF);
			LCD_Str("C ");
			
			itoa(CheckSum,data,10);
			LCD_Str(data);
			LCD_Str(" ");
		}
		
		_delay_ms(3000);
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






