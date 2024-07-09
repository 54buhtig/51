#include <REGX52.H>

int main()
{
	while(1)
	{
		if(P3_1==0)
			P2=~(0x01);
		else
			P2=~(0x00);
	}
	return 0;
}