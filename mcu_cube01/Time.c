#include "Time.h"

bit pic_ch_flag;   //ͼƬ�л���־
bit Time0_flag=0;  //��ʱ��0�жϱ�־
bit pic_red_ok=0;  //ͼƬ�������־
bit pic_rd_flag;   //ͼƬ��ɱ�־
bit open_close_flang=0;	
bit time_refurbish_flag; //ʱ��ˢ����ʾ��־
//uint D=400;
uchar speed;	   //����ٶȱ���
uchar speedsum;	   //����ٶȼ�������

uint Pt;		   //����Ӧʱ����װֵ
uint T0_S=179;	   //��ʱ��0�жϣ���ʾ��������ֵ��
uint line_now;	   //�������������С�����ֵ
uint line_vol;	 
uchar irtime;	   //������붨ʱ��1�жϼ�������
uchar num;
uchar day,month,year,week,second,minute,hour; //ϵͳʱ�����

void Time_init(void)	//��ʱ����ʼ��
{
	 AUXR=0XD5;	//����T0 1Tģʽ, ģʽ����ģʽΪ12T, ����ʹ���ڲ�RAM,������������ʷ�������
			    // b7       b6       b5       b4      b3     b2     b1     b0
			    //t0x12   t1x12    uart_m0x6  TR2   T2/CT   T2X12 EXTRAM  SIST2       
			    //	1        1		  0		   1	   0	  1	   	 0      1
				//SIST2   ��ʱ��2�Ƿ���������1�Ĳ����ʷ�����  
				//EXTRAM  �ڲ�/�ⲿRAM��ȡ����	 0�����ڲ�RAM��ȡ��
				//T2x12    ��ʱ��2ʱ��ģʽ
				//T2/CT    ��ʱ��2������ʱ���Ǽ�����
				//TR2      ��ʱ��2��������
				
				
	 TMOD=0X01; //��ʱ��0������ʽ1,/��ʱ��1������ʽ2,8λ�Զ���װ��
			    //   b7   b6   b5  b4  b3   b2  b1   b0/
			    //  GATE  C/T  M1   M0 GATE	C/T M1   M0
			    //    0	  0	   1	0	0	 0	 0	 1

	 /*
	 IT0=1;			 //���ж�0������ʽ,Ϊ1ʱΪ�½�����Ч,Ϊ0ʱ�͵�ƽ��Ч
	 IT1=1;           //���ж�1������ʽ, Ϊ1ʱΪ�½�����Ч,Ϊ0ʱ�͵�ƽ��Ч
 	 EX0=1;			 //���ж�0ʹ�ܱ�־
	 EX1=1;			 //���ж�1ʹ�ܱ�־
	 EA=1;	    //�����жϣ�
	 */
	 TL0 = 0x71;		//���ö�ʱ��ֵ	 153
	 TH0 = 0xDD;		//���ö�ʱ��ֵ
	 //TL1 = 0xF8;		//���ö�ʱ��ֵ	 255
	 //TH1 = 0xE9;		//���ö�ʱ��ֵ
	 TL1 = 0x33;		//���ö�ʱ��ֵ	 125
	 TH1 = 0xF5;		//���ö�ʱ��ֵ
	 TR1 = 1;		     //������ʱ��1
 	 TR0 = 1;		 //�򿪶�ʱ��0
	 //TR1 =0;		 //�ض�ʱ��1
	 //TR0 =0;		 //�ض�ʱ��0
	 ET0 = 1;		 //��ʱ��0�ж�ʹ��,Ϊ1ʱ��,Ϊ0ʱ��
	 ET1 = 1;		 //��ʱ��1�ж�ʹ��,Ϊ1ʱ��,Ϊ0ʱ��
	 //ET0 = 0;		 //��ʱ��0�ж�ʹ��,Ϊ1ʱ��,Ϊ0ʱ��
	 //ET1 = 0;		 //��ʱ��1�ж�ʹ��,Ϊ1ʱ��,Ϊ0ʱ��		 
}
/****************************************************************
����������ʱ��0�жϷ�����  �жϺ�:1 ;
��  �ã���
��  ������
����ֵ����
��  �ܣ��ṩ��ʾλ�������ʱ��;
��  ע����ʱ��0,������ʽ1,16λ��ʱ�� 1Tģʽ,
/****************************************************************/

void timer0(void)   interrupt 1   using 1
{
    TR0=0;
	Time0_flag=1;	           //��ʱ�жϱ�־λ��1;
	TH0=-Pt/256;TL0=-Pt%256;   //���ö�ʱ��T0�ĳ���ֵ
	T0_S++; 
	//if(T0_S>179)                   //����
	//Int0_flag=0;
	line_now=180-line_vol+T0_S;	 //��ʱ����ת
	if(line_now>180)
	line_now=T0_S-line_vol;
	TR0=1;
}

/****************************************************************
����������ʱ��1�жϷ�����  �жϺ�:3 ;
��  �ã���
��  ������
����ֵ����
��  �ܣ��ṩ��ʾλ�������ʱ��;
��  ע����ʱ��1,������ʽ0,16λ�Զ���װ�� 1Tģʽ,
/****************************************************************/

void timer1(void)   interrupt 3   using 2
{
	uint s,j,k,n,c;
	s++; irtime++;	j++; n++;c++;		//	second,minute,hour
	if(j==2)  {j=0;  pic_ch_flag=1;}		  //����ˢ��ʱ��
	if(n==600){n=0;  pic_red_ok=1; }

	//if(j == 50   )  {j=0;  pic_ch_flag=1;}	   //ͼƬˢ�¼��ʱ��
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
	