#include <REGX52.H>
#include "UART.h"

void main()
{
  Uart_Init();
  Uart_SendByte(0x51);	
	while(1)
	{
		
	}
}


