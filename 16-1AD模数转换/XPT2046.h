#ifndef __XPT2046_H_
#define __XPT2046_H_


#define  XPT2046_XP_8  0x9C	  //��x��  (ox8c)��������
#define  XPT2046_YP_8  0xDC     //��y��
#define  XPT2046_VBAT_8  0xAC     //���ص�ѹ
#define  XPT2046_AUX_8  0xEC     //��


#define  XPT2046_XP_12  0x94	  //��x��  (ox8c)��������
#define  XPT2046_YP_12  0xD4     //��y��
#define  XPT2046_VBAT_12  0xA4     //���ص�ѹ
#define  XPT2046_AUX_12  0xE4     //��


unsigned int XPT2046_ReadAD(unsigned char Command);




#endif
