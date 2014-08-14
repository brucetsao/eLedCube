
/*****************************************************************************
 ͷ�ļ�
 *****************************************************************************/
//#include <STC11F60XE.h>
#include 	"ds1302.h"
                    //��    ��    ʱ    ��    ��  ����    ��
//uchar code init[] = {0x00, 0x00, 0x20, 0x01, 0x01, 0x05, 0x10};
//uchar data now[7];
uchar xdata disp_time[19]; 
/******************************************************************************
��������:	1302����
��ڲ���:   
���ڲ���:	
******************************************************************************/

//DS1302д�����ݣ��ײ�Э�飩
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
//DS1302д���ֽڣ��ײ�Э�飩
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
//DS1302��ȡ���ݣ��ײ�Э�飩
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
//************����1302�ĳ�ʼʱ��*****************/
void Init_1302(void) //
{  /*if(read_clock(0xc1) != 0x54)
	{
	write_clock(0x8e,0x00);//����д����
	write_clock(0x8c,0x10);//��
	write_clock(0x8a,0x03);//����
	write_clock(0x88,0x11);//��
	write_clock(0x86,0x24);//��
	write_clock(0x84,0x07);//Сʱ
	write_clock(0x82,0x57);//����
	write_clock(0x80,0x00);//��
	write_clock(0x90,0xb5);//���
	write_clock(0xc0,0x54);//д���ʼ����־RAM����00��RAMλ�ã�
	write_clock(0x8e,0x80);//��ֹд����	
	}
	write_clock(0x8e,0x00);//����д����
	write_clock(0x8e,0x80);//��ֹд����	 */
	
	 write_clock(0x8e,0x00);   //����д����
	 write_clock(0x84,0xa0);   //����д����
	 write_clock(0x8c,0x13);   //��
	 write_clock(0x8a,0x07);   //����
	 write_clock(0x88,0x11);   //��
	 write_clock(0x86,0x28);   //��
	 write_clock(0x84,0x10);   //Сʱ
	 write_clock(0x82,0x23);   //����
	 write_clock(0x80,0x30);   //��
	//write_clock(0x80,0x80);   //��
	 write_clock(0x90,0xa5);   //��� 
	 write_clock(0x8e,0x80);   //��ֹд����	
}
/****************************************************************
����������һ�ζ�ȡʱ�亯��
��  �ã�time_first_read();
��  ������
����ֵ����
��  ����
��  ע����
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

//===============��ʾˢ���ӳ���==================
void time_refurbish() 
{
/*
	ss=read_clock(0x81);   //����
	ss=ss%16+ss/16*10;
	if(ss==0)//��=0ʱ����
	{
		mm=read_clock(0x83);
		mm=mm%16+mm/16*10;
	}
	if(mm==0)//��=0ʱ��Сʱ��
	{
		hh=read_clock(0x85);
	    hh=hh%16+hh/16*10;
		if(hh>11)
		{
			hh=hh-12;
		}
	}
		
 	day = read_clock(0x87);   //��
	day=day%16+dd/16*10;
	month = read_clock(0x89);   //��
	month=month%16+month/16*10;
	week = read_clock(0x8b);   //����
	week=week%16+week/16*10;
	year = read_clock(0x8d);   //��
	year=year%16+year/16*10;
	*/
	if(time_refurbish_flag)
	{
		time_refurbish_flag=0;

		second=read_clock(0x81);   //����
		second=second%16+second/16*10;
		if(second==0)//��=0ʱ����
		{
			minute=read_clock(0x83);
			minute=minute%16+minute/16*10;
		}
		if(minute==0)//��=0ʱ��Сʱ��
		{
			hour=read_clock(0x85);
		    hour=hour%16+hour/16*10;
			if(hour>11)
			{
				hour=hour-12;
			}
		}	
	 	day = read_clock(0x87);     //��
		day=day%16+day/16*10;
		month = read_clock(0x89);   //��
		month=month%16+month/16*10;
		week = read_clock(0x8b);    //����
		week=week%16+week/16*10;
		year = read_clock(0x8d);    //��
		year=year%16+year/16*10;
		//disp_time[1] = speedsum/10;   //����ٶ�
	   	//disp_time[2] = speedsum%10;   //����ٶ�
		disp_time[1] = hour/10;   //Сʱ
	   	disp_time[2] =hour%10;   //Сʱ
		disp_time[3] = 10;   //Сʱ
		disp_time[4] =minute/10;   //��ȡ��������
	   	disp_time[5] =minute%10;   //��ȡ�������� 
		disp_time[6] =10;  
		disp_time[7] =second/10;   //��ȡ������
	   	disp_time[8] =second%10;   //��ȡ������
		disp_time[16] = year/10;   //��
	   	disp_time[15] = year%10;   //���λ
	   	disp_time[14]=10;
	   	disp_time[13] =month/10;   //��ʮλ
	   	disp_time[12] =month%10;   //�¸�λ
	   	disp_time[11]=10;
	   	disp_time[10] =day/10;   //��ʮλ
	   	disp_time[9] =day%10;   //�ո�λ
	}
}