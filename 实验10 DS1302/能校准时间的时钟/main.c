#include <REGX52.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "Timer0.h"
#include "key.h"

unsigned char KeyNum,KeyNumboot,MODE,TimeSelect,TimeFlashFlag,T0Count;

void Timeshow()
{
			DS1302_ReadTime();
	    LCD_ShowNum(1,1,DS1302_Time[0],2);
			LCD_ShowNum(1,4,DS1302_Time[1],2);
			LCD_ShowNum(1,7,DS1302_Time[2],2);
			LCD_ShowNum(2,1,DS1302_Time[3],2);
			LCD_ShowNum(2,4,DS1302_Time[4],2);
			LCD_ShowNum(2,7,DS1302_Time[5],2);
}

void Timeset()
{
		if(KeyNum == 2)
		{
			TimeSelect++;
			TimeSelect %= 6;
		}
		if(KeyNum==3)
		{
			DS1302_Time[TimeSelect]++;
			if(DS1302_Time[0]>99){DS1302_Time[0] = 0;}
			if(DS1302_Time[1]>12){DS1302_Time[1] = 1;}
			
			if(DS1302_Time[1]==1|| DS1302_Time[1]==3 ||DS1302_Time[1]==5 ||DS1302_Time[1]==7
         ||DS1302_Time[1]==8 || DS1302_Time[1]==10|| DS1302_Time[1]==12)
			{if(DS1302_Time[2]>31) DS1302_Time[2] = 1; }
			else if(DS1302_Time[1]==4 || DS1302_Time[1]==6|| DS1302_Time[1]==9 
				     || DS1302_Time[1]==11)
			{if(DS1302_Time[2]>30) DS1302_Time[2]=1;}
			else
			{
				if(DS1302_Time[0]%4 == 0)
				{
					if(DS1302_Time[2]>29) DS1302_Time[2] = 1;
			  }
				else 
				{
					if(DS1302_Time[2]>28) DS1302_Time[2] = 1;
				}
			}
			
			if(DS1302_Time[3]>23){DS1302_Time[3] = 0;}
			if(DS1302_Time[4]>59){DS1302_Time[4] = 0;}
			if(DS1302_Time[5]>59){DS1302_Time[5] = 0;}
		}
		if(KeyNum == 4)
		{
			DS1302_Time[TimeSelect]--;
			if(DS1302_Time[0]<0){DS1302_Time[0] = 99;}
			if(DS1302_Time[1]<1){DS1302_Time[1] = 12;}
			
			if(DS1302_Time[1]==1 || DS1302_Time[1]==3||DS1302_Time[1]==5 ||DS1302_Time[1]==7
         ||DS1302_Time[1]==8 || DS1302_Time[1]==10 || DS1302_Time[1]==12)
			{if(DS1302_Time[2]<1) DS1302_Time[2] = 31;
       if(DS1302_Time[2]>31) DS1302_Time[2] = 1;}
			else if(DS1302_Time[1]==4||DS1302_Time[1]==6|| DS1302_Time[1]==9 
				     || DS1302_Time[1]==11)
			{if(DS1302_Time[2]<1) DS1302_Time[2]=30;
			 if(DS1302_Time[2]>30) DS1302_Time[2]=1;}
			else
			{
				if(DS1302_Time[0]%4 == 0)
				{
					if(DS1302_Time[2]<1) DS1302_Time[2] = 29;
					if(DS1302_Time[2]>29) DS1302_Time[2] = 1;
				}
				else 
				{
					if(DS1302_Time[2]<1) DS1302_Time[2] = 28;
					if(DS1302_Time[2]>28) DS1302_Time[2] = 1;
				}
			}
			if(DS1302_Time[3]<0){DS1302_Time[3] = 23;}
			if(DS1302_Time[4]<0){DS1302_Time[4] = 59;}
			if(DS1302_Time[5]<0){DS1302_Time[5] = 59;}
		}	
		LCD_ShowNum(1,12,TimeSelect,2);
}

void main ()
{
		LCD_Init();
	  DS1302_Init();
	  Timer0Init();
	  DS1302_SetTime();
		LCD_ShowString(1,1,"  -  -");
	  LCD_ShowString(2,1,"  :  :");
	 
      while(1)
    { 
			KeyNum = Key();
			LCD_ShowNum(2,12,KeyNum,2);
			LCD_ShowNum(1,15,MODE,2);
			if(KeyNum)
			{
				if(KeyNum == 1)MODE = 1;
				if(KeyNum >= 2){MODE = 2,DS1302_SetTime();};
			}
			switch(MODE)
			{
				case 1 :Timeshow();break;
				case 2 :Timeset();break;
			}
    }
}






