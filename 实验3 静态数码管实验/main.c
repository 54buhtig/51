#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

u16 NixueTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0xff,0x39,0xbf,0x79,0x71,0x00};

void Nixue(u16 Location,u16 Number)
{
	switch(Location)
	{
		case 1:P2_4=0;P2_3=0;P2_2=0;break;
	  case 2:P2_4=0;P2_3=0;P2_2=1;break;
		case 3:P2_4=0;P2_3=1;P2_2=0;break;
		case 4:P2_4=0;P2_3=1;P2_2=1;break;
		case 5:P2_4=1;P2_3=0;P2_2=0;break;
		case 6:P2_4=1;P2_3=0;P2_2=1;break;
		case 7:P2_4=1;P2_3=1;P2_2=0;break;
		case 8:P2_4=1;P2_3=1;P2_2=1;break;
	}
	P0=NixueTable[Number];
}

int main()
{
  Nixue(3,12);
	while(1)
	{
	}
}