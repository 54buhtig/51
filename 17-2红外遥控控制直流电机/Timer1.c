#include <REGX52.H>

/**
   *@brief  ��ʱ��1����ֵ
   *@param  ��
   *@retval	��
  */

void Timer1_Init(void)		//100΢��@11.0592MHz
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
//	TL0 = 0xAE;		//���ö�ʱ��ʼֵ
//	TH0 = 0xFB;		//���ö�ʱ��ʼֵ
	TL1 = 0x9C;
	TH1 = 0xFF;
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1=1;          //��ʱ��1ʹ��
	EA=1;          //�ж���ʹ�ܿ��ش�
	PT1=0;        //�ж����ȼ�Ϊ0
}


/*��ʱ�����жϷ������ģ��*/ 
//void Timer1_Routine(void) interrupt 3
//{
//	TL1 = 0xAE;		//���ö�ʱ��ʼֵ
//	TH1 = 0xFB;		//���ö�ʱ��ʼֵ
//	T1Count++;
//	if(T1Count>=1000)
//	{
//		T1Count=0;
//	}
//}
