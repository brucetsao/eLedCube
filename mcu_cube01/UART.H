#ifndef __UART_H__
#define	__UART_H__

#include "STC15Fxxxx.h"
//#include "MyType.h"
#include "intrins.h"
#include "eeprom.h"

extern bit uart_flang;

//extern uint  num;

extern void UART_init (void);
//extern void UART_R(void);
extern void UART_Send_Enter();
extern void UART_Send_Byte(uchar ucData);
extern void UART_Send_Str(char *pStr);

#endif 