#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned  int IR_Time;   //进行计时
unsigned  char IR_State;  //红外线方波状态,默认为空闲状态

unsigned char IR_Data[4];   //数据缓存
unsigned char IR_pData;  //表示当前存储的位数


unsigned char IR_DataFlag;   //标志位判断是否得到数据
unsigned char IR_RepeatFlag; //NEC标准的重发标志 
unsigned char IR_Address;    //存放我们接收的最终地址
unsigned char IR_Command;    //存放我们接收的最终命令码

unsigned char TestNum;

void IR_Init(void)
{
	Timer0_Init();  //初始化计时器
	Int0_Init();    //初始化外部中断1
}


unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}


unsigned char IR_GetRepeat(void)
{
	if(IR_RepeatFlag==1)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}
	
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

void Int0_Routine(void) interrupt 0
{
	if(IR_State==0)
	{		
		Timer0_SetCounter(0);   //将计时器清零
		Timer0_Run(1);         //计时器启动
		IR_State = 1;         //红外接收状态置为1
	}
	else if(IR_State==1)    //搜寻起始信号
	{
		IR_Time = Timer0_GetCounter();//获得计时器当前的时间
		Timer0_SetCounter(0);   //将计时器清零,方便下次使用
		if(IR_Time>13500-3300  && IR_Time<13500+3300 )   //起始信号判定
		{
//			P2=0;
			IR_State = 2;         //红外线状态置为2
		}
		else if(IR_Time>10368-500  && IR_Time<10368+500 )
		{
//			P2=0;
//			LCD_ShowNum(1,8,IR_Time,6);

			IR_RepeatFlag=1;    //重发标志位置1
			IR_State = 0;      //红外接收信号置1
			Timer0_Run(0);         //计时器停止
		}	
		else  //处理信号接收错误的情况
		{
			IR_State = 1;      //红外接收信号置1,继续搜寻起始信号
		}
	}	
	else if(IR_State==2)   //解码
	{
		IR_Time = Timer0_GetCounter();//获得计时器当前的时间
		Timer0_SetCounter(0);   //将计时器清零,方便下次使用
		if(IR_Time>1120-500 &&IR_Time<1120+500 )   //存储0
		{
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));  
			IR_pData++;
		}
		else if(IR_Time>2250-500 &&IR_Time<2250+500 )   //存储1
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));  
			IR_pData++;
		}
		else   //收到错误信息
		{
			IR_pData=0;   //将数据放弃
			IR_State=1;   //开始搜寻起始信号
		}
		if(IR_pData>=32)  //数据缓存区存满
		{
			P2=0;
			IR_pData=0;     //将位指针归位
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))  //校验数据是否正确
			{
				IR_Address=IR_Data[0];  //将位置存进位置变量里面
				IR_Command=IR_Data[2];  //将命令存进命令变量里面
				IR_DataFlag=1;          //数据标志位置1
			}
			Timer0_Run(0);  //定时器停止
			IR_State=0;    //红外接收处于空闲状态
		}
	}
}	

