#include <REGX52.H>
#include "key.h"
#include "Timer0.h"
#include "Delay.h"
#include "Nixie.h"

unsigned char Counter,Compare;
unsigned char i;


sbit DA = P2^1;


int main()
{
	Timer0_Init();   //初始化定时器
	
	while(1)
	{
		for(i=0;i<100;i++)
		{
			Compare = i;
			Delay1ms(10);
		}
		for(i=100;i>0;i--)
		{
			Compare = i;
			Delay1ms(10);
		}
	}
	return ;
}


void Timer0(void) interrupt 1
{
//	static unsigned char TCount0;
	TL0 = 0x9C;
	TH0 = 0xFF;
	Counter++;
	Counter%=100;   //将counter重置
	if(Counter<Compare)
	{
//		LED=0;
		DA=1;  //电机的极性与LED相反
	}
	else
	{
//		LED=1;
		DA=0;  //电机的极性与LED相反
	}

}
