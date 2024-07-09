#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

void Delay(u16 time)
{
	u8 i,j;
	while(time--)
	{
		i=2;
		j=239;
		do
		{
			while(--j);
		}while(--i);
	}
}

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
	Delay(1);
	P0=0x00;
}

int main()
{
  Nixue(3,12);
	while(1)
	{
		Nixue(1,1);  //1
		 Delay(2000);	
		Nixue(2,2);   //2
		 Delay(2000);	
		Nixue(3,3);   //3
    Delay(2000);	
		Nixue(4,4);     //4
		 Delay(2000);	
		Nixue(5,5);     //5
		 Delay(2000);	
		Nixue(6,6);    //6
    Delay(2000);	
		Nixue(7,7);     //7
		 Delay(2000);	
		Nixue(8,8);    //8
    Delay(2000);	
	}
}

