#ifndef __74HC595_H__
#define	__74HC595_H__
//#include "config.h"
#include "STC15Fxxxx.h"
//#include	"MyType.h"
/*
sbit SDAA=P2^4;	//����
sbit OEA =P2^5;  //595ʹ��
sbit STRA=P2^6;	 //����
sbit SCKA=P2^7;	//ʱ��

sbit SDAB=P2^0;	//����
sbit OEB =P2^1;  //595ʹ��
sbit STRB=P2^2;	 //����
sbit SCKB=P2^3;	//ʱ��

sbit SDAC=P3^4;	//����
sbit OEC =P3^0;  //����595ʹ��
sbit STRC=P3^6;	 //����
sbit SCKC=P3^7;	//ʱ��

sbit OED =P4^4;  //����595ʹ��

sbit LED0=P4^5;	  //ƽ����ȦLED
sbit LED1=P3^1;	  //������ȦLED

*/

sbit SDAA=P1^1;	//����
sbit OEA =P4^7;  //595ʹ��
sbit STRA=P1^2;	 //����
sbit SCKA=P1^3;	//ʱ��

sbit SDAB=P3^4;	//����
sbit OEB =P4^4;  //595ʹ��
sbit STRB=P3^6;	 //����
sbit SCKB=P3^7;	//ʱ��

//sbit SDAC=P3^4;	//����
sbit OEC =P4^0;  //����595ʹ��
//sbit STRC=P3^6;	 //����
//sbit SCKC=P3^7;	//ʱ��

//sbit OED =P4^4;  //����595ʹ��

sbit LED0=P4^5;	  //ƽ����ȦLED
sbit LED1=P1^4;	  //������ȦLED
sbit LED2=P1^5;	  //������ȦLED





extern void Send_data_A(uchar dat1,uchar dat2);
extern void Send_data_B(uchar temp1,uchar temp2);
//extern void start(void);
extern void dis_open(void);
extern void dis_close(void);
extern void delay(void);

#endif