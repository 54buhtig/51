#include <REGX52.H>

/**
   *@brief  定时器1赋初值
   *@param  无
   *@retval	无
  */

void Timer1_Init(void)		//100微秒@11.0592MHz
{
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;		//设置定时器模式
//	TL0 = 0xAE;		//设置定时初始值
//	TH0 = 0xFB;		//设置定时初始值
	TL1 = 0x9C;
	TH1 = 0xFF;
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1=1;          //定时器1使能
	EA=1;          //中断总使能开关打开
	PT1=0;        //中断优先级为0
}


/*计时器的中断服务程序模板*/ 
//void Timer1_Routine(void) interrupt 3
//{
//	TL1 = 0xAE;		//设置定时初始值
//	TH1 = 0xFB;		//设置定时初始值
//	T1Count++;
//	if(T1Count>=1000)
//	{
//		T1Count=0;
//	}
//}
