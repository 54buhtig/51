#include <REGX52.H>

sbit LCD_E=P2^7;
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;

#define LCD_DataPort  P0


/**
   * @brief    ��ʱ1ms����
   * @param    �� 
   * @retval   ��
   */
void LCD_Delay()		//@11.0592MHz1ms
{
	unsigned char i, j;

	
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}


/**
   * @brief   LCD�ڲ��Ĵη�����
   * @param   xΪ����,yΪָ��
   * @retval  ���شη��Ľ��
   */
int LCD_Power(int x,int y)
{
	unsigned char i;
	int Result =1;
	for(i=0;i<y;i++)
	{
		Result*=x;
	}
	return Result;
}

/**
   * @brief   LCDִ��д�������
   * @param   ��Ҫ��ִ���������Ϊunsigned char
   * @retval  ��
   */
void  LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;    //0Ϊ����ָ��
	LCD_RW=0;    //0Ϊд���� 
	LCD_DataPort=Command;       //����ͨ��,8λһ�𷢹�ȥ
	LCD_E=1;        //���øߵ�ƽ
	LCD_Delay();         //��ʱ����
	LCD_E=0;        //���õ͵�ƽ
	LCD_Delay();         //��ʱ����
}


/**
   * @brief    LCDд���ݲ���
   * @param    ��Ҫ���������
   * @retval   ��
   */
void  LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;    //1Ϊ��������
	LCD_RW=0;    //0Ϊд���� 
	LCD_DataPort=Data;    //����ͨ��,8λһ�𷢹�ȥ
	LCD_E=1;        //���øߵ�ƽ
	LCD_Delay();         //��ʱ����
	LCD_E=0;        //���õ͵�ƽ
	LCD_Delay();         //��ʱ����
}

/**
   * @brief     LCD��ʼ������
   * @param     ��
   * @retval    ��
   */
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);   //��λ���ݽӿڣ�������ʾ��5\*7����
	LCD_WriteCommand(0x0C);   //��ʾ�������أ���˸��
	LCD_WriteCommand(0x06);   //���ݶ�/д������AC�Զ���1�����治�� 
	LCD_WriteCommand(0x01);   //���DDRAM��ACֵ����긴λ��������

} 

/**
   * @brief    ���ù��λ��
   * @param    Line:������
   * @param    Column:������
   * @retval
   */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	//���ù���ַ
	if(Line==1)   //����ַ���Ҫ��ʾ�ڵ�һ��,��ַ����0x0*,*������-1
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else         //�ڶ�������ڵ�һ��������0x40
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

/**
   * @brief    ��LCD����ʾһ���ַ�
   * @param    Line:�ַ����ڵ���(1����2)
   * @param    Column:�ַ����ڵ���(1��16)
   * @param    Char:��Ҫ��ʾ���ַ�
   * @retval   ��
   */
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{

	LCD_SetCursor(Line,Column);
	
	//2.��������
	LCD_WriteData(Char);
}

/**
   * @brief  LCD��ʾ�ַ�������
   * @param  Line:�ַ����ڵ���
   * @param  Column:�ַ����ڵ���
   * @param  String:��Ҫ��ʾ���ַ���
   * @retval
   */
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char* String)
{
	unsigned char i;

	LCD_SetCursor(Line,Column);
	
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
   * @brief    ��ʾ�޷��ŵ�����
   * @param    Line:���ֳ��ֵ���
   * @param    Column:���ֳ��ֵ���
   * @param    Number:��Ҫ��ʾ������
   * @param    Length:���ֵ�λ��
   * @retval   ��
   */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);   //���ù��λ��
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Power(10,i-1)%10+0x30);    //��Ҫ�ó�ÿһλ��Ӧ�����ֺ��ڼ���0x30,�������ܵõ�ÿһλ���ַ�����
	}
}


/**
   * @brief     LCD��ʾ�з�������
   * @param     Line:  ������ʾ������
   * @param     Column:  ������ʾ������
   * @param     Number:  ��ʾ����
   * @param     Length:  ��ʾ���ֵ�λ��
   * @retval    ��
   */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;  //�����洢���ֲ���  ���-32768�޷�������ʾ������,����ԭ�����ڳ�����Χ
	LCD_SetCursor(Line,Column);   //���ù��λ��
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;    //�������ȡ��ÿһλ
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Power(10,i-1)%10+0x30);    //��Ҫ�ó�ÿһλ��Ӧ�����ֺ��ڼ���0x30,�������ܵõ�ÿһλ���ַ�����
	}
	
}

/**
   * @brief     LCD��ʾ�з�������
   * @param     Line:  ������ʾ������
   * @param     Column:  ������ʾ������
   * @param     Number:  ��ʾ��16��������
   * @param     Length:  ��ʾ���ֵ�λ��
   * @retval    ��
   */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);   //���ù��λ��
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Power(16,i-1)%16;     //�õ�
		if(SingleNumber<10)
		{
		LCD_WriteData('0'+SingleNumber);    //��Ҫ�ó�ÿһλ��Ӧ�����ֺ��ڼ���0x30,�������ܵõ�ÿһλ���ַ�����
		}
		else
		{
		LCD_WriteData('A'+SingleNumber-10);    //��Ҫ�ó�ÿһλ��Ӧ�����ֺ��ڼ���0x30,�������ܵõ�ÿһλ���ַ�����,-10��Ϊ�˵õ�ƫ����
		}
	}
}

/**
   * @brief     LCD��ʾ�з�������
   * @param     Line:  ������ʾ������
   * @param     Column:  ������ʾ������
   * @param     Number:  ��ʾ��16��������
   * @param     Length:  ��ʾ���ֵ�λ��
   * @retval    ��
   */
void LCD_BinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);   //���ù��λ��
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Power(2,i-1)%2+'0');    //��Ҫ�ó�ÿһλ��Ӧ�����ֺ��ڼ���0x30,�������ܵõ�ÿһλ���ַ�����
	}
}


