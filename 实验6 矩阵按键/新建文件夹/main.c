#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "Mixture.h"

int main()
{
  unsigned	int keyname=0;
	unsigned int password=0,count=0; 
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		keyname=Matrixkey();
		if(keyname)
		{
		if(keyname<10&&count<4)     //S1~S9为密码键
		{
			password=10*password;
			password=keyname+password;
			count++;
			LCD_ShowNum(2,1,password,4);
		}
		else if(keyname==10)        //S10为确认键
		{
			if(password==1314)
				LCD_ShowString(1,12,"OK ");
			else
				LCD_ShowString(1,12,"ERR");
			count=0;           //重置密码和按键次数
			password=0;
		}		
	}
		}	
}
