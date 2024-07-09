#include <REGX52.H>
#include "UART.h"

void main ()
{
		Uart_Init();
      while(1)
      {
				
      }
}

void Uart_Rountine() interrupt 4
{
	if(RI==1)
	{
		RI=0;
		P2=SBUF;
		Uart_SendByte(SBUF);
	}	
}

