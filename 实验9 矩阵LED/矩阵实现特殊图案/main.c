#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit SRCLK = P3^6;
sbit RCK = P3^5;
sbit SER = P3^4;

#define MatrixLED_port P0

void _74HC595_transform_port(unsigned char Byte)
{
	int i;
	for(i=0;i<8;i++)
	{
		SER = Byte & (0x80>>i);
		SRCLK = 1;
		SRCLK = 0;
	}
	RCK = 1;
	RCK = 0;
}

void MatrixLED(unsigned char column,unsigned char Data)
{	
	_74HC595_transform_port(Data);
	MatrixLED_port = ~(0x80 >> column);
	Delay100us();
	MatrixLED_port = 0xff;
}

void main ()
{
		SRCLK = 0;
		RCK = 0;
      while(1)
    {  //0x3E,0x49,0xF5,0x85,0x85,0xF5,0x49,0x7E,
			//0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF,
      MatrixLED(0,0xFF);
			MatrixLED(1,0x81);
			MatrixLED(2,0x81);
			MatrixLED(3,0x81);
			MatrixLED(4,0x81);
			MatrixLED(5,0x81);
			MatrixLED(6,0x81);
			MatrixLED(7,0xFF);
			/*MatrixLED(2,0x01);
			MatrixLED(1,0x02);
			MatrixLED(3,0x42);
			MatrixLED(4,0x53);
			MatrixLED(5,0xfe);
			MatrixLED(6,0xa3);
			MatrixLED(7,0x64);
			MatrixLED(0,0xdb);*/
    }
}

//void Timer0(void) interrupt 1
//{
//	TH0= 0xFC;
//	TL0= 0x66;
//	MatrixLED_port = 0xff;
//}

