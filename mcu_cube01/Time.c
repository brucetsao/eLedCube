#include "Time.h"

bit pic_ch_flag;   //图片切换标志
bit Time0_flag=0;  //定时器0中断标志
bit pic_red_ok=0;  //图片读缓冲标志
bit pic_rd_flag;   //图片完成标志
bit open_close_flang=0;	
bit time_refurbish_flag; //时间刷新显示标志
//uint D=400;
uchar speed;	   //电机速度变量
uchar speedsum;	   //电机速度计数变量

uint Pt;		   //自适应时间重装值
uint T0_S=179;	   //定时器0中断（显示分数计数值）
uint line_now;	   //表盘修正现在列、修正值
uint line_vol;	 
uchar irtime;	   //红外解码定时器1中断计数变量
uchar num;
uchar day,month,year,week,second,minute,hour; //系统时间变量

void Time_init(void)	//定时器初始化
{
	 AUXR=0XD5;	//设置T0 1T模式, 模式串行模式为12T, 允许使用内部RAM,允许独立波特率发生器，
			    // b7       b6       b5       b4      b3     b2     b1     b0
			    //t0x12   t1x12    uart_m0x6  TR2   T2/CT   T2X12 EXTRAM  SIST2       
			    //	1        1		  0		   1	   0	  1	   	 0      1
				//SIST2   定时器2是否用作串口1的波特率发生器  
				//EXTRAM  内部/外部RAM存取控制	 0允许内部RAM存取，
				//T2x12    定时器2时钟模式
				//T2/CT    定时器2用作定时还是计数器
				//TR2      定时器2允许运行
				
				
	 TMOD=0X01; //定时器0工作方式1,/定时器1工作方式2,8位自动重装；
			    //   b7   b6   b5  b4  b3   b2  b1   b0/
			    //  GATE  C/T  M1   M0 GATE	C/T M1   M0
			    //    0	  0	   1	0	0	 0	 0	 1

	 /*
	 IT0=1;			 //外中断0触发方式,为1时为下降沿有效,为0时低电平有效
	 IT1=1;           //外中断1触发方式, 为1时为下降沿有效,为0时低电平有效
 	 EX0=1;			 //外中断0使能标志
	 EX1=1;			 //外中断1使能标志
	 EA=1;	    //开总中断；
	 */
	 TL0 = 0x71;		//设置定时初值	 153
	 TH0 = 0xDD;		//设置定时初值
	 //TL1 = 0xF8;		//设置定时初值	 255
	 //TH1 = 0xE9;		//设置定时初值
	 TL1 = 0x33;		//设置定时初值	 125
	 TH1 = 0xF5;		//设置定时初值
	 TR1 = 1;		     //开启定时器1
 	 TR0 = 1;		 //打开定时器0
	 //TR1 =0;		 //关定时器1
	 //TR0 =0;		 //关定时器0
	 ET0 = 1;		 //定时器0中断使能,为1时开,为0时关
	 ET1 = 1;		 //定时器1中断使能,为1时开,为0时关
	 //ET0 = 0;		 //定时器0中断使能,为1时开,为0时关
	 //ET1 = 0;		 //定时器1中断使能,为1时开,为0时关		 
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
    TR0=0;
	Time0_flag=1;	           //定时中断标志位置1;
	TH0=-Pt/256;TL0=-Pt%256;   //设置定时器T0的初设值
	T0_S++; 
	//if(T0_S>179)                   //计数
	//Int0_flag=0;
	line_now=180-line_vol+T0_S;	 //反时针旋转
	if(line_now>180)
	line_now=T0_S-line_vol;
	TR0=1;
}

/****************************************************************
函数名：定时器1中断服务函数  中断号:3 ;
调  用：无
参  数：无
返回值：无
功  能：提供显示位置所需的时间;
备  注：定时器1,工作方式0,16位自动重装载 1T模式,
/****************************************************************/

void timer1(void)   interrupt 3   using 2
{
	uint s,j,k,n,c;
	s++; irtime++;	j++; n++;c++;		//	second,minute,hour
	if(j==2)  {j=0;  pic_ch_flag=1;}		  //动画刷屏时间
	if(n==600){n=0;  pic_red_ok=1; }

	//if(j == 50   )  {j=0;  pic_ch_flag=1;}	   //图片刷新间隔时间
	//if(n == 44000 )  {n=0;  pic_red_ok=1; }	   
	if(c == 600 )  
	{
		c=0;  
		time_refurbish_flag=1;
		line_vol++; 
		if(line_vol>179) 
		line_vol=0;
	}
	if(s==8000)
	{
		s=0;
		speedsum=speed;
		speed=0;
		second++;  
		k++;
		/*
		if(speed>10)
		{
			speed=0;
			open_close_flang=1;
			TR0=1;
		}
		else {TR0=0;}
		*/
		if(k==3) 
		{
			k=0;
		//	pic_ch_flag=1;
			//if(uart_flang)
			{
				//UART_Send_Byte(pov_dat[num]) ;
				//P0=pov_dat[1];
				num++;// i++;
				if(num>719)
				{
				num=0;
				}
				
			}
			LED0=!LED0;
		}
		if(second==60)
		{
			second=0;
			minute++;
			if(minute==60)
			{
				minute=0;
				hour++;
				if(hour>11)
				{
					hour=0;
				}
			}
		}
	}
}
	