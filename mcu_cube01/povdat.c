/*********************************************
	项 目:	多功能旋转POV LED 
	模 块：	数据库文件
	功 能：	提供系统所需的数据
	版 本：	V5.0
	设 计：	智趣电子
	时 间：	2013年11月25日
	修 改:	2013.10.28.19:00 创建项目
	说 明：
********************************************/					  

#include "povdat.h" 
//每张图片占用720字节，EEPROM 从0X0000，开始，前面8张图片是动画； 从第9张开始显示图片
//图片张数	        	1      2	  3	     4	    5	   6	  7	     8	    9	   10	  11     12	    13	   14	  15	 16	    17	   18	  19	 20	    21	   22	  23	 24	    25	   26	  27	 28	    29	   30	  31      32	 33	    34	    35	    36	   37	  38	 39	    40	   41	  42	 43	    44	   45	  46	 47
//存储地址	十进制表示	0      720    1440   2160   2880   3600   4320   5040	5760   6480   7200   7920	8640   9360   10080	 10800  11520  12240  12960	 13680  14400  15120  15840	 16560  17280  18000  18720	 19440  20160  20880  21600	  22320  23040  23760	24480  25200  25920  26640	 27360  28080  28800  29520	 30240  30960  31680  32400	 39600
//          16进制表示	0x0000 0x02D0 0x05A0 0x0870	0x0B40 0x0E10 0x10E0 0x13B0 0x1680 0x1950 0x1C20 0x1EF0 0x21C0 0x2490 0x2760 0x2A30 0x2d00 0x2fd0 0x32a0 0x3570 0x3840 0x3B10 0x3DE0 0x40B0 0x4380 0x4650 0x4920 0x4BF0 0x4EC0 0x5190 0x5460  0x5730 0x5A00 0x5CD0  0x5FA0 0x6270 0x6540 0x6810  0x6AE0 0x6DB0 0x7080 0x7350 0x7620 0x78F0 0x7BC0 0x7E90 0x8160
//uint picaddr;       //EEPROM图片动画地址
//图片调用地址数组
uint code pic_addr[][2]=
{
	{0x0000,0x1680}, //奔马动画
	{0x1680,0x2490}, //奔马动画
	{0x2490,0x5190}, //奔马动画
	{0x5190,0x6DB0}, //奔马动画
};
//中国义乌
uchar code pic2[][4]=
{

{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xF7,0xF7,0xFF},{0xFF,0xC7,0xE3,0xFF},{0xFF,0x7, 0xE0,0xFF},
{0xFF,0xF,0xE0,0xFF},{0xFF,0xF,0xE0,0xFF},{0xFF,0xF,0xE0,0xFF},{0xFF,0x8F,0xC0,0xFF},
{0x9F,0x8F,0xC1,0xFF},{0x1F,0xF,0xC3,0xFF},{0x1F,0xC,0xC7,0xFF},{0x1F,0x10,0x86,0xFF},
{0x9F,0x30,0x4,0xFF},{0x9F,0x23,0xC,0xFF},{0x8F,0x42,0xC,0xFF},{0x8F,0x8C,0x8,0xFF},
{0x8F,0x88,0x9,0xFE},{0x8F,0x10,0x7,0xFE},{0x9F,0x10,0x7,0xFE},{0x1F,0x21,0xC6,0xFE},
{0x3F,0x23,0xE2,0xFF},{0x7F,0x2,0xE2,0xFF},{0xFF,0x7,0xF0,0xFF},{0xFF,0x47,0xF0,0xFF},
{0xFF,0x4F,0xF8,0xFF},{0xFF,0xF,0xF8,0xFF},{0xFF,0xF,0xFC,0xFF},{0xFF,0x8F,0xFE,0xFF},
{0xFF,0x8F,0xFF,0xFF},{0xFF,0x8F,0xFF,0xFF},{0xFF,0x8F,0xFF,0xFF},{0xFF,0x9F,0xFF,0xFF},
{0xFF,0x9F,0xFF,0xFF},{0xFF,0x9F,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0x9F,0xFF,0xFF},
{0xFF,0x8F,0xFF,0xFF},{0xFF,0x8F,0xFF,0xFF},{0xFF,0x8F,0xFF,0xFF},{0xFF,0xF,0xFF,0xFF},
{0xFF,0x7,0xFF,0xFF},{0xFF,0x7,0xFF,0xFF},{0xFF,0x7,0xFF,0xFF},{0xFF,0xF,0xFF,0xFF},
{0xFF,0xF,0xFF,0xFF},{0xFF,0x1F,0xFF,0xFF},{0xFF,0x1F,0xFF,0xFF},{0xFF,0x1F,0xFF,0xFF},
{0xFF,0x3F,0xFF,0xFF},{0xFF,0x3F,0xFF,0xFF},{0xFF,0x3F,0xFF,0xFF},{0xFF,0x3F,0xFF,0xFF},
{0xFF,0x7,0xFC,0xFF},{0xFF,0x0,0xE0,0xFF},{0x3F,0x0,0x0,0xFF},{0x1F,0x30,0x1,0xFE},
{0xF,0x3E,0x7,0xFE},{0xF,0x3F,0xF,0xFE},{0x8F,0x1F,0x1B,0xFE},{0x9F,0x9F,0x19,0xFF},
{0xFF,0x8F,0xD9,0xFF},{0xFF,0x87,0xF9,0xFF},{0xFF,0x87,0xF9,0xFF},{0xFF,0xC3,0xF8,0xFF},
{0xFF,0xC7,0xF8,0xFF},{0xFF,0xE7,0xF8,0xFF},{0xFF,0x6F,0xF8,0xFF},{0xFF,0xFF,0xF8,0xFF},
{0xFF,0xFF,0xFC,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xEF,0xFF},{0xFF,0xFF,0xCF,0xFF},
{0xFF,0xFF,0xCF,0xFF},{0xFF,0xFF,0xC7,0xFF},{0xFF,0xF9,0xC7,0xFF},{0xFF,0xF9,0xC7,0xFF},
{0xFF,0xF1,0xC7,0xFF},{0xFF,0xE1,0xE3,0xFF},{0xFF,0xE1,0xE3,0xFF},{0xFF,0xC1,0xE3,0xFF},
{0xFF,0x81,0xE3,0xFF},{0x3F,0x88,0xF1,0xFF},{0x1F,0xC,0xF1,0xFF},{0x3F,0x1C,0xF8,0xFF},
{0x7F,0x3C,0xF8,0xFF},{0x7F,0x38,0xFC,0xFF},{0xFF,0x38,0xFC,0xFF},{0xFF,0x30,0xFC,0xFF},
{0xFF,0x11,0xF8,0xFF},{0xFF,0x1,0xF8,0xFF},{0xFF,0x83,0xF0,0xFF},{0xFF,0xC3,0xF1,0xFF},
{0xFF,0xC1,0xF1,0xFF},{0xFF,0xC3,0xF1,0xFF},{0xFF,0xCF,0xE3,0xFF},{0xFF,0x8F,0xE3,0xFF},
{0xFF,0x8F,0xE3,0xFF},{0xFF,0x9F,0xC3,0xFF},{0xFF,0x1F,0xC1,0xFF},{0xFF,0x1F,0xC0,0xFF},
{0xFF,0x3F,0xF0,0xFF},{0xFF,0x3F,0xF8,0xFF},{0xFF,0x3F,0xFC,0xFF},{0xFF,0x3F,0xFC,0xFF},
{0xFF,0x3F,0xFE,0xFF},{0xFF,0x7F,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0x1F,0xFE,0xFF},{0xFF,0x1F,0xFE,0xFF},{0xFF,0x1F,0xFC,0xFF},
{0xFF,0x1F,0xF0,0xFF},{0xFF,0x1F,0xE0,0xFF},{0xFF,0x8F,0xC1,0xFF},{0xFF,0xF,0x4,0xFF},
{0xFF,0x4F,0xC,0xFF},{0xFF,0x47,0x10,0xFC},{0xFF,0x27,0x22,0xFC},{0xFF,0x3,0x72,0xFC},
{0xFF,0x13,0x51,0xF8},{0xFF,0x1,0xD1,0xF8},{0xFF,0x88,0x90,0xF8},{0x7F,0x4,0x88,0xF1},
{0x7F,0x0,0x84,0xF0},{0x3F,0x2,0x86,0xF0},{0x1F,0x11,0x0,0xF0},{0x8F,0x8,0x40,0xF0},
{0x7,0x0,0x20,0xF0},{0x7,0x40,0x0,0xF0},{0x1F,0x3,0x8,0xFC},{0x3F,0x11,0xC,0xFC},
{0x7F,0x1E,0x2,0xFE},{0xFF,0xC,0x1,0xFF},{0xFF,0x84,0xC0,0xFF},{0xFF,0x44,0xC0,0xFF},
{0xFF,0x29,0xE0,0xFF},{0xFF,0x19,0xF8,0xFF},{0xFF,0x1,0xFC,0xFF},{0xFF,0x3,0xFE,0xFF},
{0xFF,0x83,0xFF,0xFF},{0xFF,0xE3,0xFF,0xFF},{0xFF,0xE3,0xFF,0xFF},{0xFF,0xF7,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},
{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},

};

uint code hanzi[360] = {
//  h(0) a(1) p(2) p(3) y(4)  (5) b(6) i(7) r(8) t(9) h(10) d(11) a(12) y(13) 青(14) 春(15) 美(16) 丽(17)

0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,

//    时(0) 光(1) 不(2) 老(3) -(4) -(5) 我(6) 们(7) 不(8) 散(9)

0xFF,0xFF,0xC0,0x1F,0xDD,0xDF,0xDD,0xDF,0xDD,0xDF,0xC0,0x1F,0xF7,0xFF,0xF6,0xFF,
0xF7,0x3F,0xF7,0xFD,0xF7,0xFE,0x00,0x01,0xF7,0xFF,0xF7,0xFF,0xF7,0xFF,0xFF,0xFF,/*"时",0*/

0xFF,0xFF,0xFD,0xFE,0xBD,0xFD,0xDD,0xFB,0xC5,0xE7,0xEC,0x1F,0xFD,0xFF,0x01,0xFF,
0xFD,0xFF,0xFC,0x03,0xF5,0xFD,0x8D,0xFD,0xDD,0xFD,0xF9,0xFD,0xFD,0xE1,0xFF,0xFF,/*"光",1*/

0xFF,0xFF,0xBF,0xEF,0xBF,0xDF,0xBF,0xBF,0xBF,0x7F,0xBE,0xFF,0xBD,0xFF,0x80,0x01,
0x9F,0xFF,0xBD,0xFF,0xBC,0xFF,0xBE,0x7F,0xBF,0x1F,0x3F,0xBF,0xBF,0xFF,0xFF,0xFF,/*"不",2*/

0xFD,0xEF,0xDD,0xEF,0xDD,0xDF,0xDD,0xDF,0xDD,0xBF,0xDD,0x83,0x01,0x6D,0xDC,0xED,
0xDC,0xDD,0xDD,0xDD,0xD9,0xBD,0xD5,0xBD,0x8D,0xFD,0xDD,0xF1,0xFD,0xFF,0xFF,0xFF,/*"老",3*/

0xFF,0xFF,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,/*"-",4*/

0xFF,0xFF,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,/*"-",5*/

0xFB,0xDF,0xFB,0xDF,0xBB,0xBD,0xBB,0xBE,0x80,0x01,0x7B,0x7F,0x7B,0x7F,0xFB,0xF7,
0xFB,0xF7,0x00,0xEF,0xFB,0x1F,0xBB,0xA7,0xCA,0x7B,0xFB,0xFD,0xFB,0xF0,0xFF,0xFF,/*"我",6*/

0xFE,0xFF,0xFD,0xFF,0xF0,0x01,0xC7,0xFF,0x3F,0xFF,0xF0,0x01,0x7F,0xFF,0x8F,0xFF,
0xDF,0xFF,0xFF,0xFF,0xDF,0xFF,0xDF,0xFB,0xDF,0xFD,0xC0,0x03,0xFF,0xFF,0xFF,0xFF,/*"们",7*/

0xFF,0xFF,0xBF,0xEF,0xBF,0xDF,0xBF,0xBF,0xBF,0x7F,0xBE,0xFF,0xBD,0xFF,0x80,0x01,
0x9F,0xFF,0xBD,0xFF,0xBC,0xFF,0xBE,0x7F,0xBF,0x1F,0x3F,0xBF,0xBF,0xFF,0xFF,0xFF,/*"不",8*/

0xDB,0xFF,0xDA,0x00,0x02,0xAF,0xDA,0xAF,0xDA,0xAD,0x02,0xAE,0xDA,0x01,0xDA,0xFF,
0xF9,0xFE,0x04,0xFD,0xB7,0x33,0xF7,0xCF,0xF6,0x33,0xF1,0xFC,0xF7,0xFD,0xFF,0xFF,/*"散",9*/


0xFF,0xFF,0xF0,0xFF,0xE0,0x7F,0xC0,0x3F,0xC0,0x1F,0xE0,0x0F,0xF0,0x07,0xF8,0x03,   //心形图
0xF8,0x03,0xF0,0x07,0xE0,0x0F,0xC0,0x1F,0xC0,0x3F,0xE0,0x7F,0xF0,0xFF,0xFF,0xFF,

0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,

 };

 uchar code zhifu[13][16]={
{0x00,0x00,0xFC,0x03,0xFE,0x07,0x02,0x04,0x02,0x04,0xFE,0x07,0xFC,0x03,0x00,0x00},/*"0",0*/
{0x00,0x00,0x04,0x00,0x04,0x00,0xFE,0x07,0xFE,0x07,0x00,0x00,0x00,0x00,0x00,0x00},/*"1",1*/
{0x00,0x00,0x0C,0x07,0x8E,0x07,0xC2,0x04,0x62,0x04,0x3E,0x04,0x1C,0x04,0x00,0x00},/*"2",2*/
{0x00,0x00,0x04,0x02,0x06,0x06,0x22,0x04,0x22,0x04,0xFE,0x07,0xDC,0x03,0x00,0x00},/*"3",3*/
{0x00,0x00,0x80,0x01,0xE0,0x01,0x78,0x01,0x1C,0x01,0xFE,0x07,0xFE,0x07,0x00,0x00},/*"4",4*/
{0x00,0x00,0x7E,0x02,0x7E,0x06,0x22,0x04,0x22,0x04,0xE2,0x07,0xC2,0x03,0x00,0x00},/*"5",5*/
{0x00,0x00,0xFC,0x03,0xFE,0x07,0x22,0x04,0x22,0x04,0xE6,0x07,0xC4,0x03,0x00,0x00},/*"6",6*/
{0x00,0x00,0x02,0x00,0x02,0x07,0xE2,0x07,0xFA,0x00,0x1E,0x00,0x06,0x00,0x00,0x00},/*"7",7*/
{0x00,0x00,0xDC,0x03,0xFE,0x07,0x22,0x04,0x22,0x04,0xFE,0x07,0xDC,0x03,0x00,0x00},/*"8",8*/
{0x00,0x00,0x3C,0x02,0x7E,0x06,0x42,0x04,0x42,0x04,0xFE,0x07,0xFC,0x03,0x00,0x00},/*"9",9*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x03,0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00},/*":",10*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*" ",11*/
{0x00,0x00,0x00,0x0C,0x00,0x0F,0xC0,0x03,0xF0,0x00,0x3C,0x00,0x0C,0x00,0x00,0x00},/*"/",12*/

};

uchar code zhifu1[11][16]={
{0x03,0xFC,0x07,0xFE,0x04,0x02,0x04,0x02,0x07,0xFE,0x03,0xFC,0x00,0x00},/*"0",0*/
{0x02,0x00,0x02,0x00,0x07,0xFE,0x07,0xFE,0x00,0x00,0x00,0x00,0x00,0x00},/*"1",1*/
{0x03,0x0E,0x07,0x1E,0x04,0x32,0x04,0x62,0x07,0xC2,0x03,0x82,0x00,0x00},/*"2",2*/
{0x02,0x04,0x06,0x06,0x04,0x42,0x04,0x42,0x07,0xFE,0x03,0xBC,0x00,0x00},/*"3",3*/
{0x00,0x18,0x00,0x78,0x01,0xE8,0x03,0x88,0x07,0xFE,0x07,0xFE,0x00,0x00},/*"4",4*/
{0x07,0xE4,0x07,0xE6,0x04,0x42,0x04,0x42,0x04,0x7E,0x04,0x3C,0x00,0x00},/*"5",5*/
{0x03,0xFC,0x07,0xFE,0x04,0x42,0x04,0x42,0x06,0x7E,0x02,0x3C,0x00,0x00},/*"6",6*/
{0x04,0x00,0x04,0x0E,0x04,0x7E,0x05,0xF0,0x07,0x80,0x06,0x00,0x00,0x00},/*"7",7*/
{0x03,0xBC,0x07,0xFE,0x04,0x42,0x04,0x42,0x07,0xFE,0x03,0xBC,0x00,0x00},/*"8",8*/
{0x03,0xC4,0x07,0xE6,0x04,0x22,0x04,0x22,0x07,0xFE,0x03,0xFC,0x00,0x00},/*"9",9*/
{0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00},/*"-",0*/
//{0x00,0x00,0x00,0x06,0x00,0x18,0x00,0x60,0x01,0x80,0x06,0x00,0x00,0x00,0x00,0x00},/*"/",0*/
//{0x00,0x00,0x00,0x03,0x00,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC0,0x03,0x00,0x00,0x00},/*"/",10*/
};