#include <REGX52.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
   * @brief   起始条件：SCL高电平期间，SDA从高电平切换为低电平
   * @param   无
   * @retval  无
   */
void I2C_Start()
{
	I2C_SDA=1;  
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
   * @brief  终止条件：SCL高电平期间，SDA从低电平切换到高电平
   * @param  无
   * @retval 无
   */
void I2C_Stop()
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
   * @brief  I2C协议中负责传输字节
   * @param  Byte：写入的数据
   * @retval 无
   */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA = Byte&(0x80>>i);   //让每一位每次循环与上一个1,这样位是0就还是0,位是1就还是1
		I2C_SCL = 1;  //需要考虑单片机翻转的时间,单片机翻转的时间应该大于I2C读取数据的时间,如果小于那么就需要延时
		I2C_SCL = 0;
	}
}

/**
   * @brief   I2C协议中负责接收字节
   * @param   无
   * @retval  Byte 类型为unsigned char
   */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i, Byte = 0x00;
	I2C_SDA=1;
	
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;     //SCL高电平时数据开始读取
		if(I2C_SDA)
		{
			Byte|= (0x80>>i);
		}
		I2C_SCL=0;    //SCL低电平时停止读取
	}
	return Byte;
}

/**
   * @brief I2C协议中的发送应答信息,从机发给主机
   * @param 0为应答,1为非应答，接收一个发送应答信息,类型为unsigned char(也可以为bit)
   * @retval 无
   */  
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}


/** 
   * @brief   I2C协议中的接收应答信息,主机发给从机
   * @param   无 	
   * @retval  应答位  类型位为unsigned char  (也可以为bit)
   */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit =0;
	I2C_SDA =1;      //主机让出SDA的控制权
	I2C_SCL =1;
	AckBit=I2C_SDA;
	I2C_SCL = 0;
	return AckBit;
}





