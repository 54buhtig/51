#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define DS1302_SECOND   0x80
#define DS1302_MINUTE   0x82
#define DS1302_HOUR     0x84
#define DS1302_DATE     0x86
#define DS1302_MONTH    0x88
#define DS1302_DAY      0x8A
#define DS1302_YEAR     0x8C
#define DS1302_WP       0x8E

//�����������洢��ʼ����������ʱ��������
unsigned char DS1302_Time[] = {23,3,23,15,10,57,4};

//DS1302ģ��ĳ�ʼ��
void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

//��DS1302����д����
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i;
	DS1302_CE = 1;
	for(i=0;i<8;i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO = Data & (0x01<<i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
		DS1302_SCLK = 0;
		DS1302_CE = 0;
}

//��DS1302���ж�����
unsigned char DS1302_ReadByte(unsigned char Command)
{ 
	unsigned char i,Data = 0x00;
	Command = Command + 0x01;    //��ԭ���������Ķ�����תΪд����
	 
	DS1302_CE = 1;
	for(i=0;i<8;i++)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO){Data |= (0x01<<i);}
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

//������ʼ��ʱ��
void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR ,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH ,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE ,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR ,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE ,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}

//����ʵʱ��ȡ�Լ���õ�ʱ��
void DS1302_ReadTime()
{
	unsigned char Temper;
	
	Temper = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = Temper/16*10+Temper%16;
	
	Temper = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = Temper/16*10+Temper%16;
	
	Temper = DS1302_ReadByte(DS1302_DATE );
	DS1302_Time[2] = Temper/16*10+Temper%16;
	
	Temper = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = Temper/16*10+Temper%16;
	
	Temper = DS1302_ReadByte(DS1302_MINUTE );
	DS1302_Time[4] = Temper/16*10+Temper%16;
	
	Temper = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = Temper/16*10+Temper%16;
}



