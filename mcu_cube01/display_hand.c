#include "display_hand.h"
uchar t_mode;

//xdata uint hz_dat[360];
/**********************************************************************************************
函数名：指针模式函数
调  用：无
参  数：无
返回值：无
结  果：
备  注：
/*********************************************************************************************/
void display_hand(void)
{
	uchar Temp,datmp1,datmp2,datmp3,datmp4;
	//P1=P0=0xff;
	//dis_close(); 
	datmp1=0xff;
	datmp2=0xff;
	datmp3=0xff;
	datmp4=0xff; 
	if(Time0_flag )
	{
		Time0_flag=0;
		Temp=(T0_S-1);
		if(Temp<=180)
		{	
			//datmp1=0;datmp2=0;datmp3=0;datmp4=0;
			if(t_mode)	 //为1时显示数字指针表盘模式 ，为0时显示指针式表盘模式
			{
				//标12点
				if(Temp==1)  {datmp1=0xcd;}
				if(Temp==2)  {datmp1=0xb6;}
				if(Temp==3)  {datmp1=0xb6;}
				if(Temp==4)  {datmp1=0xb6;}
				if(Temp==5)  {datmp1=0xb9;}
				if(Temp==179){datmp1=0x80;}
	
				//标3点
				if(Temp==42){datmp1=0xf1;}
				if(Temp==43){datmp1=0xee;}
				if(Temp==44){datmp1=0xfe;}
				if(Temp==45){datmp1=0xf1;}
				if(Temp==46){datmp1=0xfe;}
				if(Temp==47){datmp1=0xee;}
				if(Temp==48){datmp1=0xf1;}
				//标6点
				if(Temp==88){datmp1=0xd9;}
				if(Temp==89){datmp1=0xb6;}
				if(Temp==90){datmp1=0xb6;}
				if(Temp==91){datmp1=0xb6;}
				if(Temp==92){datmp1=0xc1;}
				//标9点
				if(Temp==132){datmp1=0xf1;}
				if(Temp==133){datmp1=0xee;}
				if(Temp==134){datmp1=0xef;}
				if(Temp==135){datmp1=0xe1;}
				if(Temp==136){datmp1=0xee;}
				if(Temp==137){datmp1=0xee;}
				if(Temp==138){datmp1=0xf1;}
				//标1、2、4、5、7、8、10、11整点
				if((Temp==15)||(Temp==30)||(Temp==60)||(Temp==75)||(Temp==105)||(Temp==120)||(Temp==150)||(Temp==165)){datmp1=0xfc;}
			}
			else  //否则
			{
				if(Temp%3==0){datmp1=0xfe;datmp2=0xff;datmp3=0xff;datmp4=0xff;	}   //画分刻度
				if((Temp%15==0)||(Temp==179)||(Temp==1)){LED1=0;datmp1= datmp1&0xfc;}
			}
			switch(Temp%3)
			{
				case 0:
				{
					//datmp1=0xfe;datmp2=0xff;datmp3=0xff;datmp4=0xff;	   //画分刻度
					//if(Temp%15==0){LED1=0;datmp1= datmp1&0xfc;}
		  			if((Temp==second*3)||(Temp==179)){datmp1= datmp1&0x07;datmp2= datmp2&0x00; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
					if(Temp==minute*3){datmp1= datmp1&0xff;datmp2= datmp2&0x00; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
					if(Temp==(15*hour+minute/12*3))	{datmp1= datmp1&0xff;datmp2= datmp2&0x0f; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
								    
					break;		  
				}	
				default:
		
				{
				if(Temp==1||Temp==179)
				{datmp1= datmp1&0xfc;datmp2=datmp2&0xff;datmp3=0xff;datmp4=0xff;}
				if(minute>0||second>=0)
				{
					if(Temp==(3*minute-1) || Temp==(3*minute+1))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x01; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
					if(Temp==(15*hour+minute/12*3-1)|| Temp==(15*hour+minute/12*3+1))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x1f; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
					if(Temp==(15*hour+minute/12*3-2)|| Temp==(15*hour+minute/12*3+2))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x3f; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
				}
				if(minute==0)
				{
					if(Temp==(180-3*minute-1) || (Temp==3*minute+1))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x01; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
				}
				if(hour==0)
				{
					if(Temp==(180-15*hour+minute/12*3)-1|| Temp==(15*hour+minute/12*3+1))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x1f; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
					if(Temp==(180-15*hour+minute/12*3)-2|| Temp==(15*hour+minute/12*3+2))
					{datmp1= datmp1&0xff;datmp2= datmp2&0x3f; datmp3= datmp3&0x00;datmp4= datmp4&0x00;}
				} 
				break;
				}  
				
				 
			} 

		dat1=datmp1;dat2=datmp2;dat3=datmp3;dat4=datmp4;  dat5=pov_hz[line_now][0];	 dat6=pov_hz[line_now][1];
		}
		 		 Send_data_A(dat1,dat2);
				 Send_data_B(dat5,dat6);	
				 dis_open(); 
				 P2=dat3;
			     P0=dat4;
			 LED1=0;
			 LED0=0;	 
			 LED2=0;
			 delay();
			 //LED0=1;
			 LED1=1;
			 LED2=1;
			 P0=P2=0xff;
			 dis_close(); 
	} 	
		
}