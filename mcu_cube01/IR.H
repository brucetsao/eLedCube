#ifndef __IR_H__
#define	__IR_H__

#include "STC15Fxxxx.h"
#include "Time.h"
//sbit IR=P3^3;            //����ӿڱ�־,���жϷ�ʽ���ö���


extern bit irprosok;
extern bit irreceok;
extern uchar ircode[4];
extern void IR_pros(void); //������뺯���ⲿ����




#endif