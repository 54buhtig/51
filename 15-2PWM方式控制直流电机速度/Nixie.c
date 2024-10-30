#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;


u8 Nixie_Buf[9]={0,17,17,17,17,17,17,17,17};  //用来存储我们要扫描到数码管上的数据

u16 NixueTable[]={0x3f,0x06,0x5b,0x4f,
				  0x66,0x6d,0x7d,0x07,
				  0x7f,0x6f,0x77,0xff,
				  0x39,0xbf,0x79,0x71,0x40,0x00};   //用来存储数字对应的数码管数，这些段码存储在数码管的段码表上


/**
   * @brief    用来主函数设置数码管缓存里的数值的
   * @param    Location:第几根数码管
   * @param    Number:显示什么数字
   * @retval   无
   */
void Nixie_SetBuf(u16 Location,u16 Number)
{
	Nixie_Buf[Location]=Number;
}


/**
   * @brief   对数码管进行扫描的函数,属于硬件层面的函数
   * @param   无
   * @retval  无
   */
void Nixie_Scan(u16 Location,u16 Number)
{
	P0=0x00;
	switch(Location)
	{
		case 1:P2_4=0;P2_3=0;P2_2=0;break;
		case 2:P2_4=0;P2_3=0;P2_2=1;break;
		case 3:P2_4=0;P2_3=1;P2_2=0;break;
		case 4:P2_4=0;P2_3=1;P2_2=1;break;
		case 5:P2_4=1;P2_3=0;P2_2=0;break;
		case 6:P2_4=1;P2_3=0;P2_2=1;break;
		case 7:P2_4=1;P2_3=1;P2_2=0;break;
		case 8:P2_4=1;P2_3=1;P2_2=1;break;
	}
	P0=NixueTable[Number];
}

/**
   * @brief     数码管的定时执行函数
   * @param     无
   * @retval    无
   */
void Nixie_Loop(void)
{
	static unsigned char i=1;
	Nixie_Scan(i,Nixie_Buf[i]);
	i++;
	if(i>=9){i=1;}
}



