#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;
#define Nixue P0
#define MATXUE P1

u16 NixueTable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                  0x7f,0x6f,0x77,0xff,0x39,0xbf,0x79,0x71,0x00};



void Delay_1ms(u16 time)
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





u8 Scan_MatXue(void)
{
		u8 key_value=0;

	  MATXUE=0xf7;           //进行第一行的扫描
		if(MATXUE!=0xf7)
		{
			Delay_1ms(100);
			if(MATXUE!=0xf7)
			{
				switch(MATXUE)
				{
					case 0x77:key_value=1;break;
					case 0xb7:key_value=5;break;
					case 0xd7:key_value=9;break;
					case 0xe7:key_value=13;break;
				}
			}	
		}
		while(MATXUE!=0xf7);
		
		 MATXUE=0xfb;           //进行第二行的扫描
		if(MATXUE!=0xfb)
		{
			Delay_1ms(100);
			if(MATXUE!=0xfb)
			{
				switch(MATXUE)
				{
					case 0x7b:key_value=2;break;
					case 0xbb:key_value=6;break;
					case 0xdb:key_value=10;break;
					case 0xeb:key_value=14;break;
				}
			}	
		}
		while(MATXUE!=0xfb);   
		
		 MATXUE=0xfd;          //进行第三行的扫描
		if(MATXUE!=0xfd)
		{
			Delay_1ms(100);
			if(MATXUE!=0xfd)
			{
				switch(MATXUE)
				{
					case 0x7d:key_value=3;break;
					case 0xbd:key_value=7;break;
					case 0xdd:key_value=11;break;
					case 0xed:key_value=15;break;
				}
			}	
		}
		while(MATXUE!=0xfd);

		 MATXUE=0xfe;        //进行第四行的扫描
		if(MATXUE!=0xfe)
		{
			Delay_1ms(100);
			if(MATXUE!=0xfe)
			{
				switch(MATXUE)
				{
					case 0x7e:key_value=4;break;
					case 0xbe:key_value=8;break;
					case 0xde:key_value=12;break;
					case 0xee:key_value=16;break;
				}
			}	
		}
		while(MATXUE!=0xfe);
	return key_value;
}
int main()
{
	u8 key=0;
	while(1)
	{
		key=Scan_MATXUE();
		if(key)
		Nixue=NixueTable[key-1];
	}
	return 0;
}



