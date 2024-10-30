#include <REGX52.H>
#include "LCD1602.h"
#include "key.h"
#include "Delay.h"
#include "AT24C02.h"

unsigned char Data;

unsigned char KeyNum = 0;
unsigned int Num;


int main()
{
	LCD_Init();
	LCD_ShowNum(1,1,Num,5);
//	AT24C02_WriteByte(1,178);         //字地址范围为0-255
//	Delay1ms(5);                     //延时5ms延时是因为从RAM到ROM速度下降,周期最长可达到5ms,因此延时,不延时数据写不进去,AT24C02默认存储位为1
//	Data = AT24C02_ReadByte(1);             //读取字地址为1的空间里的数据
//	LCD_ShowNum(2,1,Data,3);
	
	
	
	while(1)
	{
		KeyNum=Key();
		if(KeyNum==1)
		{
			Num++;
			LCD_ShowNum(1,1,Num,5);	
		}
		else if(KeyNum==2)
		{
			Num--;
			LCD_ShowNum(1,1,Num,5);
		}
		else if(KeyNum==3)
		{
			AT24C02_WriteByte(0,Num%256);  //数据为16位,需要分别存储低8位和高8位,0地址处存低8位
			Delay1ms(5); 
			AT24C02_WriteByte(1,Num/256);  //1地址处存高8位
			Delay1ms(5); 
			LCD_ShowString(2,1,"Write OK");
			Delay1ms(1000); 
			LCD_ShowString(2,1,"        ");
		}
		else if(KeyNum==4)
		{
			Num=AT24C02_ReadByte(0);  //数据为16位,需要分别存储低8位和高8位,0地址处存低8位
			Num|=(AT24C02_ReadByte(1)<<8);  //1地址处存高8位
			LCD_ShowNum(1,1,Num,5);	        //读出后立马显示在LCD屏幕上
			LCD_ShowString(2,1,"Read OK");
			Delay1ms(1000); 
			LCD_ShowString(2,1,"       ");
		}
	}
	return;
}
