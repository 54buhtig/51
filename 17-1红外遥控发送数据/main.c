#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"

unsigned char Number;
unsigned char Address,Command;

unsigned char Test;

int main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADDR  CMD  NUM");
	LCD_ShowString(2,1,"00    00   000");

	IR_Init();
	
	while(1)
	{
		if(IR_GetDataFlag() || IR_GetRepeat() )  //收到消息或者连发消息都能进入以下操作  
										         //实现连发就在于:1.标志位  2.上一个数据并未被覆盖
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			
			
			
			

			LCD_ShowHexNum(2,1,Address,2);
			LCD_ShowHexNum(2,7,Command,2);
			
			if(Command==IR_VOL_MINUS)   //按下“vol-”
			{
				Number--;
			}
			if(Command==IR_VOL_ADD)  //按下“vol+”
			{
				Number++;
			}
			LCD_ShowNum(2,12,Number,3);
		}
	}
	return ;
}

//void Int0_Routine(void) interrupt 0
//{
//	Number--;
//}	

