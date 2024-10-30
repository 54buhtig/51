#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"


//蜂鸣器端口
sbit Buzzer = P2^5;

#define SPEED  500


#define P   0
#define L1  1
#define L1_ 2
#define L2  3
#define L2_ 4
#define L3  5
#define L4  6
#define L4_ 7
#define L5  8
#define L5_ 9
#define L6  10
#define L6_ 11
#define L7  12


#define M1  13
#define M1_ 14
#define M2  15
#define M2_ 16
#define M3  17
#define M4  18
#define M4_ 19
#define M5  20
#define M5_ 21
#define M6  22
#define M6_ 23
#define M7  24

#define H1  25
#define H1_ 26
#define H2  27
#define H2_ 28
#define H3  29
#define H4  30
#define H4_ 31
#define H5  32
#define H5_ 33
#define H6  34
#define H6_ 35
#define H7  36






unsigned int FrqTable[]={
			0,
			63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,
			64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,
			65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283};
						//音调
						 
						 
						 
//unsigned char Music1[]={ 
//	13,4,
//	13,4,
//	20,4,
//	20,4,
//	22,4,
//	22,4,
//	20,4+4,
//	18,4,
//	18,4,
//	17,4,
//	17,4,
//	15,4,
//	15,4,
//	13,4+4
//	
//	0xff
//};     //乐谱


//code属性的数组会存进flash(ROM)里面,属性为只读,适合一些值比较大,非常占用RAM空间,而且定义好不需要再修改
//例如数码管的断码表,大的表格
unsigned char code Music2[]=
{
	//1
	P,4,
	P,4,
	P,4,
	M6,2,
	M7,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	M7,4+4+4,
	M3,2,
	M3,2,
	
	//2
	M6,4+2,
	M5,2,
	M6,4,
	H1,4,
	
	M5,4+4+4,
	M3,4,
	
	M4,4+2,
	M3,2,
	M4,4,
	H1,4,
	
	//3
	M3,4+4,
	P,2,
	H1,2,
	H1,2,
	H1,2,
	
	M7,4+2,
	M4_,2,
	M4,4,
	M7,4,
	
	M7,4+4,
	P,4,
	M6,2,
	M7,2,
	
	//4
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	M7,4+4+4,
	M3,2,
	M3,2,
	
	M6,4+2,
	M5,2,
	M6,4,
	H1,4,
	
	//5
	M5,4+4+4,
	M2,2,
	M3,2,
	
	M4,4,
	H1,2,
	M7,2+2,
	H1,2+4,
	
	H2,2,
	H2,2,
	H3,2,
	H1,2+4+4,
	
	//6
	H1,2,
	M7,2,
	M6,2,
	M6,2,
	M7,4,
	M5_,4,
	
	M6,4+4+4,
	H1,2,
	H2,2,
	
	H3,4+2,
	H2,2,
	H3,4,
	H5,4,
	
	//7
	H2,4+4+4,
	M5,2,
	M5,2,
	
	H1,4+2,
	M7,2,
	H1,4,
	H3,4,
	
	H3,4+4+4+4,
	
	//8
	M6,2,
	M7,2,
	H1,4,
	M7,4,
	H2,2,
	H2,2,
	
	H1,4+2,
	M5,2+4+4,
	
	H4,4,
	H3,4,
	H2,4,
	H1,4,
	
	//9
	H3,4+4+4,
	H3,4,
	
	H6,4+4,
	H5,4,
	H5,4,
	
	H3,2,
	H2,2,
	H1,4+4,
	P,2,
	H1,2,
	
	//10
	H2,4,
	H1,2,
	H2,2,
	H2,4,
	H5,4,
	
	H3,4+4+4,
	H3,4,
	
	H6,4+4,
	H5,4+4,
	
	//11
	H3,2,
	H2,2,
	H1,4+4,
	P,2,
	H1,2,
	
	H2,4,
	H1,2,
	H2,2+4,
	M7,4,
	
	M6,4+4+4,
	M6,2,
	M7,2,
	
	
	
	0xff   //乐谱结束标志
};


						 
unsigned char FreqSelect,MusicSelect;   //音乐频率选择和乐谱索引选择

void main()
{
		Timer0Init();
		while(1)
		{
			if(Music2[MusicSelect]!=0xff)
			{
				FreqSelect = Music2[MusicSelect];
				MusicSelect++;   //后续显示时长
				Delay1ms(SPEED/4*Music2[MusicSelect]);
				MusicSelect++;  //后续显示频率
				TR0= 0;   //关闭计数器
				Delay1ms(5);  //模拟抬手动作
				TR0= 1;  //打开计数器
			}
			else
			{
				TR0 = 0;  //关闭计数器
				while(1);
			}
		}
}


void Timer0(void) interrupt 1
{
	if(FrqTable[FreqSelect])
	{
		TL0= FrqTable[FreqSelect]%256;  //设置重装载值
		TH0= FrqTable[FreqSelect]/256;  //设置重装载值
		Buzzer=!Buzzer;
	}
	
//	TL0= 0x18;  //设置重装载值
//	TH0= 0xFC;  //设置重装载值
//	Buzzer=!Buzzer;
}

