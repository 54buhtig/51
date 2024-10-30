#ifndef _TIMER_H_
#define _TIMER_H_

void Timer0_Init(void);
void Timer0_SetCounter(unsigned int Value);
unsigned int Timer0_GetCounter(void);
void  Timer0_Run(unsigned char Flag);

#endif