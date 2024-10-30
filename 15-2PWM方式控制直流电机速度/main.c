#include <REGX52.H>
#include "key.h"
#include "Timer0.h"
#include "Delay.h"
#include "Nixie.h"

unsigned char Counter,Compare;
unsigned char KeyNumber,Speed;

sbit LED=P2^0;
sbit Motor = P1^0;


int main()
{
	Timer0_Init();   //初始化定时器
	
	while(1)
	{
		KeyNumber=Key();
		if(KeyNumber == 1)
		{
			Speed++;
			Speed%=4;  //Speed自动清零
			if(Speed==0){Compare=0;}
			if(Speed==1){Compare=60;}
			if(Speed==2){Compare=75;}
			if(Speed==3){Compare=100;}
		}
		Nixie_SetBuf(1,Speed);
		Nixie_Loop();
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
		Motor=1;  //电机的极性与LED相反
	}
	else
	{
//		LED=1;
		Motor=0;  //电机的极性与LED相反
	}

}
