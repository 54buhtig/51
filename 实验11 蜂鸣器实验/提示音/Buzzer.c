#include <REGX52.H>
#include "Delay.h"

//�������˿�
sbit Buzzer  = P1^5;

/**
   *@brief  ������˽����ʱ����
   *@param  ��
   *@retval  ��
  */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	i = 227;
	while (--i);
}


/**
   *@brief   ����������
   *@param    ����ʱ��
   *@retval   ��
  */

void Buzzer_Time(unsigned int ms)
{
		unsigned int i;
		for(i=0;i<ms*2;i++)
		{
			Buzzer = !Buzzer;
			Buzzer_Delay500us();
		}
}



