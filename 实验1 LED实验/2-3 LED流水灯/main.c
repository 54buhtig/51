#include <REGX52.H>
#include <INTRINS.H>

#define LED_PORT p2

typedef unsigned char u8
typedef unsigned int u16
	
void Delay_10us(u16 time)
{
	while(time--);   
}

int main()
{
	int i=0;
	LED_PORT=0xfe;
	Delay_10us(50000);
	for(i=0;i<7;i++)
	{
		LED_PORT=_crol_(LED_PORT,1);
		Delay_10us(50000);
	}
	for(i=0;i<7;i++)
	{
		LED_PORT=_cror_(LED_PORT,1);
		Delay_10us(50000);
	}
	return 0;
}


