/*********************************************
	项 目:	多功能旋转POV LED 
	模 块：	主函数
	功 能：	图片显示测试
	版 本：	V5.0
	设 计：	ZhiQu Studio
	时 间：	2013年11月25日
	修 改:	2013.11.25.19:00 创建项目
	说 明：	主控MCU STC115F08S2  
********************************************/

#include <intrins.h>
#include <string.h>
#include "STC15Fxxxx.h"
#include "74HC595.H"
#include "Time.h"
#include "povdat.h" 
#include "display.H"
//#include "UART.h"
#include "IR_KEY.H"
#include "IR.h"
#include "Exti.h"
#include "display_hand.h"
#include "display_figure.h"
#include "EEPROM.H"
#include "ds1302.h"

//系统主函数
void main (void)
{
	uint i,j;
	//LED1=0;
	//OEC=1;
	picaddr_end=pic_addr[Addr_num][1]; //初始化图片动画结束地址
	picaddr_start=pic_addr[Addr_num][0];  //动画开始地址
	Exti_init();  //中断初始化
	Time_init();  //两个定时器初始化
	//Init_1302();        //设置1302的初始时间
	time_first_read();	//第一次读取时间
    //UART_init();
	//ES=0;
	//UART_Send_Str("知趣电子欢迎你！");
	//IapReadByte(uint addr);	        //从EEPROM读1字节数据；
	//IapProgramByte(0x0000, 0x00);	    //写1字节数据到EEPROM;
	//IapEraseSector(0x0ff1);		    //擦除扇区
	/*
	IapEraseSector(0x0000);
	IapEraseSector(0x0000+512);
	for(j=0;j<180;j++)
	{
		IapProgramByte(4*j+0, pic0[j][0]);
		IapProgramByte(4*j+1, pic0[j][1]);
		IapProgramByte(4*j+2, pic0[j][2]);
		IapProgramByte(4*j+3, pic0[j][3]);
	}
	*/
	for(j=0;j<180;j++)
	{
		pov_pic[j][0]=IapReadByte(4*picaddr+0);
		pov_pic[j][1]=IapReadByte(4*picaddr+1);
		pov_pic[j][2]=IapReadByte(4*picaddr+2);
		pov_pic[j][3]=IapReadByte(4*picaddr+3);
		picaddr++;
	}
	picaddr=0x0000;	
		for(i=0;i<180;i++)
		{	
			pov_hz[i][0]=hanzi[359-(2*i)];
			pov_hz[i][1]=hanzi[359-(2*i+1)];

		} 
	for(i=0;i<19;i++)
	{
		disp_time[i]=0x00;
	}
	 
	 //IapEraseSector(0x0000);
	 //IapProgramByte(0x0000, 0x55);
	 //UART_Send_Byte(0XFF);
	while(1)
	{ 	
		key_cont();
		
		//Send_data_A(0,0);
		//dis_open( );
		//Send_data_B(dat1);
		//Send_data_B(0,0);
		//P1=P2=0;
		//LED1=0;
		//LED0=0;	
		switch (DIS_MODE)
		{
			case 0:
				//display_hand();
				//picaddr_end=pic_addr[Addr_num][1]; //初始化图片动画结束地址
	           // picaddr_start=pic_addr[Addr_num][0];  //动画开始地址	
			//	display_pic(); 
				//display_figure();	  //可以显示电机转速
				Send_data_A(0,0);
				Send_data_B(0,0);
				P0=P2=0;
		        dis_open( );
				break;
			case 1:
				//TR1=1;
				//T0_S=0;
				display_hand();
				//display_pic();
				break;
			case 2:
				//display_hanzhi();
				//display_hand();
				display_figure();
				break;
			default:
				break;
		}
	  
		 //EEPROM_TEST(); 
		 //display_hand();
		 //display_pic();
		 //display_figure();
	
	}
}


