   
/*****************************Nothing below this line***************************/  

// (c) Copyright 2007-2017, Guozhou Chen. All Rights Reserved. 
 
/******************************************************************************** 
 *  个人申明：																	*	 
 *			本人在运用STC89C5x系列单片机内部EEPROM时，了解其对非0xff值的存储空间* 
 *			不能通过字节编程直接写入。这一约定可能给一些人带来应用的麻烦，所以本* 
 *			人决定编写一能够让程序员不考虑这一约定的API。经过几个小时的编写和调 * 
 *			试，基本能达到本人原本设想的目标。由于时间仓促及个人水平有限，不免会* 
 *			有些算法低效，还望高手指教。Email:chenguozhou1982@yahoo.com.cn。	* 
 *																				* 
 *			本程序通过改几个宏定义可以运用到STC的很多型号MCU上，本人只测试了	* 
 *			STC89C5x系列														* 
  
 *			本程序可以任意修改和传播，修改者请注明修改人、修改时间，传播过程请注* 
 *			明原著。不得用于任何商业目的。										* 
 *																				* 
 ******************************************************************************** 
 *  File Name:  EEPROM.C, V0.2.0                                              	* 
 *  Author:     Guozhou Chen                                                  	* 
 *  Date:       2007.09.15                                                   	* 
 *																				* 
 ******************************************************************************** 
 *  使用数据类型说明：															* 
 *					UINT：16位无符号整形										* 
 *					BYTE：8位无符号字符型										* 
 *					BOOL：1位布尔类型											* 
 *																				* 
 ******************************************************************************** 
 *  直接调用的API说明:															* 
 *																				* 
 *			读函数原形：UINT EEPROM_ReadBytes(UINT addr, BYTE *buf, UINT size)	* 
 *						函数返回为UINT类型的实际读出数据字节数。				* 
 *			参数说明：	addr为需要读取EEPROM区域的第一字节地址，取值范围为内部	* 
 *						EEPROM除最后一扇区外的地址，因最后一扇区被牺牲做为缓存。* 
 *						buf为目的数据区指针，即指向保存读出数据区域的首地址。	* 
 *						size为要求读出数据的字节数								* 
 *																				* 
 *			写函数原形：UINT EEPROM_WritBytes(UINT addr, BYTE *buf, UINT size)	* 
 *						函数返回为UINT类型的实际写入数据字节数。				* 
 *			参数说明：	addr为需要写入EEPROM区域的第一字节地址，取值范围为内部	* 
 *						EEPROM除最后一扇区外的地址，因最后一扇区被牺牲做为缓存。* 
 *						buf为源数据区指针，即指向需要写入数据区域的首地址。		* 
 *						size为要求写入数据的字节数								* 
 *																				* 
 ******************************************************************************** 
 * 使用说明：																	* 
 *		1、根据MCU和编译器的实际情况修改几个宏定义和数据类型定义。宏定义和数据类* 
 *			型定义部分可以单独写成头文件。										* 
 *		2、在需要使用EEPROM_ReadBytes（）和EEPROM_WritBytes（）函数的文件中做个 * 
 *			原形申明。															* 
 *		3、在需要的地方直接添入实参调用即可。									* 
 *																				* 
 ********************************************************************************/ 
 
/******************************************************************************** 
 *																				* 
 * 头文件																		* 
 *																				* 
 ********************************************************************************/ 
#include <STC89C5x.h>

 
/******************************************************************************** 
 *																				* 
 * 数据类型定义																	* 
 *																				* 
 ********************************************************************************/ 
 typedef unsigned int 	UINT; 
 typedef unsigned char 	BYTE; 
 typedef bit 			BOOL; 
 
/******************************************************************************** 
 *																				* 
 * 宏定义																		* 
 *																				* 
 ********************************************************************************/ 
#define BYTES_EACH_SECTOR	512		//MCU EEPROM每扇区的字节数 
 
//CPU等待时间，晶振0-5M设置为3，5-10M为2，10-20M为1，大于20M为0 
#define WAIT_TIME			0	 
	 
#define USEING_EACH_SECTOR	512		//计划每扇区要用的字节数，用量越小写速度越快 
 
#define EEPROM_ADDR_START	0x2000	//EEPROM起始地址 
#define EEPROM_ADDR_END		0xf3ff	//EEPROM结束地址 
 
 
/******************************************************************************** 
 *																				* 
 * 从指定首地址为addr的EEPROM区域读出size字节数据到buf指向的区域内，并返回实际读* 
 * 出数据的字节数																* 
 *																				* 
 ********************************************************************************/ 
 
UINT EEPROM_ReadBytes(UINT addr, BYTE *buf, const UINT size) 
{ 
	BOOL old_EA; 
	 
	BYTE *p_buf;	 
	UINT i, current_size; 
	 
	p_buf = buf; 
	current_size = 0; 
	 
	ISP_CMD = 0x01; 
	ISP_CONTR = 0x80|WAIT_TIME;  
 
	for (i = 0; i < size; i++) 
	{ 
		//地址越界检测 
		if ((addr < EEPROM_ADDR_START)	|| (addr > EEPROM_ADDR_END)) 
		{ 
			break;	 
		}			 
		 
		ISP_ADDRH = addr>>8; 
		ISP_ADDRL = addr&0x00ff; 
		 
		old_EA = EA; 
		EA = 0; 
		 
		ISP_TRIG = 0x46; 
		ISP_TRIG = 0xB9; 
		 
		EA = old_EA; 
 
		*p_buf = ISP_DATA; 
				 
		addr++; 
		p_buf++; 
		current_size++; 
 
	} 
	ISP_CMD = 0x00;	 
	ISP_CONTR = 0x00;  
	 
	return current_size; 
} 
 
/******************************************************************************** 
 * 																				* 
 * 把buf指向单元内的数据写入地址为addr的EEPROM单元内，成功返回1，或则返回0		* 
 *																				* 
 ********************************************************************************/ 
BOOL EEPROM_WritByte(UINT addr, BYTE *buf) 
{ 
	BOOL old_EA; 
 
	if ((addr < EEPROM_ADDR_START) || (addr > EEPROM_ADDR_END)) 
	{ 
		return 0;	 
	} 
	 
	ISP_CMD = 0x02; 
	ISP_CONTR = 0x80|WAIT_TIME; 
				 
	ISP_DATA = (*buf); 
	 
	ISP_ADDRH = addr>>8; 
	ISP_ADDRL = addr&0x00ff; 
	 
	old_EA = EA;	 
	EA = 0; 
		 
	ISP_TRIG = 0x46; 
	ISP_TRIG = 0xB9; 
		 
	EA = old_EA;	 
	 
	ISP_CMD = 0x00;	 
	ISP_CONTR = 0x00;  
		 
	return 1;	 
} 
 
/******************************************************************************** 
 *																				* 
 * 擦除AddrInSector地址所在的整个扇区											* 
 *																				* 
 ********************************************************************************/ 
void ErasureAllSector(UINT AddrInSector) 
{ 
	BOOL old_EA; 
	 
	ISP_CMD = 0x03; 
	ISP_CONTR = 0x80|WAIT_TIME; 
	 
	ISP_ADDRH = AddrInSector>>8; 
	ISP_ADDRL = AddrInSector&0x00ff; 
	 
	old_EA = EA;	 
	EA = 0; 
		 
	ISP_TRIG = 0x46; 
	ISP_TRIG = 0xB9; 
		 
	EA = old_EA;	 
	 
	ISP_CMD = 0x00;	 
	ISP_CONTR = 0x00; 	 
} 
 
/******************************************************************************** 
 *																				* 
 * 从首地址为src扇区单元拷贝连续size字节数据到首地址为des的连续扇区单元内，并返 * 
 * 回实际拷贝的字节数															* 
 *																				* 
 ********************************************************************************/ 
UINT CopySector(UINT src, UINT des, const UINT size) 
{ 
	BYTE temp; 
	UINT current_size, i; 
	 
	current_size = 0; 
	 
	for (i = 0; i < size; i++) 
	{ 
		if (!EEPROM_ReadBytes(src, &temp, 1)) 
		{ 
			break;	 
		} 
		 
		if (!EEPROM_WritByte(des, &temp))	 
		{ 
			break;	 
		} 
		 
		des++; 
		src++; 
		current_size++;		 
	} 
	 
	return 	current_size; 
} 
 
/******************************************************************************** 
 *																				* 
 * 把buf指向区域内的size字节数据写入首地址为addr的EEPROM连续区域，并返回实际写入* 
 * 数据的字节数																	* 
 *																				* 
 ********************************************************************************/ 
UINT EEPROM_WritBytes(UINT addr, BYTE *buf, const UINT size) 
{ 
	BYTE *p_buf, temp, move; 
	 
	UINT i, bufaddr, current_size, cur_sector_start_addr; 
	 
	p_buf = buf; 
	 
	move = 0; 
	current_size = 0; 
	 
	for (i = 0; i < size; i++) 
	{ 
		if (!EEPROM_ReadBytes(addr, &temp, 1)) 
		{ 
			break;	 
		} 
		 
		if (temp == 0xff) 
		{ 
			EEPROM_WritByte(addr, p_buf); 
		} 
		//发现第一个单元不是0xff，要从新写入数据需要做擦除整个扇区 
		else											 
		{ 
			//擦除用作缓冲的这个扇区 
			ErasureAllSector(EEPROM_ADDR_END); 
 
			cur_sector_start_addr = addr&0xfe00; 
 
			//把第一个非0xff单元前的数据拷贝到缓冲扇区 
			CopySector(cur_sector_start_addr 
						, (EEPROM_ADDR_END + 1 - BYTES_EACH_SECTOR) 
						, (addr - cur_sector_start_addr)); 
 
			//计算剩余需要存储的数据需写入缓冲扇区的首个单元地址 
			bufaddr = (addr - cur_sector_start_addr) 
					+ (EEPROM_ADDR_END + 1 - BYTES_EACH_SECTOR); 
 
			//把剩余要存储的数据写入缓冲扇区 
			for (  ; i < size; i++) 
			{ 
				EEPROM_WritByte(bufaddr, p_buf); 
 
				addr++; 
				bufaddr++; 
				p_buf++; 
				current_size++; 
			} 
			 
			//把需要改变区域后的数据写入缓冲扇区 
			if (addr < cur_sector_start_addr + USEING_EACH_SECTOR ) 
			{ 
				CopySector(addr, bufaddr, USEING_EACH_SECTOR  
							- (addr - cur_sector_start_addr));  
			} 
 
			//擦除当前扇区 
			ErasureAllSector(cur_sector_start_addr); 
			move = 1; 
			break; 
		} 
		 
		addr++; 
		p_buf++; 
		current_size++; 
	} 
	 
	if (move) 
	{ 
		//把缓冲扇区数据拷贝到当前扇区 
		CopySector((EEPROM_ADDR_END - BYTES_EACH_SECTOR + 1) 
					, cur_sector_start_addr, USEING_EACH_SECTOR); 
	} 
	 
	return current_size; 
} 
/*****************************Nothing below this line***************************/







 