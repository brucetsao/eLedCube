#include "display_figure.h"
#include "Time.h"

/**********************************************************************************************
������������ģʽ����
��  �ã���
��  ������
����ֵ����
��  ����
��  ע��
/*********************************************************************************************/
void display_figure()
{
	uchar temp;
	time_refurbish();
	if(Time0_flag)
   	{
		Time0_flag=0;
		temp=T0_S-1;
		P2=P0=0xff;
		dis_close();
		if(temp<=180)
		{
			if((temp>=0)&&(temp<32))		  //��ʾ5678λ�ã�
			{	//OE_595=1;
				//dat1=~zhifu[disp_time[(4-(T0_S/8))]][(7-(T0_S%8))*2];
		    	//dat2=~zhifu[disp_time[(4-(T0_S/8))]][(7-(T0_S%8))*2+1];
				dat1=~zhifu[disp_time[(5+(temp/8))]][((temp%8))*2];	 
		    	dat2=~zhifu[disp_time[(5+(temp/8))]][((temp%8))*2+1];
				dat3=0xff;dat4=0xff;
				//display(dat1,dat2,dat3,dat4); display_CLR();
		    }
		    else if((temp>147)&&(temp<180))//	��ʾ1234λ�ã�
		    {	
				dat1=~zhifu[disp_time[(4-(179-temp)/8)]][(7-((179-temp)%8))*2];
		    	dat2=~zhifu[disp_time[(4-(179-temp)/8)]][(7-((179-temp)%8))*2+1];
				dat3=0xff;dat4=0xff;
				//display(dat1,dat2,dat3,dat4);  display_CLR();
			}
			else if((temp>57)&&(temp<90))	//��ʾ9��10��11��12λ�ã�
			{	
				dat2=~zhifu1[disp_time[(12-((89-temp)/8))]][(((89-temp)%8))*2];
		    	dat1=~zhifu1[disp_time[(12-((89-temp)/8))]][(((89-temp)%8))*2+1];
				dat3=0xff;dat4=0xff;
				//display(dat1,dat2,0xdf,dat4); display_CLR();
	   		}
	   		else if((temp>=90)&&(temp<122))//��ʾ13��14��15��16λ�ã�
			{
				dat2=~zhifu1[disp_time[(16-((121-temp)/8))]][(((121-temp)%8))*2];	   //�����ֳ�����32�ַ�
		    	dat1=~zhifu1[disp_time[(16-((121-temp)/8))]][(((121-temp)%8))*2+1];
				dat3=0xff;dat4=0xff;
				//display(dat1,dat2,0xdf,dat4);  display_CLR();
	   		}
	   		else if((temp>=32)&&(temp<=57))//��ʾ13��14��15��16λ�ã�
			{	
				dat1=0xff;dat2=0xff;dat3=0xff;dat4=0xff;
				//display(0xff,0xff,0xdf,0xff);  display_CLR();
	   		}
	   		else if((temp>=122)&&(temp<=147))//��ʾ13��14��15��16λ�ã�
			{	
				dat1=0xff;dat2=0xff;dat3=0xff;dat4=0xff;
				//display(0xff,0xff,0xdf,0xff); display_CLR();
	   		} 
			dat5=pov_hz[line_now][0];
		    dat6=pov_hz[line_now][1];
	   		 LED1=0;LED0=0;	
			 Send_data_A(dat1,dat2);
			 //Send_data_B(dat1);
			 Send_data_B(dat5,dat6);
			 dis_open(); 
			 P2=dat3;
			 P0=dat4;
			 delay();
			 LED0=1;	LED1=1;
			 P0=P2=0xff;
			 dis_close(); 
		}
	}
}