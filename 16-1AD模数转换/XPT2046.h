#ifndef __XPT2046_H_
#define __XPT2046_H_


#define  XPT2046_XP_8  0x9C	  //测x正  (ox8c)基础配置
#define  XPT2046_YP_8  0xDC     //测y正
#define  XPT2046_VBAT_8  0xAC     //测电池电压
#define  XPT2046_AUX_8  0xEC     //测


#define  XPT2046_XP_12  0x94	  //测x正  (ox8c)基础配置
#define  XPT2046_YP_12  0xD4     //测y正
#define  XPT2046_VBAT_12  0xA4     //测电池电压
#define  XPT2046_AUX_12  0xE4     //测


unsigned int XPT2046_ReadAD(unsigned char Command);




#endif
