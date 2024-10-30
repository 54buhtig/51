#include <REGX52.H>

/**
   *@brief  定时器改计时器赋初值
   *@param  无
   *@retval	无
  */
	
void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0无需计时

}

/**
   * @brief   设置定时器时间
   * @param   定时器计时时间
   * @retval  无
   */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/** 
   * @brief   得到定时器当前的时间
   * @param   无
   * @retval  放回定时器存储的时间
   */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;  
}

/**
   * @brief   停止或开始计时
   * @param   标志位
   *          Flag为1时,开始计时
   *          Flag为0时,停止计时
   * @retval  无
   */
void  Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}
	 



