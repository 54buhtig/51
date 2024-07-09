#include <REGX52.H>
#include "Delay.h"

//蜂鸣器端口
sbit Buzzer  = P1^5;

/**
   *@brief  蜂鸣器私有延时函数
   *@param  无
   *@retval  无
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	i = 227;
	while (--i);
}


/**
   *@brief   蜂鸣器函数
   *@param    延音时间
   *@retval   无
  */

void Buzzer_Time(unsigned int ms)
{
		unsigned int i;
		for(i=0;i<ms*2;i++)
		{
			Buzzer = !Buzzer;
			Buzzer_Delay500us();
		}
}



