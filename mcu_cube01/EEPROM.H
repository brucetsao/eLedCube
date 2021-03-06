#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "STC15Fxxxx.h"
#include "intrins.h"
//-----------------------------------------------


#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//���Ե�ַ
#define IAP_ADDRESS 0x0000

//extern void Delay1();
extern void IapIdle();
extern uchar IapReadByte(uint addr);
extern void IapProgramByte(uint addr, uchar dat);
extern void IapEraseSector(uint addr);

#endif
