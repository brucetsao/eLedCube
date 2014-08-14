#include "IR_KEY.H"
#include 	"ds1302.h"

//按键标志位定义
bit menu_flag;	   //MENU
bit test_flag;	   //TEST
bit esc_flag;	   //ESC 返回
bit left_flag;	   //←左
bit right_falg;	   //←右
bit hour_flag;
bit minute_flag;
bit second_falg;
bit year_flag;
bit month_flag;
bit day_falg;
bit rotate_falg;
bit Pchang_falg;
bit pic_o_falg;
bit t_mode_falg;  //指针表盘选择标志为1时为数字指针表盘，为0时只为指针式表盘
//全局变量定义
uchar DIS_MODE;  //显示模式ID
uchar Addr_num;
//uchar line_vol=1;  //表盘处理变量

//遥控器键码表//
/*用户码00FF */
/*电源(0X45) 空(0X46)  MENU(0X47)*/
/*TEST(0X44) + (0X40)  返回(0X43)*/
/* ←  (0X07) ▲ (0X15)   →  (0X09)*/
/* 0  (0X16) - (0X19)   C  (0X0D)*/
/* 1  (0X0C) 2 (0X18)   3  (0X5E)*/
/* 4  (0X08) 5 (0X1C)   6  (0X5A)*/
/* 7  (0X42) 8 (0X52)   9  (0X4A)*/

//红外遥控按键处理函数
void key_cont(void)
{
	if(irreceok)
    {  
	    irreceok=0;	
		IR_pros();
		if(irprosok)
		{
			irprosok=0;
			//if(ircode[0]==0x00)
			//{
				switch (ircode[2])
				{
					case 0x47:
						menu_flag=1;	  //菜单键标志
						break;
					case 0x44:		
						test_flag=1;	  //测试键标志
						break;
					case 0x43:	   
						esc_flag=1;		  //返回键标志
						break;
					case 0x07:	
						left_flag=1;	  //左移键标志	 ← 
						break;
					case 0x09:	   
						right_falg=1;	  //右移键标志	 →
						break;
					case 0x0c:	   
						hour_flag=1;	  //调时键标志	 1
						break;
					case 0x18:	
						minute_flag=1;	  //调分键标志	 2
						break;
					case 0x5e:	   
						second_falg=1;	  //调秒键标志	 3
						break;
					case 0x08:	   
						year_flag=1;	  //调年键标志	 4
						break;
					case 0x1c:	
						month_flag=1;	  //调月键标志	 5
						break;
					case 0x5A:	   
						day_falg=1;	      //调日键标志	 6
						break;
					case 0X42:	   
						Pchang_falg=1;	  //动画切换键标志	 7
						break;
					case 0x4A:	   
						t_mode_falg=1;	  //指针表盘切换标志    9
						break;
					case 0x0D:	   		  //旋转起停标志（TEST）C
						rotate_falg=1;	      
						break;
					case 0x16:	   		  //旋转起停标志（TEST）0
						pic_o_falg=1;	      
						break;
					default:
						break;
				}
			//}
		}
		if(menu_flag)	   //模式切换
		{
			menu_flag=0;
            //PCA_LED = !PCA_LED;
            //LED33=~LED33;
			//LED0=~LED0;
			DIS_MODE++;
			//if(DIS_MODE==0)
			//pic_rotate=1;
			//else 
			//pic_rotate=0;
			//if(pic_rotate==0)
			//line_vol=0;
			if(DIS_MODE>2)
         	DIS_MODE=0;	
		}
		if(left_flag)		//向左转动盘面
		{
			left_flag=0; 
			/*if(line_vol==0)	//先判断后减减
			{
			    line_vol=179;
			}
			else
			line_vol--;
			*/
		}
		if(right_falg)	    //向右转动盘面
		{
			right_falg=0 ;
		/*	line_vol++;
		    if(line_vol>179)
		    line_vol=0;
		*/
		}
		if(hour_flag)		//调时
		{
			hour_flag=0; 
			//if(DIS_MODE==0)
			//Addr_num=0;
			hour++;
			write_clock(0x84,hour);   //小时
			if(hour>11)	
		    hour=0;
		}
		if(minute_flag)		//调分
		{
			minute_flag=0;
			//if(DIS_MODE==0)
			//Addr_num=1;
			minute++; 
			if(minute>59)	
			{
				minute=0;
				hour++;
				if(hour>11)
				hour=0;
			}
		}
		if(second_falg)		//调秒
		{
			second_falg=0;
			//if(DIS_MODE==0)
			//Addr_num=2; 
			second++;
			if(second>59)	
		    second=0;
		}
		if(year_flag)		//调年
		{
			year_flag=0; 
			//if(DIS_MODE==0)
			//Addr_num=3;
			year++;
			if(year>25)	   
		    year=13;
		}
		if(month_flag)		//调月
		{
			month_flag=0; 
			month++;
			if(month>11)	//
		    month=0;
		}
		if(day_falg)		//调日
		{
			day_falg=0; 
			day++;
			if(day>31)	
		    day=0;
		}
		if(t_mode_falg)		//指针表盘切换
		{
			t_mode_falg=0; 
			t_mode=~t_mode;
			
		}
		if(rotate_falg)		//旋转与停止
		{
		//	pic_rotate=~pic_rotate;
		}
		if(pic_o_falg)		//旋转与停止
		{
		//	pic_ch=~pic_ch;
		}
		if(Pchang_falg)		//调月
		{
			Pchang_falg=0; 
			Addr_num++;
			if(Addr_num>3)	//
		    Addr_num=0;
		}
	}			
}