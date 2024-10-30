#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;


u8 Nixie_Buf[9]={0,17,17,17,17,17,17,17,17};  //�����洢����Ҫɨ�赽������ϵ�����

u16 NixueTable[]={0x3f,0x06,0x5b,0x4f,
				  0x66,0x6d,0x7d,0x07,
				  0x7f,0x6f,0x77,0xff,
				  0x39,0xbf,0x79,0x71,0x40,0x00};   //�����洢���ֶ�Ӧ�������������Щ����洢������ܵĶ������


/**
   * @brief    ������������������ܻ��������ֵ��
   * @param    Location:�ڼ��������
   * @param    Number:��ʾʲô����
   * @retval   ��
   */
void Nixie_SetBuf(u16 Location,u16 Number)
{
	Nixie_Buf[Location]=Number;
}


/**
   * @brief   ������ܽ���ɨ��ĺ���,����Ӳ������ĺ���
   * @param   ��
   * @retval  ��
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
   * @brief     ����ܵĶ�ʱִ�к���
   * @param     ��
   * @retval    ��
   */
void Nixie_Loop(void)
{
	static unsigned char i=1;
	Nixie_Scan(i,Nixie_Buf[i]);
	i++;
	if(i>=9){i=1;}
}



