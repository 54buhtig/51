#include <REGX52.H>

/**
   *@brief  ��ʱ������ֵ
   *@param  ��
   *@retval	��
  */

void Timer0Init(void)		//1����@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0=1;
	EA=1;
	PT0=1;
}


/*��ʱ�����жϷ������ģ��*/
//void Timer0(void) interrupt 1
//{
//	TH0= 0xFC;
//	TL0= 0x66;
//	T0Count++;
//	if(T0Count>=1000)
//	{
//		T0Count=0;
//		P2_1=~P2_1;
//	}
//}
