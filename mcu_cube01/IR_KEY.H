#ifndef __IR_KEY_H__
#define __IR_KEY_H__

//#include "STC12C5AXX.H"
#include "IR.H"
#include "display_hand.h"


extern uchar DIS_MODE;  //显示模式ID
extern uchar Addr_num;//EEPROM地址指针变量
//extern bit t_mode_falg;  //指针表盘选择标志为1时为数字指针表盘，为0时只为指针式表盘
extern void key_cont(void);

#endif