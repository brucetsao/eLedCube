/*********************************************
	项 目:	多功能旋转POV LED 
	模 块：	主函数
	功 能：	图片显示测试
	版 本：	V3.0
	设 计：	ZhiQu Studio
	时 间：	2013年7月5日
	修 改:	2013.7.5.19:00 创建项目
	说 明：	主控MCU STC115F08S2  
********************************************/

#include <intrins.h>
#include <string.h>
//#include "MyType.h"
#include "STC15Fxxxx.h"
//#include	"POV LED_PIC.H"
#include "74HC595.H"
#include "Time.h"
#include "povdat.h" 
#include "display.H"
#include "UART.h"
#include "IR.h"
#include "Exti.h"
#include "display_hand.h"
#include "display_figure.h"
//#include "eeprom.h"

//uchar speed;
//bit open_close_flang=0;

/*********外部接口定义*********	*/


//bit Time0_flag=0;	//定时器T0中断标志位
//bit Time1_flag=0;	//定时器T1中断标志位
bit  T_S0_flag=0;	 
//uchar xdata leddat[128];
/*定义全局变量*/
//uchar dat1,dat2,dat3; dat4;
//uint D=400;
//uint T0_S=179;
//uint Pt;

//uchar pic_id;
//bit pic_ch_flag;


//函数声明

/****************************************************************
函数名：定时器0中断服务函数  中断号:1 ;
调  用：无
参  数：无
返回值：无
功  能：提供显示位置所需的时间;
备  注：定时器0,工作方式1,16位定时器 1T模式,
/****************************************************************/
/*
void timer0(void)   interrupt 1   using 1
{
    Time0_flag=1;	           //定时中断标志位置1;
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	T0_S++;                    //计数
}
*/
/****************************************************************
函数名：定时器1中断服务函数  中断号:3 ;
调  用：无
参  数：无
返回值：无
功  能：提供显示位置所需的时间;
备  注：定时器1,工作方式0,16位自动重装载 1T模式,
/****************************************************************/
/*
void timer1(void)   interrupt 3   using 1
{
    //TL1 = 0xF8;		//设置定时初值
	//TH1 = 0xE9;		//设置定时初值
	uint s,k;
	s++; irtime++;
	if(s==4000)
	{
		s=0;
		if(speed>10)
		{
			speed=0;
			open_close_flang=1;
			TR0=1;
		}
		else {TR0=0;}
		k++;
		if(k==3) 
		{
			k=0;
			pic_ch_flag=1;
			//if(uart_flang)
			{
				UART_Send_Byte(pov_dat[num]) ;
				//P0=pov_dat[1];
				num++;// i++;
				if(num>719)
				{
				num=0;
				}
				
			}
			LED0=!LED0;
		}
	//	OEC=0;
	}
	
}
*/
/****************************************************************
函数名：外部中断0服务函数  中断号:0 ;
调  用：无
参  数：无
返回值：无
结  果：无
备  注：自适应速度调节;
/****************************************************************/
/*
void intersvr0(void) interrupt 0   using 2
{  
	speed++;
	EX0=0;				//关外中断
	D+=(T0_S-180)*2;   //修正值
   	Pt=600+D;       //得到定时器T0的初设值
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	T0_S=0;            //计数器清零，将重新计数	
	EX0=1;				//开外中断
}
*/

//系统主函数
void main (void)
{
//	uint i;
	LED1=1;
	LED0=0;
	OEC=1;
	Exti_init();
	Time_init();	  //两个定时器初始化
	//TR0=0;
	UART_init();
	UART_Send_Str("知趣电子欢迎你！");
	while(1)
	{ 	
	
		if(irreceok)
    	{  
		    irreceok=0;	
			//P0=0X00;
			IR_pros();
			if(irprosok)
			{
				irprosok=0;
				P0=ircode[2];
			}
		}
		//if(open_close_flang)
	//	{
		///	open_close_flang=0;
			//TR0=1;
		//display_pic();
	//	}
		//else {
		//TR0=0;
		//}
		 display_hand();
		 //display_pic();
		 //display_figure();
		/*if(uart_flang)
		{
			//uart_flang=0;
			P0=0x00;
		//	if(pic_ch_flag)
		//	{
		//		pic_ch_flag=0;
			 TR1=1;   

		//	}
			
		}
		*/
	}
}


