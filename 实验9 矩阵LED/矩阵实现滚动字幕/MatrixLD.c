#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit RCK = P3^5;
sbit SCK = P3^6;
sbit SER = P3^4;

//unsigned char MatrixCol[] = {0xFF,0x08,0x08,0x08,0xFF,0x00,0x1F,0x15,
//														 0x1D,0x00,0x00,0xFF,0x01,0x02,0x00,0xFF,
//														 0x02,0x00,0x08,0x14,0x22,0x22,0x14,0x08,
//	                           0x00,0xF1,0x1F,0x10,0x44,0x4C,0x54,0x64,
//														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

void MatrixLED_Init()
{
	SCK = 0;
	RCK = 0;
}

void _74_Byte_transfer(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER = Byte & (0x80>>i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

void Matrixled(unsigned char column,unsigned char Data)
{
	P0 = ~(0x80 >> column);
	_74_Byte_transfer(Data);
	P0 = 0xff;
}

void Matrixcoll()
{
	unsigned char i;
	if(count>28)
		count = 0;
	for(i=0;i<8;i++)
	{
		Matrixled(i,MatrixCol[i+count]);
	}
}	
