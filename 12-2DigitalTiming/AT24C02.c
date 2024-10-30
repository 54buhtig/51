#include <REGX52.H>
#include "I2C.h"


#define AT24C02_ADDRESS  0xA0       //AT24C02�ӻ���ַ


/**
   * @brief    д��һ���ֽ�
   * @param    WordAddress��д����ֵ�ַ
   * @param	   Data��д�������
   * @retval   ��
   */
 
void  AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();                   //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS);  //���ʹӻ���ַ
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);      //�����ֵ�ַ
	I2C_ReceiveAck();
	I2C_SendByte(Data);            //��������
	I2C_ReceiveAck();
	I2C_Stop();                 //��ֹ����
}  

/**
   * @brief  ��ȡһ���ֽڵ�����
   * @param  WordAddress����ȡ���ݵ��ֵ�ַ
   * @retval �Ż��ֽ�����
   */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();                   //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS);  //���ʹӻ���ַ
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);      //�����ֵ�ַ
	I2C_ReceiveAck();    //����Ӧ��

	I2C_Start();                   //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS | 0x01);            //���ʹӻ���ַ������
	I2C_ReceiveAck();    //����Ӧ��
	Data= I2C_ReceiveByte();         //�����ַ�
	I2C_SendAck(1);                   //����Ӧ��
	I2C_Stop();                      //��ֹ���� 
	return Data;
}






