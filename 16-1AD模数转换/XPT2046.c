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
	XPT2046_DCLK = 0;   //Ĭ��Ϊ�͵�ƽ
	XPT2046_CS= 0;      //CS�õ͵�ƽ,Ƭѡͨ��
	
	
	for(i=0;i<8;i++)
	{
		XPT2046_DIN = Command & (0x80>>i);
		XPT2046_DCLK = 1;   //�ߵ�ƽ,��������������,�ӻ����(����)
		Delay1ms(1);
		XPT2046_DCLK = 0;   //Ĭ�ϵ͵�ƽ,�½��ز������κ�����
	}
	
	
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK = 1;   //����������������,�ӻ����(����)
		XPT2046_DCLK = 0;   //�͵�ƽ,�½��ض����κ�����	
		if(XPT2046_DOUT)
		{
			ADValue|=(0x8000>>i);  //ÿһλ����һ��1
		}
	}

	XPT2046_CS= 1;      //CS�øߵ�ƽ,Ƭѡ����

	if(Command&0x08)
	{
		return ADValue>>8	;
	}
	else
	{
		return ADValue>>4;	
	}
	
	
}

