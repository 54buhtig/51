#include <REGX52.H>
/**
   *@brief  ���ڳ�ʼ��
   *@param  ��
   *@retval ��
  */

void Uart_Init(void)			//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}

/**
   *@brief    ͨ�����ڷ����޷�������
   *@param		�޷�����
   *@retval		��
  */

void Uart_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
		TI=0;
}
