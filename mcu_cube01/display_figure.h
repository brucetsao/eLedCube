#ifndef __DISPLAY_FIGURE_H__
#define __DISPLAY_FIGURE_H__
#include "STC15Fxxxx.h"
#include "74HC595.H"
#include "display.H"
#include "Time.h"
#include "IR.h"
#include "povdat.h" 

extern xdata uchar disp_time[]; 
static void time_refurbish();
extern void display_figure();

#endif