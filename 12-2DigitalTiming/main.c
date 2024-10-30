#include <REGX52.H>
#include "Timer0.h"
#include "Delay.h"
#include "Nixie.h"
#include "Key.h"
#include "I2C.h"
#include "AT24C02.h"

unsigned char KeyNumber; 
unsigned char Minute,Sec,MiniSec;    //ʱ����
unsigned  char RunFlag;      //�����־λ

int main()
{
	Timer0_Init();  //��ʼ����ʱ��
	while(1)
	{
		KeyNumber=Key();
		if(KeyNumber==1)
		{
			RunFlag=!RunFlag;
		}
		if(KeyNumber==2)
		{
			Minute=0;
			Sec=0;
			MiniSec=0;
		}
		if(KeyNumber==3)
		{
			AT24C02_WriteByte(0,Minute);   //д��������
			Delay1ms(5);
			AT24C02_WriteByte(1,Sec);   //д������
			Delay1ms(5);
			AT24C02_WriteByte(2,MiniSec);   //дmini������
			Delay1ms(5);
		}
		if(KeyNumber==4)
		{
			Minute=AT24C02_ReadByte(0);  //����������
			Sec=AT24C02_ReadByte(1);  //��������
			MiniSec=AT24C02_ReadByte(2);  //��mini������
		}
		
			//������mini��д�뵽����ܵĻ�����
			Nixie_SetBuf(8,Minute/10);
			Nixie_SetBuf(7,Minute%10);
			Nixie_SetBuf(6,16);
			Nixie_SetBuf(5,Sec/10);
			Nixie_SetBuf(4,Sec%10);
			Nixie_SetBuf(3,16);
			Nixie_SetBuf(2,MiniSec/10);
			Nixie_SetBuf(1,MiniSec%10);	
	}
	return ;
}
/**
   * @brief    ����mini��仯�Ķ�ʱ����
   * @param    ��
   * @retval   ��
   */
void MiniSec_Loop(void)
{
	if(RunFlag)             //Ϊ��ʵ�������ͣ�ͼ������õ������־λ
	{
		MiniSec++; 
		if(MiniSec>=100)
		{
			MiniSec=0;
			Sec++;
			if(Sec>=60)
			{
				Sec=0;
				Minute++;
				if(Minute>=60)
				{
					Minute=0;
				}
			}
		}
	}
}

void Timer0(void) interrupt 1
{
	static unsigned int T0Count1,T0Count2,T0Count3;
	TH0= 0xFC;
	TL0= 0x66;
	T0Count1++;
	if(T0Count1>=20)
	{
		T0Count1=0;
		Key_Loop();    //ʵ�ּ�����
	}
	T0Count2++;
	if(T0Count2>=2)
	{
		T0Count2=0;
		Nixie_Loop();    //ʵ��ˢ�������
	}
	T0Count3++;
	if(T0Count3>=10)
	{
		T0Count3=0;
		MiniSec_Loop();    //ʵ�ַ���mini��仯�ĺ���
	}
}
