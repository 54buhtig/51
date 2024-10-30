#include <REGX52.H>
#include "Delay.h"

unsigned char KeyNum;

unsigned char Key(void)
{
	unsigned char Temp = 0;
	Temp = KeyNum;
	KeyNum=0;
	return Temp;
}

unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	
	if(P3_1==0){KeyNumber = 1;}
	if(P3_0==0){KeyNumber = 2;}
	if(P3_2==0){KeyNumber = 3;}
	if(P3_3==0){KeyNumber = 4;}
	
	return KeyNumber;
}


/**
   * @brief   键盘的定时执行函数
   * @param   无
   * @retval  无
   */
void Key_Loop()
{
	static unsigned char NowState,LastState;   //记录上20ms的状态和当前的状态
	LastState = NowState;                      //记录前20ms的状态
	NowState = Key_GetState();
	if(LastState==1&&NowState==0)
	{
		KeyNum=1;
	}
	if(LastState==2&&NowState==0)
	{
		KeyNum=2;
	}
	if(LastState==3&&NowState==0)
	{
		KeyNum=3;
	}
	if(LastState==4&&NowState==0)
	{
		KeyNum=4;
	}
}


