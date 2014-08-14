#ifndef __Time_H__
#define	__Time_H__

#include "STC15Fxxxx.h"
#include "intrins.h"
#include "74HC595.H"
#include "Exti.h"
//#include "UART.h"
extern uchar day,month,year,week,second,minute,hour;  //�ⲿ����Ҫ�õ���������Ϊ�ⲿȫ�ֱ���
extern uint T0_S;

extern uint line_now;		//�������������С�����ֵ
extern uint line_vol;
extern uchar irtime;	    //����ң�ؽ���ʱ���׼
extern uint Pt;
extern bit Time0_flag;		//��ʱ��0�жϱ�־
extern bit pic_ch_flag;		//ͼƬ�л���־
extern bit  pic_red_ok;		//ͼƬ�������־
extern bit pic_rd_flag;		//ͼƬ��ɱ�־
extern uchar speed;			//����ٶȱ���
extern uchar speedsum;		//����ٶȼ�������
extern bit open_close_flang;
extern bit time_refurbish_flag; //ʱ��ˢ����ʾ��־
//extern bit T_S0_flag;
//
extern void Time_init(void);

#endif 