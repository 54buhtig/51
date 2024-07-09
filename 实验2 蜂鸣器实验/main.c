#include <reg52.h>



typedef unsigned int u16;
typedef unsigned char u8;

sbit BEEP=P2^5;

void delay_10us(u8 ten_us)
{
	while(ten_us--);
}

int mian()
{
	u16 i=2000;
	while(1)
	{
		while(i--)
		{
			BEEP=0;
			delay_10us(50);
			BEEP=1;
			delay_10us(150);
		}
		i=0;
		BEEP=0;
	}
	return 0;
}
			