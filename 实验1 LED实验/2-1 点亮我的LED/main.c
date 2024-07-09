#include <REGX52.H>
typedef unsigned char u8
typedef unsigned int u16
	
sbit LED_1=p2^0

void main()
{
		LED_1=0xFE;
	  while(1);
}