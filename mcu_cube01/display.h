#ifndef __DIS_PLAY_H__
#define __DIS_PLAY_H__
#include "STC15Fxxxx.h"
#include "74HC595.H"
#include "Time.h"
#include "Exti.h"
#include "IR_KEY.H"
#include "povdat.h" 
#include "EEPROM.H"
extern uchar dat1,dat2,dat3,dat4,dat5,dat6;
extern uchar pic_id;

extern uint picaddr;
extern uint picaddr_end,picaddr_start;	//EEPROM结束，开始地址
//extern bit pic_ch_flag;
//extern bit Time0_flag;	//定时器T0中断标志位
extern void display_pic();
extern void pic_chang(void);
extern uchar xdata pov_pic[180][4];
extern uchar xdata pov_hz[180][2];

#endif