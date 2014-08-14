#include "IR_KEY.H"
#include 	"ds1302.h"

//������־λ����
bit menu_flag;	   //MENU
bit test_flag;	   //TEST
bit esc_flag;	   //ESC ����
bit left_flag;	   //����
bit right_falg;	   //����
bit hour_flag;
bit minute_flag;
bit second_falg;
bit year_flag;
bit month_flag;
bit day_falg;
bit rotate_falg;
bit Pchang_falg;
bit pic_o_falg;
bit t_mode_falg;  //ָ�����ѡ���־Ϊ1ʱΪ����ָ����̣�Ϊ0ʱֻΪָ��ʽ����
//ȫ�ֱ�������
uchar DIS_MODE;  //��ʾģʽID
uchar Addr_num;
//uchar line_vol=1;  //���̴�������

//ң���������//
/*�û���00FF */
/*��Դ(0X45) ��(0X46)  MENU(0X47)*/
/*TEST(0X44) + (0X40)  ����(0X43)*/
/* ��  (0X07) �� (0X15)   ��  (0X09)*/
/* 0  (0X16) - (0X19)   C  (0X0D)*/
/* 1  (0X0C) 2 (0X18)   3  (0X5E)*/
/* 4  (0X08) 5 (0X1C)   6  (0X5A)*/
/* 7  (0X42) 8 (0X52)   9  (0X4A)*/

//����ң�ذ�����������
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
						menu_flag=1;	  //�˵�����־
						break;
					case 0x44:		
						test_flag=1;	  //���Լ���־
						break;
					case 0x43:	   
						esc_flag=1;		  //���ؼ���־
						break;
					case 0x07:	
						left_flag=1;	  //���Ƽ���־	 �� 
						break;
					case 0x09:	   
						right_falg=1;	  //���Ƽ���־	 ��
						break;
					case 0x0c:	   
						hour_flag=1;	  //��ʱ����־	 1
						break;
					case 0x18:	
						minute_flag=1;	  //���ּ���־	 2
						break;
					case 0x5e:	   
						second_falg=1;	  //�������־	 3
						break;
					case 0x08:	   
						year_flag=1;	  //�������־	 4
						break;
					case 0x1c:	
						month_flag=1;	  //���¼���־	 5
						break;
					case 0x5A:	   
						day_falg=1;	      //���ռ���־	 6
						break;
					case 0X42:	   
						Pchang_falg=1;	  //�����л�����־	 7
						break;
					case 0x4A:	   
						t_mode_falg=1;	  //ָ������л���־    9
						break;
					case 0x0D:	   		  //��ת��ͣ��־��TEST��C
						rotate_falg=1;	      
						break;
					case 0x16:	   		  //��ת��ͣ��־��TEST��0
						pic_o_falg=1;	      
						break;
					default:
						break;
				}
			//}
		}
		if(menu_flag)	   //ģʽ�л�
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
		if(left_flag)		//����ת������
		{
			left_flag=0; 
			/*if(line_vol==0)	//���жϺ����
			{
			    line_vol=179;
			}
			else
			line_vol--;
			*/
		}
		if(right_falg)	    //����ת������
		{
			right_falg=0 ;
		/*	line_vol++;
		    if(line_vol>179)
		    line_vol=0;
		*/
		}
		if(hour_flag)		//��ʱ
		{
			hour_flag=0; 
			//if(DIS_MODE==0)
			//Addr_num=0;
			hour++;
			write_clock(0x84,hour);   //Сʱ
			if(hour>11)	
		    hour=0;
		}
		if(minute_flag)		//����
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
		if(second_falg)		//����
		{
			second_falg=0;
			//if(DIS_MODE==0)
			//Addr_num=2; 
			second++;
			if(second>59)	
		    second=0;
		}
		if(year_flag)		//����
		{
			year_flag=0; 
			//if(DIS_MODE==0)
			//Addr_num=3;
			year++;
			if(year>25)	   
		    year=13;
		}
		if(month_flag)		//����
		{
			month_flag=0; 
			month++;
			if(month>11)	//
		    month=0;
		}
		if(day_falg)		//����
		{
			day_falg=0; 
			day++;
			if(day>31)	
		    day=0;
		}
		if(t_mode_falg)		//ָ������л�
		{
			t_mode_falg=0; 
			t_mode=~t_mode;
			
		}
		if(rotate_falg)		//��ת��ֹͣ
		{
		//	pic_rotate=~pic_rotate;
		}
		if(pic_o_falg)		//��ת��ֹͣ
		{
		//	pic_ch=~pic_ch;
		}
		if(Pchang_falg)		//����
		{
			Pchang_falg=0; 
			Addr_num++;
			if(Addr_num>3)	//
		    Addr_num=0;
		}
	}			
}