#ifndef _DS1302_H_
#define _DS1302_H_

//对于变量要记得加extern属性
extern char DS1302_Time[];

void DS1302_Init();
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_WriteByte(unsigned char Command,Data);
void DS1302_SetTime();
void DS1302_ReadTime();


#endif