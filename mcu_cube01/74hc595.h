#ifndef __74HC595_H__
#define	__74HC595_H__
//#include "config.h"
#include "STC15Fxxxx.h"
//#include	"MyType.h"
/*
sbit SDAA=P2^4;	//数据
sbit OEA =P2^5;  //595使能
sbit STRA=P2^6;	 //锁存
sbit SCKA=P2^7;	//时钟

sbit SDAB=P2^0;	//数据
sbit OEB =P2^1;  //595使能
sbit STRB=P2^2;	 //锁存
sbit SCKB=P2^3;	//时钟

sbit SDAC=P3^4;	//数据
sbit OEC =P3^0;  //侧面595使能
sbit STRC=P3^6;	 //锁存
sbit SCKC=P3^7;	//时钟

sbit OED =P4^4;  //侧面595使能

sbit LED0=P4^5;	  //平面外圈LED
sbit LED1=P3^1;	  //侧面外圈LED

*/

sbit SDAA=P1^1;	//数据
sbit OEA =P4^7;  //595使能
sbit STRA=P1^2;	 //锁存
sbit SCKA=P1^3;	//时钟

sbit SDAB=P3^4;	//数据
sbit OEB =P4^4;  //595使能
sbit STRB=P3^6;	 //锁存
sbit SCKB=P3^7;	//时钟

//sbit SDAC=P3^4;	//数据
sbit OEC =P4^0;  //侧面595使能
//sbit STRC=P3^6;	 //锁存
//sbit SCKC=P3^7;	//时钟

//sbit OED =P4^4;  //侧面595使能

sbit LED0=P4^5;	  //平面外圈LED
sbit LED1=P1^4;	  //侧面外圈LED
sbit LED2=P1^5;	  //侧面外圈LED





extern void Send_data_A(uchar dat1,uchar dat2);
extern void Send_data_B(uchar temp1,uchar temp2);
//extern void start(void);
extern void dis_open(void);
extern void dis_close(void);
extern void delay(void);

#endif