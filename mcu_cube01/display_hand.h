#ifndef __DISPLAY_HAND__
#define	__DISPLAY_HAND__
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#include "STC15Fxxxx.h"
#include "74HC595.H"
#include "display.H"
#include "Time.h"
#include "povdat.h" 
//#include "IR_KEY.H"
//#include "UART.h"

//extern xdata uint hz_dat[];
extern uchar t_mode;
extern void display_hand(void);

#endif