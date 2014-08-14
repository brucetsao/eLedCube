#ifndef __IR_H__
#define	__IR_H__

#include "STC15Fxxxx.h"
#include "Time.h"
//sbit IR=P3^3;            //红外接口标志,用中断方式不用定义


extern bit irprosok;
extern bit irreceok;
extern uchar ircode[4];
extern void IR_pros(void); //红外解码函数外部声明




#endif