#include <REGX52.H>
#include "Delay.h"

sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;


unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int ADValue;
	XPT2046_DCLK = 0;   //默认为低电平
	XPT2046_CS= 0;      //CS置低电平,片选通过
	
	
	for(i=0;i<8;i++)
	{
		XPT2046_DIN = Command & (0x80>>i);
		XPT2046_DCLK = 1;   //高电平,上升沿主机输入,从机输出(接收)
		Delay1ms(1);
		XPT2046_DCLK = 0;   //默认低电平,下降沿不读入任何数据
	}
	
	
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK = 1;   //先上升沿主机输入,从机输出(接收)
		XPT2046_DCLK = 0;   //低电平,下降沿读入任何数据	
		if(XPT2046_DOUT)
		{
			ADValue|=(0x8000>>i);  //每一位或上一个1
		}
	}

	XPT2046_CS= 1;      //CS置高电平,片选结束

	if(Command&0x08)
	{
		return ADValue>>8	;
	}
	else
	{
		return ADValue>>4;	
	}
	
	
}

