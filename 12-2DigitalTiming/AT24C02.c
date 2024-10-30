#include <REGX52.H>
#include "I2C.h"


#define AT24C02_ADDRESS  0xA0       //AT24C02从机地址


/**
   * @brief    写入一个字节
   * @param    WordAddress：写入的字地址
   * @param	   Data：写入的数据
   * @retval   无
   */
 
void  AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();                   //起始条件
	I2C_SendByte(AT24C02_ADDRESS);  //发送从机地址
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);      //发送字地址
	I2C_ReceiveAck();
	I2C_SendByte(Data);            //发送数据
	I2C_ReceiveAck();
	I2C_Stop();                 //终止条件
}  

/**
   * @brief  读取一个字节的数据
   * @param  WordAddress：读取数据的字地址
   * @retval 放回字节数据
   */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();                   //起始条件
	I2C_SendByte(AT24C02_ADDRESS);  //发送从机地址
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);      //发送字地址
	I2C_ReceiveAck();    //接收应答

	I2C_Start();                   //起始条件
	I2C_SendByte(AT24C02_ADDRESS | 0x01);            //发送从机地址读命令
	I2C_ReceiveAck();    //接收应答
	Data= I2C_ReceiveByte();         //接收字符
	I2C_SendAck(1);                   //发送应答
	I2C_Stop();                      //终止条件 
	return Data;
}







