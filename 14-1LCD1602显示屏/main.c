#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

int main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(1,9,77,3);
	LCD_ShowSignedNum(1,13,-99,3);
	LCD_ShowHexNum(2,1,0xF5,2);
	LCD_BinNum(2,4,0xF5,8);   //51无法识别二进制数表示
	LCD_ShowChar(2,13,0xDF);
	LCD_ShowChar(2,14,'C');
	LCD_ShowChar(2,16,0xE2);
	
	
	LCD_ShowString(1,16,"Welcome to China!");
	while(1)
	{
		LCD_WriteCommand(0x18);
		Delay1ms(500);
	}
	return ;
}

