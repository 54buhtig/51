#include <REGX52.H>


/**
   * @brief   对外部中断0进行初始化
   * @param   无
   * @retval  无
   */
void Int0_Init(void)
{
	IT0=1;    //选择触发方式   0为低电平触发，1为下降沿触发
	IE0=0;    //中断标志位置0
	EX0=1;    //外部中断0使能打开
	EA=1;     //使能总开关打开
	PX0=1;   //给外部中断较高的优先级,保证信号的实时性
}


//void Int0_Routine(void) interrupt 0
//{
//	
//}	


