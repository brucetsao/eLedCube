/*********************************************
	项 目:	多功能旋转POV LED 
	模 块：	主函数
	功 能：	图片显示测试
	版 本：	V1.0
	设 计：	ZhiQu Studio
	时 间：	2012年10月28日
	修 改:	2012.10.28.19:00 创建项目
	说 明：	主控MCU STC12C5A16S2  
********************************************/
#include "STC_15FXX.h"
#include <intrins.h>
#include <string.h>
#include	"MyType.h"
#include	"POV LED_PIC.H"

/*********外部接口定义*********	*/
//STC11 接口定义
/*sbit IR_HW=P3^2;	//过零信号检测端口//外中断0;
sbit IR_YK=P3^3;	//红外遥控接收端口
sbit LED33 =P3^6;	//内圈LED输出端口
sbit LED0=P3^7;	    //外圈LED输出端口
sbit OE_595= P0^1;	//595使能端口 13脚
sbit DAT= P0^0 ;    //595串行数据输入 14脚
sbit CLK= P0^3 ;    //移位寄存器时钟输入,对应595的11脚SCK
sbit RCK= P0^2 ;    //存储寄存器时钟输入,对应595的12脚RCK
sbit CLR= P0^1 ;    //寄存器数据清零
sbit PWM= P1^3 ;	//亮度调节
*/
/*
//STC12接口定义
sbit OE_595 = P4^3;	 //595使能端口 13脚
sbit DAT = P2^2 ;    //595串行数据输入 14脚
sbit CLK = P2^0 ;    //移位寄存器时钟输入,对应595的11脚SCK
sbit RCK = P2^1 ;    //存储寄存器时钟输入,对应595的12脚RCK	

sbit LED33 =P2^4;	//内圈LED输出端口
sbit LED0  =P2^3;	//外圈LED输出端口


//sbit SPEEK=P1^4 ;	//蜂鸣器 
*/

sbit SDAA=P2^4;	//数据
sbit OEA =P2^5;  //595使能
sbit STRA=P2^6;	 //锁存
sbit SCKA=P2^7;	//时钟

sbit SDAB=P2^0;	//数据
sbit OEB =P2^1;  //595使能
sbit STRB=P2^2;	 //锁存
sbit SCKB=P2^3;	//时钟

sbit SDAC=P3^4;	//数据
sbit OEC =P3^0;  //595使能
sbit STRC=P3^6;	 //锁存
sbit SCKC=P3^7;	//时钟

sbit OED =P4^4;  //595使能


sbit LED0=P4^5;
sbit LED1=P3^1;


bit Time0_flag=0;	//定时器T0中断标志位
//bit Time1_flag=0;	//定时器T1中断标志位
bit  T_S0_flag=0;	 

/*定义全局变量*/
uchar dat1,dat2,dat3; dat4;
uint Pt,S0,T,D,T0_S=179;		//计数用的变量

//函数声明
void delay();
void display_pic();		 //图片显示函数

/****************************************************************
函数名：LED显示用延时函数
调  用：delay();
参  数：无
返回值：无
结  果：占用CPU方式延时500微秒时间
备  注：晶振24.0m 1T模式，每个机器周期为0.06254US；
/****************************************************************/
void delay(void)   //误差 -0.46875us
{
    uchar a,b;
    for(b=10;b>0;b--)
        for(a=2;a>0;a--);
}
/****************发送数据A*************************/
void Send_data_A(uchar  dat2)	  
{
	uchar i; 
	for(i=0;i<8;i++)         //一个字节8位 发送给595
   {
       SCKA=0;               //上升沿移位595			   
	   SDAA=(0X80&dat2);//通过IO口送一个位给 595
       dat2<<=1;         //字节移位 准备送下一位			   
       SCKA=1;
   }
    STRA=1;
	STRA=0;
   
}
/****************发送数据B*************************/
void Send_data_B(uchar dat1)	  
{
	uchar i; 
	for(i=0;i<8;i++)		 //一个字节8位 发送给595
   {
       SCKB=0;               //上升沿移位595			   
	   SDAB=(0X80&dat1);//通过IO口送一个位给 595
       dat1<<=1;         //字节移位 准备送下一位			   
       SCKB=1;
   }
    STRB=1;
	STRB=0;
   
}
/****************发送数据C**********************/
///
void Send_data_C(uchar dat5,uchar dat6)	 
{
   uchar i; 
	for(i=0;i<8;i++)//一个字节8位 发送给595
   {
       SCKC=0; //上升沿移位595			   
	   SDAC=(bit)(dat5&0x01);//通过IO口送一个位给 595
       dat5=dat5>>1;  //字节移位 准备送下一位			   
       SCKC=1;
   }
   for(i=0;i<8;i++)//一个字节8位 发送给595
   {
       SCKC=0; //上升沿移位595			   
	   SDAC=(bit)(dat6&0x01);//通过IO口送一个位给 595
       dat6=dat6>>1;  //字节移位 准备送下一位			   
       SCKC=1;
   }
    STRC=1;
	STRC=0;
}
///
/*****************打开595显示***************/
void dis_open( )
{
	OEA=OEB=OED=0;
}
/******************关闭595显示**************/
void dis_close( )
{
	OEA=OEB=OED=1;
}

//图片显示函数
void display_pic()
{
	dis_close(); 
    P1=P0=0xff;
	delay();
	if(T0_S<=179)
	{
		if(Time0_flag)
		{
		 	Time0_flag=0;
			dat1=pic0[T0_S][0];		//改变图片的数组名，可以显示不同的图片，系统内置了6张图片，请查看POVLED_PID.H
			dat2=pic0[T0_S][1];
			dat3=pic0[T0_S][2];
			dat4=pic0[T0_S][3];
			LED1=0;LED0=0;	
			//display(dat1,dat2,dat3,dat4);
			
			Send_data_A(dat2);
			Send_data_B(dat1);
			Send_data_C(0x00,0x00);
			dis_open(); 
		    P0=dat3;
			P1=dat4;
			delay();
			LED0=1;	LED1=1;
			dis_close();
			P1=P0=0xff;
			//display_CLR();
		}		
	}
}
//系统初始化
void init()
{
	 //AUXR1=0X80； //释放该行指令，则串行口从P3口切换到P1口；
	 //AUXR=0X80;	//设置T0定时器为1T模式；
	 AUXR=0XD1;	//设置T0 1T模式, 模式串行模式为12T, 允许使用内部RAM,允许独立波特率发生器，
			    //b7        b6       b5       b4     b3     b2    b1     b0
			    //t0x12   t1x12    uart_m0x6  BRTR    -   BRTX12 XRAM  SIBRS       
			    //	1      1		  0		  1	    0		 0	   0	  1
				//BRTR=1 起动独立波特发生器，BRTX12=1独立波特发生器1T模式，SIBRS=1启用独立波特发生器；
	 TMOD=0X21; //定时器0工作方式1,/定时器1工作方式2,8位自动重装；
			    //   b7   b6   b5  b4  b3   b2  b1   b0/
			    //  GATE  C/T  M1   M0 GATE	C/T M1   M0
			    //    0	  0	   1	0	0	 0	 0	 1
	 IT0=1;			 //外中断0触发方式,为1时为下降沿有效,为0时低电平有效
	 //IT1=1;           //外中断1触发方式, 为1时为下降沿有效,为0时低电平有效
 	 EX0=1;			 //外中断0使能标志
	 EA=1;	    //开总中断；
	 //PWM=0;
}
/****************************************************************
函数名：定时器初始化函数
调  用：无
参  数：无
返回值：无
功  能：初始化定时器
备  注：
/****************************************************************/
void initTimer(void)
{
    //TMOD = 0x21;   //定时器0,工作方式1（16位计数模式）；定时器1,工作方式2（8位自动重装模式）
    //TH0 = 0x0FC;	// 定时器0,工作方式1,12T模式,定时400US;
    //TL0 = 0x0E0;
	TH0 = 0x0DA;	// 定时器0,工作方式1,1T模式,定时400US;
    TL0 = 0x80;
	TH1 = 0x00;		// 定时器1,工作方式2，8位自动重装,1T模式,定时10US;
    TL1 = 0x10;
	//TR1 =1;		     //开启定时器1
	TR0 = 1;		 //打开定时器0
	//TR1 =0;		     //关定时器1
	//TR0 =0;		 //关定时器0

	ET0 = 1;		 //定时器0中断使能,为1时开,为0时关
	//ET1 =1;			 //定时器1中断使能,为1时开,为0时关
}
/****************************************************************
函数名：定时器0中断服务函数  中断号:1 ;
调  用：无
参  数：无
返回值：无
功  能：提供显示位置所需的时间;
备  注：定时器0,工作方式1,16位定时器 1T模式,
/****************************************************************/
void timer0(void)   interrupt 1   using 1
{
    Time0_flag=1;	           //定时中断标志位置1;
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	T0_S++;                    //计数
}
/****************************************************************
函数名：外部中断0服务函数  中断号:0 ;
调  用：无
参  数：无
返回值：无
结  果：无
备  注：自适应速度调节;
/****************************************************************/
void intersvr0(void) interrupt 0   using 2
{  
	EX0=0;				//关外中断
	D+=(T0_S-180)*2;   //修正值
   	Pt=600+D;       //得到定时器T0的初设值
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	T0_S=0;            //计数器清零，将重新计数	
	EX0=1;				//开外中断
}
//系统主函数
void main (void)
{
	LED1=0;
	LED0=0;
	init();    	  //系统初始化
	initTimer();	  //两个定时器初始化
	//dis_open();
	while(1)
	{ 	
		display_pic();
	
	}
}


