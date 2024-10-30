#include <REGX52.H>
#include "Delay.h"

unsigned char KeyNum;


/**
   * @brief   �ⲿ��ȡ��ֵ����
   * @param   ��
   * @retval  �����°����ļ�ֵ
   */
unsigned char Key(void)
{
	unsigned char Temp = 0;
	Temp = KeyNum;
	KeyNum=0;
	return Temp;
}


/**
   * @brief   ��ȡ������״̬
   * @param   ��
   * @retval  ���ر����°������߼�ֵ
   */
unsigned char Key_GetState()
{
	unsigned char KeyNumber = 0;
	
	if(P3_1==0){KeyNumber = 1;}
	if(P3_0==0){KeyNumber = 2;}
	if(P3_2==0){KeyNumber = 3;}
	if(P3_3==0){KeyNumber = 4;}
	
	return KeyNumber;
}


/**
   * @brief   ���̵Ķ�ʱִ�к���
   * @param   ��
   * @retval  ��
   */
void Key_Loop()
{
	static unsigned char NowState,LastState;   //��¼��20ms��״̬�͵�ǰ��״̬
	LastState = NowState;                      //��¼ǰ20ms��״̬
	NowState = Key_GetState();
	if(LastState==1&&NowState==0)
	{
		KeyNum=1;
	}
	if(LastState==2&&NowState==0)
	{
		KeyNum=2;
	}
	if(LastState==3&&NowState==0)
	{
		KeyNum=3;
	}
	if(LastState==4&&NowState==0)
	{
		KeyNum=4;
	}
}


