#include <REGX52.H>
#include "Timer1.h"


sbit Motor = P1^0;   //电机引脚定义
unsigned char Counter,Compare;


void Montor_Init(void)
{
		Timer1_Init();   //初始化定时器1
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
	Counter%=100;   //将counter重置
	if(Counter<Compare)
	{
//		LED=0;
		Motor=1;  //电机的极性与LED相反
	}
	else
	{
//		LED=1;
		Motor=0;  //电机的极性与LED相反
	}

}
