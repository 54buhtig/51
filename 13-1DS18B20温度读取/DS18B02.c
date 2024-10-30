#include <REGX52.H>
#include "OneWire.h"



#define DS18B20_CONVERT_T  0x44
#define DS18B20_SKIP_ROM   0xCC
#define DS18B20_READ_SCRATCHPAD  0xBE


/**
   * @brief    刷新检测温度的函数
   * @param    无
   * @retval   无
   */
void DS18B20_ConvertT(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}

/**
   * @brief    读取检测温度的函数
   * @param    无
   * @retval   返回读取的温度,
   */
float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReceiveByte();
	TMSB = OneWire_ReceiveByte();

	Temp = (TMSB<<8) | TLSB;
	T = Temp /16.0;   
	return T;
}


