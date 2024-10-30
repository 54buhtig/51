#include <REGX52.H>
#include "DS18B02.h"
#include "LCD1602.h"
#include "Delay.h"
#include "AT24C02.h"
#include "key.h"
#include "Timer0.h"

float T,TShow;   //TShow用于处理温度小于0时T改变的情况
char TLow,THigh;
unsigned char KeyNumber;


int main()
{
	Timer0_Init();
	/*TLow和THigh的初始化,初始化就是将存储到DS18C20的值取出来*/
	DS18B20_ConvertT();
	Delay1ms(1000);
	THigh = AT24C02_ReadByte(0);   //读出默认值
	TLow = AT24C02_ReadByte(1);	   //读出默认值
	if(THigh>125||TLow<-55||THigh<=TLow)   //防止第一次数值超出限定范围
	{
		THigh = 20;
		TLow = 15;
	}
	
	
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");
	LCD_ShowString(2,9,"TL:");
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);
		
	while(1)
	{
		KeyNumber = Key();
		/*温度读取及显示*/
		DS18B20_ConvertT();
		T = DS18B20_ReadT();
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow = -T;
		}
		else 
		{
			LCD_ShowChar(1,3,'+');
			TShow = T;
		}
		LCD_ShowNum(1,4,T,3);    //显示整数部分
		LCD_ShowChar(1,7,'.');   //显示小数点
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);  //显示小数部分 
		
		
		
		/*上下阈值设置及显示*/
		if(KeyNumber)
		{
			if(KeyNumber == 1)
			{
				THigh++;
				if(THigh>125){THigh=125;}
			}
			if(KeyNumber == 2)
			{
				THigh--;
				if(THigh<=TLow){THigh++;}				
			}
			if(KeyNumber == 3)
			{
				TLow++;
				if(TLow>=THigh){TLow--;}				
			}
			if(KeyNumber == 4)
			{
				TLow--;
				if(TLow<-55){TLow=-55;}

			}
			LCD_ShowSignedNum(2,4,THigh,3);
			LCD_ShowSignedNum(2,12,TLow,3);
			
			/*设置完阈值后写入到AT24C02中*/
			AT24C02_WriteByte(0,THigh);
			Delay1ms(5);
			AT24C02_WriteByte(1,TLow);
			Delay1ms(5);
		
		}
		if(T>THigh)
		{
			LCD_ShowString(1,13,"OV:H");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,13,"OV:L");
		}
		else
		{
			LCD_ShowString(1,13,"    ");
		}
	}
	return ;
}

/**
   * @brief   定时器中断服务函数
   * @param
   * @retval
   */
void Timer0(void) interrupt 1
{
	static unsigned int  T0Count;
	TH0= 0xFC;
	TL0= 0x66;
	T0Count++;
	if(T0Count>=20)
	{
		T0Count=0;
		Key_Loop();
	}
}


