#include <REGX52.H>


/**
   * @brief   ���ⲿ�ж�0���г�ʼ��
   * @param   ��
   * @retval  ��
   */
void Int0_Init(void)
{
	IT0=1;    //ѡ�񴥷���ʽ   0Ϊ�͵�ƽ������1Ϊ�½��ش���
	IE0=0;    //�жϱ�־λ��0
	EX0=1;    //�ⲿ�ж�0ʹ�ܴ�
	EA=1;     //ʹ���ܿ��ش�
	PX0=1;   //���ⲿ�жϽϸߵ����ȼ�,��֤�źŵ�ʵʱ��
}


//void Int0_Routine(void) interrupt 0
//{
//	
//}	


