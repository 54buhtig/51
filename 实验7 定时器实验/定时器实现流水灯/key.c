#include <REGX52.H>
#include "Delay.h"

/**
   *@brief   获取独立键盘键值
   *@param    无
   *@retval    返回键值
  */

unsigned char key()
{
	unsigned char keyNumber=0;
	if(P3_0==0){Delay1ms(20);while(P3_0==0);Delay1ms(20);keyNumber=1;}
	if(P3_1==0){Delay1ms(20);while(P3_1==0);Delay1ms(20);keyNumber=2;}
	if(P3_2==0){Delay1ms(20);while(P3_2==0);Delay1ms(20);keyNumber=3;}
	if(P3_3==0){Delay1ms(20);while(P3_3==0);Delay1ms(20);keyNumber=4;}
	return keyNumber;
}