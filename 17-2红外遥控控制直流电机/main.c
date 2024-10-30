#include <REGX52.H>
#include "key.h"
#include "Montor.h"
#include "Delay.h"
#include "Nixie.h"
#include "IR.h"
#include "LCD1602.h"

unsigned char Command,Speed;

sbit LED=P2^0;



int main()
{ 
	Montor_Init();   //电机初始化
	IR_Init();       //红外初始化
	while(1)
	{
		if(IR_GetDataFlag())
		{
			Command = IR_GetCommand();   //获取红外遥控键值
			
			if(Command == IR_0){Speed = 0;}
			if(Command == IR_1){Speed = 1;}
			if(Command == IR_2){Speed = 2;}
			if(Command == IR_3){Speed = 3;}
			

			if(Speed==0){Montor_SetSpeed(0);}
			if(Speed==1){Montor_SetSpeed(60);}
			if(Speed==2){Montor_SetSpeed(75);}
			if(Speed==3){Montor_SetSpeed(100);}
		}
		Nixie_SetBuf(1,Speed);
		Nixie_Loop();
	}
	return ;
}



