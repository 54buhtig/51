#include <REGX52.H>
#include "Timer1.h"


sbit Motor = P1^0;   //������Ŷ���
unsigned char Counter,Compare;


void Montor_Init(void)
{
		Timer1_Init();   //��ʼ����ʱ��1
}


void Montor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
	
}


void Timer1_Routine(void) interrupt 3
{
//	static unsigned char TCount0;
	TL1 = 0x9C;
	TH1 = 0xFF;
	Counter++;
	Counter%=100;   //��counter����
	if(Counter<Compare)
	{
//		LED=0;
		Motor=1;  //����ļ�����LED�෴
	}
	else
	{
//		LED=1;
		Motor=0;  //����ļ�����LED�෴
	}

}
