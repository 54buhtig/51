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
//	AT24C02_WriteByte(1,178);         //�ֵ�ַ��ΧΪ0-255
//	Delay1ms(5);                     //��ʱ5ms��ʱ����Ϊ��RAM��ROM�ٶ��½�,������ɴﵽ5ms,�����ʱ,����ʱ����д����ȥ,AT24C02Ĭ�ϴ洢λΪ1
//	Data = AT24C02_ReadByte(1);             //��ȡ�ֵ�ַΪ1�Ŀռ��������
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
			AT24C02_WriteByte(0,Num%256);  //����Ϊ16λ,��Ҫ�ֱ�洢��8λ�͸�8λ,0��ַ�����8λ
			Delay1ms(5); 
			AT24C02_WriteByte(1,Num/256);  //1��ַ�����8λ
			Delay1ms(5); 
			LCD_ShowString(2,1,"Write OK");
			Delay1ms(1000); 
			LCD_ShowString(2,1,"        ");
		}
		else if(KeyNum==4)
		{
			Num=AT24C02_ReadByte(0);  //����Ϊ16λ,��Ҫ�ֱ�洢��8λ�͸�8λ,0��ַ�����8λ
			Num|=(AT24C02_ReadByte(1)<<8);  //1��ַ�����8λ
			LCD_ShowNum(1,1,Num,5);	        //������������ʾ��LCD��Ļ��
			LCD_ShowString(2,1,"Read OK");
			Delay1ms(1000); 
			LCD_ShowString(2,1,"       ");
		}
	}
	return;
}
