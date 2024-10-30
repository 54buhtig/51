#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
   * @brief   ��ʼ������SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�ƽ�л�Ϊ�͵�ƽ
   * @param   ��
   * @retval  ��
   */
void I2C_Start()
{
	I2C_SDA=1;  
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
   * @brief  ��ֹ������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�ƽ�л����ߵ�ƽ
   * @param  ��
   * @retval ��
   */
void I2C_Stop()
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
   * @brief  I2CЭ���и������ֽ�
   * @param  Byte��д�������
   * @retval ��
   */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);   //��ÿһλÿ��ѭ������һ��1,����λ��0�ͻ���0,λ��1�ͻ���1
		I2C_SCL = 1;  //��Ҫ���ǵ�Ƭ����ת��ʱ��,��Ƭ����ת��ʱ��Ӧ�ô���I2C��ȡ���ݵ�ʱ��,���С����ô����Ҫ��ʱ
		I2C_SCL = 0;
	}
}

/**
   * @brief   I2CЭ���и�������ֽ�
   * @param   ��
   * @retval  Byte ����Ϊunsigned char
   */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i, Byte = 0x00;
	I2C_SDA=1;
	
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;     //SCL�ߵ�ƽʱ���ݿ�ʼ��ȡ
		if(I2C_SDA)
		{
			Byte|= (0x80>>i);
		}
		I2C_SCL=0;    //SCL�͵�ƽʱֹͣ��ȡ
	}
	return Byte;
}

/**
   * @brief I2CЭ���еķ���Ӧ����Ϣ,�ӻ���������
   * @param 0ΪӦ��,1Ϊ��Ӧ�𣬽���һ������Ӧ����Ϣ,����Ϊunsigned char(Ҳ����Ϊbit)
   * @retval ��
   */  
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}


/** 
   * @brief   I2CЭ���еĽ���Ӧ����Ϣ,���������ӻ�
   * @param   �� 	
   * @retval  Ӧ��λ  ����λΪunsigned char  (Ҳ����Ϊbit)
   */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit =0;
	I2C_SDA =1;      //�����ó�SDA�Ŀ���Ȩ
	I2C_SCL =1;
	AckBit=I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}





