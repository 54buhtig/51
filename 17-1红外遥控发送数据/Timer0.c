#include <REGX52.H>

/**
   *@brief  ��ʱ���ļ�ʱ������ֵ
   *@param  ��
   *@retval	��
  */
	
void Timer0_Init(void)		//1����@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0;		//���ö�ʱ��ֵ
	TH0 = 0;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 0;		//��ʱ��0�����ʱ

}

/**
   * @brief   ���ö�ʱ��ʱ��
   * @param   ��ʱ����ʱʱ��
   * @retval  ��
   */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/** 
   * @brief   �õ���ʱ����ǰ��ʱ��
   * @param   ��
   * @retval  �Żض�ʱ���洢��ʱ��
   */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;  
}

/**
   * @brief   ֹͣ��ʼ��ʱ
   * @param   ��־λ
   *          FlagΪ1ʱ,��ʼ��ʱ
   *          FlagΪ0ʱ,ֹͣ��ʱ
   * @retval  ��
   */
void  Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}
	 



