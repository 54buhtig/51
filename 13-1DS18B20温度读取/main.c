#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B02.h"
#include "Delay.h"
float T;


int main()
{
	DS18B20_ConvertT();    //提前更新检测温度,防止读出默认值
	Delay1ms(1000);
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	while(1)
	{
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(2,1,'-');
			T = -T;
		}
		else
		{
			LCD_ShowChar(2,1,'+');
		}
		LCD_ShowNum(2,2,T,3);
		LCD_ShowChar(2,5,'.');   //显示小数点
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);   //显示小数部分
	}
	return ;
}

