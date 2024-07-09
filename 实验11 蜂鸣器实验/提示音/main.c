#include <REGX52.H>
#include "Timer0.h"
#include "Nixie.h"
#include "Buzzer.h"
#include "key.h"

unsigned char KeyNum;

void main ()
{
		Nixue(1,0);
      while(1)
    {
			KeyNum = Key();
			if(KeyNum)
			{
					Buzzer_Time(100);
					Nixue(1,KeyNum);
			}
    }
}
