#include <REGX52.H>

sbit OneWire_DQ = P3^7;


/**
   * @brief   �����߿�ʼ�ź�
   * @param   ��
   * @retval  ���شӻ���Ӧ�źţ�0Ϊͨ����1Ϊ��ͨ��
   */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;  //Ӧ��λ
	
	EA = 0;         //��ʼʱ���رն�ʱ��,��ֹ����
	
	OneWire_DQ=1;
	OneWire_DQ=0;
	

	i = 227;while (--i);   //��ʱ500us
	
	OneWire_DQ=1;   //�ͷ�����
	
	
	i = 29;while (--i);    //��ʱ70us
	AckBit = OneWire_DQ;  //��ȡ���ߵ�ƽ
	i = 227;while (--i);   //��ʱ500us����������ʼ�źŵ�ʱ������

	EA = 1;   //ʱ�������򿪶�ʱ��
	
	return AckBit;
}


/**
   * @brief   �������õ����߷���һλ
   * @param   ���͵�λ��    0or1
   * @retval  ��
   */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA = 0;         //��ʼʱ���رն�ʱ��,��ֹ����

	OneWire_DQ=0;       //��������
	i = 3;while (--i);  //��ʱ 10us
	OneWire_DQ = Bit;
	
	i = 22;while (--i);    //��ʱ 50us
	
	OneWire_DQ = 1;
	EA = 1;   //ʱ�������򿪶�ʱ��	
}

/**
   * @brief    �������õ����߽���һλ
   * @param    ��
   * @retval   ����λ��,����ֵΪ0��1
   */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	EA = 0;         //��ʼʱ���رն�ʱ��,��ֹ����
		
	OneWire_DQ=0;        //��������
	i = 1;while (--i);   //��ʱ9us
	OneWire_DQ=1;        //�ͷ�����
	i = 1;while (--i);   //��ʱ9us
	Bit = OneWire_DQ;
	i = 22;while (--i);  //��ʱ 50us
	EA = 1;   //ʱ�������򿪶�ʱ��
	return Bit;
}


/**
   * @brief   ���õ����߷���һ���ֽ�
   * @param   ���͵��ֽ�
   * @retval  ��
   */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
}



/**
   * @brief   �������õ����߽���һ���ֽ�
   * @param   ��
   * @retval  ���յ����ֽ�
   */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i;
	unsigned char Byte = 0x00;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReceiveBit()) {Byte |= (0x01<<i);} 
	}
	return Byte;
}

