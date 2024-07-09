#include <REGX52.H>
#include "Timer0.h"
#include "key.h"
#include <INTRINS.H>


unsigned int T0Count=0;
unsigned char keyNum=0,LCDMode;

int main()
{
  Timer0Init();
	P2=0xFE;
	while(1)
	{
		keyNum=key();
		if(keyNum)
		{
			if(keyNum==1)
				LCDMode++;
			if(LCDMode>=2)LCDMode=0;
		}
	}
}

void Timer0(void) interrupt 1
{
	TH0= 0xFC;
	TL0= 0x66;
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		if(LCDMode==0)
			P2=_crol_(P2,1);
		if(LCDMode==1)
			P2=_cror_(P2,1);
	}
}