#ifndef __Time_H__
#define	__Time_H__

#include "STC15Fxxxx.h"
#include "intrins.h"
#include "74HC595.H"
#include "Exti.h"
//#include "UART.h"
extern uchar day,month,year,week,second,minute,hour;  //外部函数要用到必须声明为外部全局变量
extern uint T0_S;

extern uint line_now;		//表盘修正现在列、修正值
extern uint line_vol;
extern uchar irtime;	    //红外遥控解码时间标准
extern uint Pt;
extern bit Time0_flag;		//定时器0中断标志
extern bit pic_ch_flag;		//图片切换标志
extern bit  pic_red_ok;		//图片读缓冲标志
extern bit pic_rd_flag;		//图片完成标志
extern uchar speed;			//电机速度变量
extern uchar speedsum;		//电机速度计数变量
extern bit open_close_flang;
extern bit time_refurbish_flag; //时间刷新显示标志
//extern bit T_S0_flag;
//
extern void Time_init(void);

#endif 