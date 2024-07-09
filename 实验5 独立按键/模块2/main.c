#include <REGX52.H>

void Delay(unsigned int xms)		
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
	}
}

void  main()
{
	while(1)
	{
		if(P3_1==0)
		{
			Delay(20);
			while(P3_1==0);
			Delay(20);
			P2_7=~P2_7;
		}
	}	
}



