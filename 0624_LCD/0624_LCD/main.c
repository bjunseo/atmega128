#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


//  PC7 PC6 PC5 PC4 PC3 PC2 PC1 PC0
//  DB7 DB6 DB5 DB4          E   RW  RS

int arr[4] = {0,0,0,0};


int i = 0;

void COMMAND(unsigned char byte);	// COMMAND 함수 선언
void DATA(unsigned char byte);		// DATA 함수 선언
void LCD_INIT(void);			// LCD_INIT 함수 선언
void LCD_Num(int ucNum);
void LCD_Str(const unsigned char * cString);
void MOVE(int y,int x);

int main(void)
{
	DDRC = 0xff;
	PORTC = 0x00;
	DDRE = 0x00;
	
	LCD_INIT();
	
	while(1){		
		
		
		if((PINE & 0x10) == 0x00)
		{	
			if(i < 3) i++;
			_delay_ms(200);
		}
	
				
		if((PINE & 0x20) == 0x00){
			if(i > 0) i--;
			_delay_ms(200);
		}
		
		if((PINE & 0x40) == 0x00){
			arr[i] = arr[i] + 1;
			_delay_ms(200);
				
		}
		if((PINE & 0x80) == 0x00){
			arr[i] = arr[i] - 1;
			if(arr[i] < 0) arr[i] = 0;
			_delay_ms(200);
			
		}
       
		
		LCD_Num(arr[0]);
		
		LCD_Num(arr[1]);
		
		LCD_Num(arr[2]);
		
		LCD_Num(arr[3]);
		MOVE(2,i+1);
		DATA("_");
		LCD_INIT();
		
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

void LCD_Num(int ucNum)
{
	static unsigned char ucBuff[] = "1";    //  4자리 확보 보기 쉽게

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

void MOVE(int y, int x)     //커서 이동
{
	unsigned char data;
	if(y==1) 	data = 0x80 + x - 1;           //1행
	else     	data = 0xc0 + x - 1;            //2행
	COMMAND(data);
}
