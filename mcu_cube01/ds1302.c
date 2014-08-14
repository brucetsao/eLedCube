
/*****************************************************************************
 头文件
 *****************************************************************************/
//#include <STC11F60XE.h>
#include 	"ds1302.h"
                    //秒    分    时    日    月  星期    年
//uchar code init[] = {0x00, 0x00, 0x20, 0x01, 0x01, 0x05, 0x10};
//uchar data now[7];
uchar xdata disp_time[19]; 
/******************************************************************************
函数功能:	1302驱动
入口参数:   
出口参数:	
******************************************************************************/

//DS1302写入数据（底层协议）
void write_clock(uchar ord, uchar dd)
    {
	clock_clk=0;
	clock_Rst=0;
	clock_Rst=1;
	clock_out(ord);
	clock_out(dd);
	clock_Rst=0;
	clock_clk=1;
	}
//DS1302写入字节（底层协议）
uchar clock_in(void)
	{
	clock_dat=1;	          ACC0=clock_dat;
	clock_clk=1; clock_clk=0; ACC1=clock_dat;
	clock_clk=1; clock_clk=0; ACC2=clock_dat;
	clock_clk=1; clock_clk=0; ACC3=clock_dat;
	clock_clk=1; clock_clk=0; ACC4=clock_dat;
	clock_clk=1; clock_clk=0; ACC5=clock_dat;
	clock_clk=1; clock_clk=0; ACC6=clock_dat;
	clock_clk=1; clock_clk=0; ACC7=clock_dat;
	return(ACC);
	}
//DS1302读取数据（底层协议）
uchar read_clock(uchar ord)
	{
	uchar dd=0;
	clock_clk=0;
	clock_Rst=0;
	clock_Rst=1;
	clock_out(ord);
	dd=clock_in();
	clock_Rst=0;
	clock_clk=1;
	return(dd);
}
void clock_out(uchar dat)
{
	ACC=dat;
	clock_dat=ACC0; clock_clk=1; clock_clk=0;
	clock_dat=ACC1; clock_clk=1; clock_clk=0;
	clock_dat=ACC2; clock_clk=1; clock_clk=0;
	clock_dat=ACC3; clock_clk=1; clock_clk=0;
	clock_dat=ACC4; clock_clk=1; clock_clk=0;
	clock_dat=ACC5; clock_clk=1; clock_clk=0;
	clock_dat=ACC6; clock_clk=1; clock_clk=0;
	clock_dat=ACC7; clock_clk=1; clock_clk=0;
}
//************设置1302的初始时间*****************/
void Init_1302(void) //
{  /*if(read_clock(0xc1) != 0x54)
	{
	write_clock(0x8e,0x00);//允许写操作
	write_clock(0x8c,0x10);//年
	write_clock(0x8a,0x03);//星期
	write_clock(0x88,0x11);//月
	write_clock(0x86,0x24);//日
	write_clock(0x84,0x07);//小时
	write_clock(0x82,0x57);//分钟
	write_clock(0x80,0x00);//秒
	write_clock(0x90,0xb5);//充电
	write_clock(0xc0,0x54);//写入初始化标志RAM（第00个RAM位置）
	write_clock(0x8e,0x80);//禁止写操作	
	}
	write_clock(0x8e,0x00);//允许写操作
	write_clock(0x8e,0x80);//禁止写操作	 */
	
	 write_clock(0x8e,0x00);   //允许写操作
	 write_clock(0x84,0xa0);   //允许写操作
	 write_clock(0x8c,0x13);   //年
	 write_clock(0x8a,0x07);   //星期
	 write_clock(0x88,0x11);   //月
	 write_clock(0x86,0x28);   //日
	 write_clock(0x84,0x10);   //小时
	 write_clock(0x82,0x23);   //分钟
	 write_clock(0x80,0x30);   //秒
	//write_clock(0x80,0x80);   //秒
	 write_clock(0x90,0xa5);   //充电 
	 write_clock(0x8e,0x80);   //禁止写操作	
}
/****************************************************************
函数名：第一次读取时间函数
调  用：time_first_read();
参  数：无
返回值：无
结  果：
备  注：；
/****************************************************************/
void time_first_read()
{
	minute=read_clock(0x83);
	minute=minute%16+minute/16*10;
	hour=read_clock(0x85);
	hour=hour%16+hour/16*10;
	if(hour>11)
	{
		hour=hour-12;
	}		
}

//===============显示刷新子程序==================
void time_refurbish() 
{
/*
	ss=read_clock(0x81);   //读秒
	ss=ss%16+ss/16*10;
	if(ss==0)//秒=0时读分
	{
		mm=read_clock(0x83);
		mm=mm%16+mm/16*10;
	}
	if(mm==0)//分=0时读小时；
	{
		hh=read_clock(0x85);
	    hh=hh%16+hh/16*10;
		if(hh>11)
		{
			hh=hh-12;
		}
	}
		
 	day = read_clock(0x87);   //日
	day=day%16+dd/16*10;
	month = read_clock(0x89);   //月
	month=month%16+month/16*10;
	week = read_clock(0x8b);   //星期
	week=week%16+week/16*10;
	year = read_clock(0x8d);   //年
	year=year%16+year/16*10;
	*/
	if(time_refurbish_flag)
	{
		time_refurbish_flag=0;

		second=read_clock(0x81);   //读秒
		second=second%16+second/16*10;
		if(second==0)//秒=0时读分
		{
			minute=read_clock(0x83);
			minute=minute%16+minute/16*10;
		}
		if(minute==0)//分=0时读小时；
		{
			hour=read_clock(0x85);
		    hour=hour%16+hour/16*10;
			if(hour>11)
			{
				hour=hour-12;
			}
		}	
	 	day = read_clock(0x87);     //日
		day=day%16+day/16*10;
		month = read_clock(0x89);   //月
		month=month%16+month/16*10;
		week = read_clock(0x8b);    //星期
		week=week%16+week/16*10;
		year = read_clock(0x8d);    //年
		year=year%16+year/16*10;
		//disp_time[1] = speedsum/10;   //电机速度
	   	//disp_time[2] = speedsum%10;   //电机速度
		disp_time[1] = hour/10;   //小时
	   	disp_time[2] =hour%10;   //小时
		disp_time[3] = 10;   //小时
		disp_time[4] =minute/10;   //读取分钟数据
	   	disp_time[5] =minute%10;   //读取分钟数据 
		disp_time[6] =10;  
		disp_time[7] =second/10;   //读取秒数据
	   	disp_time[8] =second%10;   //读取秒数据
		disp_time[16] = year/10;   //年
	   	disp_time[15] = year%10;   //年个位
	   	disp_time[14]=10;
	   	disp_time[13] =month/10;   //月十位
	   	disp_time[12] =month%10;   //月个位
	   	disp_time[11]=10;
	   	disp_time[10] =day/10;   //日十位
	   	disp_time[9] =day%10;   //日个位
	}
}