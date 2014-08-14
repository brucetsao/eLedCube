/*********************************************
	�� Ŀ:	�๦����תPOV LED 
	ģ �飺	������
	�� �ܣ�	ͼƬ��ʾ����
	�� ����	V3.0
	�� �ƣ�	ZhiQu Studio
	ʱ �䣺	2013��7��5��
	�� ��:	2013.7.5.19:00 ������Ŀ
	˵ ����	����MCU STC115F08S2  
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

/*********�ⲿ�ӿڶ���*********	*/


//bit Time0_flag=0;	//��ʱ��T0�жϱ�־λ
//bit Time1_flag=0;	//��ʱ��T1�жϱ�־λ
bit  T_S0_flag=0;	 
//uchar xdata leddat[128];
/*����ȫ�ֱ���*/
//uchar dat1,dat2,dat3; dat4;
//uint D=400;
//uint T0_S=179;
//uint Pt;

//uchar pic_id;
//bit pic_ch_flag;


//��������

/****************************************************************
����������ʱ��0�жϷ�����  �жϺ�:1 ;
��  �ã���
��  ������
����ֵ����
��  �ܣ��ṩ��ʾλ�������ʱ��;
��  ע����ʱ��0,������ʽ1,16λ��ʱ�� 1Tģʽ,
/****************************************************************/
/*
void timer0(void)   interrupt 1   using 1
{
    Time0_flag=1;	           //��ʱ�жϱ�־λ��1;
	TH0=-Pt/256;TL0=-Pt%256;   //���ö�ʱ��T0�ĳ���ֵ
	T0_S++;                    //����
}
*/
/****************************************************************
����������ʱ��1�жϷ�����  �жϺ�:3 ;
��  �ã���
��  ������
����ֵ����
��  �ܣ��ṩ��ʾλ�������ʱ��;
��  ע����ʱ��1,������ʽ0,16λ�Զ���װ�� 1Tģʽ,
/****************************************************************/
/*
void timer1(void)   interrupt 3   using 1
{
    //TL1 = 0xF8;		//���ö�ʱ��ֵ
	//TH1 = 0xE9;		//���ö�ʱ��ֵ
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
���������ⲿ�ж�0������  �жϺ�:0 ;
��  �ã���
��  ������
����ֵ����
��  ������
��  ע������Ӧ�ٶȵ���;
/****************************************************************/
/*
void intersvr0(void) interrupt 0   using 2
{  
	speed++;
	EX0=0;				//�����ж�
	D+=(T0_S-180)*2;   //����ֵ
   	Pt=600+D;       //�õ���ʱ��T0�ĳ���ֵ
	TH0=-Pt/256;TL0=-Pt%256;   //���ö�ʱ��T0�ĳ���ֵ
	T0_S=0;            //���������㣬�����¼���	
	EX0=1;				//�����ж�
}
*/

//ϵͳ������
void main (void)
{
//	uint i;
	LED1=1;
	LED0=0;
	OEC=1;
	Exti_init();
	Time_init();	  //������ʱ����ʼ��
	//TR0=0;
	UART_init();
	UART_Send_Str("֪Ȥ���ӻ�ӭ�㣡");
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

