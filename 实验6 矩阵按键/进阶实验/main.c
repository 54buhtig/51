#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "Mixture.h"

int main()
{
	int keyname=0;
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey:");
	while(1)
	{
		keyname=(int)Matrixkey();
		if(keyname)
		{
			LCD_ShowNum(2,1,keyname,2);
		}
	}
}
