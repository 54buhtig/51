#include <REGX52.H>
#include "LCD1602.h"
#include "Timer0.h"
#include "Delay.h"

unsigned char Sec=56,Min=58,Hour=23;
unsigned int T0Count=0;


void main()
{
	Timer0Init();
	LCD_Init();
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	while(1)
	{
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
		if(Sec>59)
		{
			Min++;
			Sec=0;
			if(Min>59)
			{
				Hour++;
				Min=0;
				if(Hour==24)
					Hour=0;
			}
		}
	}
}

void Timer0(void) interrupt 1
{
	TH0= 0xFC;
	TL0= 0x66;
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		Sec++;
	}
}