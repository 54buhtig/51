#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;
	
sbit LED_PORT=P2^4;

void Delay_10us(u16 time)
{
	while(time--);
}
int main()
{
	while(1)
		{
	   LED_PORT=0;
	   Delay_10us(20000);
	   LED_PORT=1;
	   Delay_10us(20000);
	  } 
		return 0;
}