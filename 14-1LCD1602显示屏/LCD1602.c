#include <REGX52.H>

sbit LCD_E=P2^7;
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;

#define LCD_DataPort  P0


/**
   * @brief    延时1ms函数
   * @param    无 
   * @retval   无
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
   * @brief   LCD内部的次方函数
   * @param   x为底数,y为指数
   * @retval  返回次方的结果
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
   * @brief   LCD执行写命令操作
   * @param   想要的执行命令，类型为unsigned char
   * @retval  无
   */
void  LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;    //0为发送指令
	LCD_RW=0;    //0为写操作 
	LCD_DataPort=Command;       //并口通信,8位一起发过去
	LCD_E=1;        //先置高电平
	LCD_Delay();         //延时函数
	LCD_E=0;        //后置低电平
	LCD_Delay();         //延时函数
}


/**
   * @brief    LCD写数据操作
   * @param    需要传输的数据
   * @retval   无
   */
void  LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;    //1为发送数据
	LCD_RW=0;    //0为写操作 
	LCD_DataPort=Data;    //并口通信,8位一起发过去
	LCD_E=1;        //先置高电平
	LCD_Delay();         //延时函数
	LCD_E=0;        //后置低电平
	LCD_Delay();         //延时函数
}

/**
   * @brief     LCD初始化函数
   * @param     无
   * @retval    无
   */
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);   //八位数据接口，两行显示，5\*7点阵
	LCD_WriteCommand(0x0C);   //显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);   //数据读/写操作后，AC自动加1，画面不动 
	LCD_WriteCommand(0x01);   //清除DDRAM和AC值，光标复位（清屏）

} 

/**
   * @brief    设置光标位置
   * @param    Line:光标的行
   * @param    Column:光标的列
   * @retval
   */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	//设置光标地址
	if(Line==1)   //如果字符想要显示在第一行,地址就是0x0*,*就是列-1
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else         //第二行相对于第一行增加了0x40
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

/**
   * @brief    在LCD上显示一个字符
   * @param    Line:字符所在的行(1或者2)
   * @param    Column:字符所在的列(1到16)
   * @param    Char:想要显示的字符
   * @retval   无
   */
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{

	LCD_SetCursor(Line,Column);
	
	//2.发送数据
	LCD_WriteData(Char);
}

/**
   * @brief  LCD显示字符串函数
   * @param  Line:字符所在的行
   * @param  Column:字符所在的列
   * @param  String:想要显示的字符串
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
   * @brief    显示无符号的数字
   * @param    Line:数字出现的行
   * @param    Column:数字出现的列
   * @param    Number:需要显示的数字
   * @param    Length:数字的位数
   * @retval   无
   */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);   //设置光标位置
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Power(10,i-1)%10+0x30);    //需要拿出每一位对应的数字后在加上0x30,这样就能得到每一位的字符数字
	}
}


/**
   * @brief     LCD显示有符号数字
   * @param     Line:  数字显示的行数
   * @param     Column:  数字显示的列数
   * @param     Number:  显示数字
   * @param     Length:  显示数字的位数
   * @retval    无
   */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;  //用来存储数字部分  解决-32768无法正常显示的问题,问题原因在于超出范围
	LCD_SetCursor(Line,Column);   //设置光标位置
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;    //方便后面取出每一位
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Power(10,i-1)%10+0x30);    //需要拿出每一位对应的数字后在加上0x30,这样就能得到每一位的字符数字
	}
	
}

/**
   * @brief     LCD显示有符号数字
   * @param     Line:  数字显示的行数
   * @param     Column:  数字显示的列数
   * @param     Number:  显示的16进制数字
   * @param     Length:  显示数字的位数
   * @retval    无
   */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);   //设置光标位置
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Power(16,i-1)%16;     //得到
		if(SingleNumber<10)
		{
		LCD_WriteData('0'+SingleNumber);    //需要拿出每一位对应的数字后在加上0x30,这样就能得到每一位的字符数字
		}
		else
		{
		LCD_WriteData('A'+SingleNumber-10);    //需要拿出每一位对应的数字后在加上0x30,这样就能得到每一位的字符数字,-10是为了得到偏移量
		}
	}
}

/**
   * @brief     LCD显示有符号数字
   * @param     Line:  数字显示的行数
   * @param     Column:  数字显示的列数
   * @param     Number:  显示的16进制数字
   * @param     Length:  显示数字的位数
   * @retval    无
   */
void LCD_BinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);   //设置光标位置
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Power(2,i-1)%2+'0');    //需要拿出每一位对应的数字后在加上0x30,这样就能得到每一位的字符数字
	}
}


