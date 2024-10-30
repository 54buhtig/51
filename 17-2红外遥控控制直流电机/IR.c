#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned  int IR_Time;   //���м�ʱ
unsigned  char IR_State;  //�����߷���״̬,Ĭ��Ϊ����״̬

unsigned char IR_Data[4];   //���ݻ���
unsigned char IR_pData;  //��ʾ��ǰ�洢��λ��


unsigned char IR_DataFlag;   //��־λ�ж��Ƿ�õ�����
unsigned char IR_RepeatFlag; //NEC��׼���ط���־ 
unsigned char IR_Address;    //������ǽ��յ����յ�ַ
unsigned char IR_Command;    //������ǽ��յ�����������

unsigned char TestNum;

void IR_Init(void)
{
	Timer0_Init();  //��ʼ����ʱ��
	Int0_Init();    //��ʼ���ⲿ�ж�1
}


unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}


unsigned char IR_GetRepeat(void)
{
	if(IR_RepeatFlag==1)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}
	
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

void Int0_Routine(void) interrupt 0
{
	if(IR_State==0)
	{		
		Timer0_SetCounter(0);   //����ʱ������
		Timer0_Run(1);         //��ʱ������
		IR_State = 1;         //�������״̬��Ϊ1
	}
	else if(IR_State==1)    //��Ѱ��ʼ�ź�
	{
		IR_Time = Timer0_GetCounter();//��ü�ʱ����ǰ��ʱ��
		Timer0_SetCounter(0);   //����ʱ������,�����´�ʹ��
		if(IR_Time>13500-3300  && IR_Time<13500+3300 )   //��ʼ�ź��ж�
		{
//			P2=0;
			IR_State = 2;         //������״̬��Ϊ2
		}
		else if(IR_Time>10368-500  && IR_Time<10368+500 )
		{
//			P2=0;
//			LCD_ShowNum(1,8,IR_Time,6);

			IR_RepeatFlag=1;    //�ط���־λ��1
			IR_State = 0;      //��������ź���1
			Timer0_Run(0);         //��ʱ��ֹͣ
		}	
		else  //�����źŽ��մ�������
		{
			IR_State = 1;      //��������ź���1,������Ѱ��ʼ�ź�
		}
	}	
	else if(IR_State==2)   //����
	{
		IR_Time = Timer0_GetCounter();//��ü�ʱ����ǰ��ʱ��
		Timer0_SetCounter(0);   //����ʱ������,�����´�ʹ��
		if(IR_Time>1120-500 &&IR_Time<1120+500 )   //�洢0
		{
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));  
			IR_pData++;
		}
		else if(IR_Time>2250-500 &&IR_Time<2250+500 )   //�洢1
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));  
			IR_pData++;
		}
		else   //�յ�������Ϣ
		{
			IR_pData=0;   //�����ݷ���
			IR_State=1;   //��ʼ��Ѱ��ʼ�ź�
		}
		if(IR_pData>=32)  //���ݻ���������
		{
			P2=0;
			IR_pData=0;     //��λָ���λ
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))  //У�������Ƿ���ȷ
			{
				IR_Address=IR_Data[0];  //��λ�ô��λ�ñ�������
				IR_Command=IR_Data[2];  //�������������������
				IR_DataFlag=1;          //���ݱ�־λ��1
			}
			Timer0_Run(0);  //��ʱ��ֹͣ
			IR_State=0;    //������մ��ڿ���״̬
		}
	}
}	

