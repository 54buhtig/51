#include <REGX52.H>
#include "MatrixLD.h"
#include "Timer0.h"

sbit RCK = P3^5;
sbit SCK = P3^6;
sbit SER = P3^4;

static unsigned char count = 0;
static unsigned int T0Count = 0;
unsigned char MatrixCol[] = {0xFF,0x08,0x08,0x08,0xFF,0x00,0x1F,0x15,
														 0x1D,0x00,0x00,0xFF,0x01,0x02,0x00,0xFF,
														 0x02,0x00,0x08,0x14,0x22,0x22,0x14,0x08,
	                           0x00,0xF1,0x1F,0x10,0x44,0x4C,0x54,0x64,
														 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};

void main ()
{
		 SCK = 0;
		 RCK = 0;
      while(1)
    {
			 Matrixled(0,MatrixCol[0]);
			 Matrixled(1,MatrixCol[1]);
			 Matrixled(2,MatrixCol[2]);
		   Matrixled(3,MatrixCol[3]);
			 Matrixled(4,MatrixCol[4]);
			 Matrixled(5,MatrixCol[5]);
			 Matrixled(6,MatrixCol[6]);
			 Matrixled(7,MatrixCol[7]);
    }
}

//void Timer0(void) interrupt 1
//{
//	TH0= 0xFC;
//	TL0= 0x66;
//	T0Count++;
//	if(T0Count>=1000)
//	{
//		T0Count=0;
//		count++;
//	}
//}

