#include "display.H"

//�ⲿ����Ҫ�õ���������Ϊ�ⲿȫ�ֱ���

uchar dat1,dat2,dat3,dat4;	   //ƽ����ʾ���ݱ���
uchar dat5,dat6;			   //������ʾ���ݱ���
uchar pic_id;				   //ͼƬ�л�ID
//ÿ��ͼƬռ��720�ֽڣ�EEPROM ��0X0000����ʼ��ǰ��8��ͼƬ�Ƕ����� �ӵ�9�ſ�ʼ��ʾͼƬ
//ͼƬ����	        	1      2	  3	     4	    5	   6	  7	     8	    9	   10	  11     12	    13	   14	  15	 16	    17	   18	  19	 20	    21	   22	  23	 24	    25	   26	  27	 28	    29	   30	  31      32	 33	    34	    35	    36	   37	  38	 39	    40	   41	  42	 43	    44	   45	  46	 47
//�洢��ַ	ʮ���Ʊ�ʾ	0      720    1440   2160   2880   3600   4320   5040	5760   6480   7200   7920	8640   9360   10080	 10800  11520  12240  12960	 13680  14400  15120  15840	 16560  17280  18000  18720	 19440  20160  20880  21600	  22320  23040  23760	24480  25200  25920  26640	 27360  28080  28800  29520	 30240  30960  31680  32400	 39600
//          16���Ʊ�ʾ	0x0000 0x02D0 0x05A0 0x0870	0x0B40 0x0E10 0x10E0 0x13B0 0x1680 0x1950 0x1C20 0x1EF0 0x21C0 0x2490 0x2760 0x2A30 0x2d00 0x2fd0 0x32a0 0x3570 0x3840 0x3B10 0x3DE0 0x40B0 0x4380 0x4650 0x4920 0x4BF0 0x4EC0 0x5190 0x5460  0x5730 0x5A00 0x5CD0  0x5FA0 0x6270 0x6540 0x6810  0x6AE0 0x6DB0 0x7080 0x7350 0x7620 0x78F0 0x7BC0 0x7E90 0x8160
uint picaddr;       //EEPROMͼƬ������ַ
uint picaddr_end;   //EEPROMͼƬ����������ַ
uint picaddr_start;	//EEPROMͼƬ��������
uchar xdata pov_pic[180][4]; //ͼƬ�������ݻ���
uchar xdata pov_hz[180][2];	 //�����������ݻ���
//bit pic_rd_flag;
//bit pic_red_ok;
//bit Time0_flag=0;	//��ʱ��T0�жϱ�־λ

/*
void pic_chang(void)
{	
	uchar i;
	if(pic_red_ok)
	{
	   if(pic_ch_flag)
	   {
	   	  pic_ch_flag=0;
		   if(pic_rd_flag==0)
		   {
		  	   pov_pic[i][0]= pov_pic[i][1]= pov_pic[i][2]= pov_pic[i][3]=0x00;
			   i++;
			   if(i>179)
			   {
			   i=0;	pic_rd_flag=1;
			   }   
		   }
		   else
		   {
			 	pov_pic[i][0]=IapReadByte(picaddr+0);
				pov_pic[i][1]=IapReadByte(picaddr+1);
				pov_pic[i][2]=IapReadByte(picaddr+2);
				pov_pic[i][3]=IapReadByte(picaddr+3);
				i++;picaddr=picaddr+4;
				if(i>179)
				{
					i=0;
					pic_red_ok=0;
				}  
				//if(picaddr==0x4bf0)
				//if(picaddr==0x1680)
				if(picaddr==0x10E0)	    //�������տ��ֽ�����ַ
				{
					picaddr=0;
					//picaddr=0x1950 ;
				} 
				 
		   }
		}
	}
}
 */
 //ͼƬ�任����
void pic_chang(void)
{	
	uchar i;
	picaddr_end=pic_addr[Addr_num][1]; //��ʼ��ͼƬ����������ַ
	picaddr_start=pic_addr[Addr_num][0];  //������ʼ��ַ	
	if(pic_ch_flag)		 //���125US��
	{
	   pic_ch_flag=0;	 //��125US�жϱ�־λ
	   if(pic_red_ok)	 //���ͼƬ�л�ʱ���־��
	   {
	   	  //ͼƬ�����߳���ʾ
		  /*
		   if(pic_rd_flag==0)
		   {
		  	   pov_pic[i][0]= pov_pic[i][1]= pov_pic[i][2]= pov_pic[i][3]=0x00;	 //��ͼ
			   //pov_hz[i][0]= pov_hz[i][1]=0xff;	  //������
			   i++;
			   if(i>179)
			   {
			    i=0;
			   	pic_rd_flag=1;
			   }   
		   }
		   if(pic_rd_flag==1)
		   
		   */
		   {
			 	pov_pic[i][0]=IapReadByte(picaddr+0);	//��EEPROM��
				pov_pic[i][1]=IapReadByte(picaddr+1);	//��EEPROM��
				pov_pic[i][2]=IapReadByte(picaddr+2);	//��EEPROM��
				pov_pic[i][3]=IapReadByte(picaddr+3);	//��EEPROM��
				//pov_hz[i][0]=hanzi[2*i];
		        //pov_hz[i][1]=hanzi[(2*i+1)];
			    //pov_hz[i][1]=hanzi[359-2*i];	//�Ӻ��������
		        //pov_hz[i][0]=hanzi[359-(2*i+1)];//�Ӻ��������
				i++;picaddr=picaddr+4;
				if(i>179)
				{
					i=0 ;
					pic_red_ok=0; pic_rd_flag=0;
				}  
				//if(picaddr==0x4bf0)   //27��ͼ
				//if(picaddr==0x1680)   //�������Ľ�����ַ
				//if(picaddr==0x1c20)   //�ܲ������Ľ�����ַ
				//if(picaddr==0x8160)	//��дЧ���Ľ�����ַ
				//if(picaddr==0x3b10)		//�������տ��ֽ�����ַ
				//if(picaddr==0x5460)   //30��ͼ
				//if(picaddr==0x2d00)		//���յ��������ַ
				//if(picaddr==0x0E10)		//��������������ַ
				//if(picaddr==0x10E0)		//˫���Ķ���������ַ
				if(picaddr==picaddr_end)		//ÿһ�������Ľ�����ַ
				{
					//picaddr=0x0000;     //���س�ʼ��ַ
					//picaddr=0x1680 ;  //����ͼƬ��ʼ��ַ
					picaddr=picaddr_start; //���س�ʼ��ַ
				} 
				 
		   }
		}
	}
}
//ͼƬ��ʾ����
void display_pic()
{
	
	uchar temp;
	dis_close(); 
    P2=P0=0xff;
	pic_chang();
    if(Time0_flag)	
	{
		Time0_flag=0;
		if(Int0_flag)
		{
			//Int0_flag=0;
			temp=(T0_S-1);
			if((temp)<=180)
			{
				
			
				dat1=~pov_pic[temp][0];
				//_cror_ (dat1, 7);
				dat2=~pov_pic[temp][1];
				//_cror_ (dat2, 7);
				dat3=~pov_pic[temp][2];
				//_cror_ (dat3, 7);
				dat4=~pov_pic[temp][3];
				//_cror_ (dat4, 7);
				/*	
				dat1=~pic2[temp][0];
				dat2=~pic2[temp][1];
				dat3=~pic2[temp][2];
				dat4=~pic2[temp][3]; 
				*/	 
				//dat6=pov_hz[temp][0]; 
			    //dat5=pov_hz[temp][1];
				dat5=pov_hz[line_now][0]; 
			    dat6=pov_hz[line_now][1];
				
				LED1=0;
			LED0=0;	
			Send_data_A(dat1,dat2);
			//Send_data_B(dat1);
			Send_data_B(dat5,dat6);
			
		    //P0=dat3;
			//�ߵ�λ����
			P2=dat3;
			P0=dat4;
			dis_open(); 
			
			delay();
			//LED0=1;	
			//LED1=1;
			dis_close();
			P0=P2=0xff;
			}
		}
		
	}
}