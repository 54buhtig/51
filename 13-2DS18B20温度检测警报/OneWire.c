#include <REGX52.H>

sbit OneWire_DQ = P3^7;


/**
   * @brief   单总线开始信号
   * @param   无
   * @retval  返回从机响应信号，0为通过，1为不通过
   */
unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;  //应答位
	
	EA = 0;         //开始时序后关闭定时器,防止干扰
	
	OneWire_DQ=1;
	OneWire_DQ=0;
	

	i = 227;while (--i);   //延时500us
	
	OneWire_DQ=1;   //释放总线
	
	
	i = 29;while (--i);    //延时70us
	AckBit = OneWire_DQ;  //读取总线电平
	i = 227;while (--i);   //延时500us，将整个开始信号的时序走完

	EA = 1;   //时序结束后打开定时器
	
	return AckBit;
}


/**
   * @brief   主机利用单总线发送一位
   * @param   发送的位数    0or1
   * @retval  无
   */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA = 0;         //开始时序后关闭定时器,防止干扰

	OneWire_DQ=0;       //拉低总线
	i = 3;while (--i);  //延时 10us
	OneWire_DQ = Bit;
	
	i = 22;while (--i);    //延时 50us
	
	OneWire_DQ = 1;
	EA = 1;   //时序结束后打开定时器	
}

/**
   * @brief    主机利用单总线接收一位
   * @param    无
   * @retval   返回位数,返回值为0或1
   */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	EA = 0;         //开始时序后关闭定时器,防止干扰
		
	OneWire_DQ=0;        //拉低总线
	i = 1;while (--i);   //延时9us
	OneWire_DQ=1;        //释放总线
	i = 1;while (--i);   //延时9us
	Bit = OneWire_DQ;
	i = 22;while (--i);  //延时 50us
	EA = 1;   //时序结束后打开定时器
	return Bit;
}


/**
   * @brief   利用单总线发送一个字节
   * @param   发送的字节
   * @retval  无
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
   * @brief   主机利用单总线接收一个字节
   * @param   无
   * @retval  接收到的字节
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

