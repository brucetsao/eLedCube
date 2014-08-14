   
/*****************************Nothing below this line***************************/  

// (c) Copyright 2007-2017, Guozhou Chen. All Rights Reserved. 
 
/******************************************************************************** 
 *  ����������																	*	 
 *			����������STC89C5xϵ�е�Ƭ���ڲ�EEPROMʱ���˽���Է�0xffֵ�Ĵ洢�ռ�* 
 *			����ͨ���ֽڱ��ֱ��д�롣��һԼ�����ܸ�һЩ�˴���Ӧ�õ��鷳�����Ա�* 
 *			�˾�����дһ�ܹ��ó���Ա��������һԼ����API����������Сʱ�ı�д�͵� * 
 *			�ԣ������ܴﵽ����ԭ�������Ŀ�ꡣ����ʱ��ִټ�����ˮƽ���ޣ������* 
 *			��Щ�㷨��Ч����������ָ�̡�Email:chenguozhou1982@yahoo.com.cn��	* 
 *																				* 
 *			������ͨ���ļ����궨��������õ�STC�ĺܶ��ͺ�MCU�ϣ�����ֻ������	* 
 *			STC89C5xϵ��														* 
  
 *			��������������޸ĺʹ������޸�����ע���޸��ˡ��޸�ʱ�䣬����������ע* 
 *			��ԭ�������������κ���ҵĿ�ġ�										* 
 *																				* 
 ******************************************************************************** 
 *  File Name:  EEPROM.C, V0.2.0                                              	* 
 *  Author:     Guozhou Chen                                                  	* 
 *  Date:       2007.09.15                                                   	* 
 *																				* 
 ******************************************************************************** 
 *  ʹ����������˵����															* 
 *					UINT��16λ�޷�������										* 
 *					BYTE��8λ�޷����ַ���										* 
 *					BOOL��1λ��������											* 
 *																				* 
 ******************************************************************************** 
 *  ֱ�ӵ��õ�API˵��:															* 
 *																				* 
 *			������ԭ�Σ�UINT EEPROM_ReadBytes(UINT addr, BYTE *buf, UINT size)	* 
 *						��������ΪUINT���͵�ʵ�ʶ��������ֽ�����				* 
 *			����˵����	addrΪ��Ҫ��ȡEEPROM����ĵ�һ�ֽڵ�ַ��ȡֵ��ΧΪ�ڲ�	* 
 *						EEPROM�����һ������ĵ�ַ�������һ������������Ϊ���档* 
 *						bufΪĿ��������ָ�룬��ָ�򱣴��������������׵�ַ��	* 
 *						sizeΪҪ��������ݵ��ֽ���								* 
 *																				* 
 *			д����ԭ�Σ�UINT EEPROM_WritBytes(UINT addr, BYTE *buf, UINT size)	* 
 *						��������ΪUINT���͵�ʵ��д�������ֽ�����				* 
 *			����˵����	addrΪ��Ҫд��EEPROM����ĵ�һ�ֽڵ�ַ��ȡֵ��ΧΪ�ڲ�	* 
 *						EEPROM�����һ������ĵ�ַ�������һ������������Ϊ���档* 
 *						bufΪԴ������ָ�룬��ָ����Ҫд������������׵�ַ��		* 
 *						sizeΪҪ��д�����ݵ��ֽ���								* 
 *																				* 
 ******************************************************************************** 
 * ʹ��˵����																	* 
 *		1������MCU�ͱ�������ʵ������޸ļ����궨����������Ͷ��塣�궨���������* 
 *			�Ͷ��岿�ֿ��Ե���д��ͷ�ļ���										* 
 *		2������Ҫʹ��EEPROM_ReadBytes������EEPROM_WritBytes�����������ļ������� * 
 *			ԭ��������															* 
 *		3������Ҫ�ĵط�ֱ������ʵ�ε��ü��ɡ�									* 
 *																				* 
 ********************************************************************************/ 
 
/******************************************************************************** 
 *																				* 
 * ͷ�ļ�																		* 
 *																				* 
 ********************************************************************************/ 
#include <STC89C5x.h>

 
/******************************************************************************** 
 *																				* 
 * �������Ͷ���																	* 
 *																				* 
 ********************************************************************************/ 
 typedef unsigned int 	UINT; 
 typedef unsigned char 	BYTE; 
 typedef bit 			BOOL; 
 
/******************************************************************************** 
 *																				* 
 * �궨��																		* 
 *																				* 
 ********************************************************************************/ 
#define BYTES_EACH_SECTOR	512		//MCU EEPROMÿ�������ֽ��� 
 
//CPU�ȴ�ʱ�䣬����0-5M����Ϊ3��5-10MΪ2��10-20MΪ1������20MΪ0 
#define WAIT_TIME			0	 
	 
#define USEING_EACH_SECTOR	512		//�ƻ�ÿ����Ҫ�õ��ֽ���������ԽСд�ٶ�Խ�� 
 
#define EEPROM_ADDR_START	0x2000	//EEPROM��ʼ��ַ 
#define EEPROM_ADDR_END		0xf3ff	//EEPROM������ַ 
 
 
/******************************************************************************** 
 *																				* 
 * ��ָ���׵�ַΪaddr��EEPROM�������size�ֽ����ݵ�bufָ��������ڣ�������ʵ�ʶ�* 
 * �����ݵ��ֽ���																* 
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
		//��ַԽ���� 
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
 * ��bufָ��Ԫ�ڵ�����д���ַΪaddr��EEPROM��Ԫ�ڣ��ɹ�����1�����򷵻�0		* 
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
 * ����AddrInSector��ַ���ڵ���������											* 
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
 * ���׵�ַΪsrc������Ԫ��������size�ֽ����ݵ��׵�ַΪdes������������Ԫ�ڣ����� * 
 * ��ʵ�ʿ������ֽ���															* 
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
 * ��bufָ�������ڵ�size�ֽ�����д���׵�ַΪaddr��EEPROM�������򣬲�����ʵ��д��* 
 * ���ݵ��ֽ���																	* 
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
		//���ֵ�һ����Ԫ����0xff��Ҫ����д��������Ҫ�������������� 
		else											 
		{ 
			//�������������������� 
			ErasureAllSector(EEPROM_ADDR_END); 
 
			cur_sector_start_addr = addr&0xfe00; 
 
			//�ѵ�һ����0xff��Ԫǰ�����ݿ������������� 
			CopySector(cur_sector_start_addr 
						, (EEPROM_ADDR_END + 1 - BYTES_EACH_SECTOR) 
						, (addr - cur_sector_start_addr)); 
 
			//����ʣ����Ҫ�洢��������д�뻺���������׸���Ԫ��ַ 
			bufaddr = (addr - cur_sector_start_addr) 
					+ (EEPROM_ADDR_END + 1 - BYTES_EACH_SECTOR); 
 
			//��ʣ��Ҫ�洢������д�뻺������ 
			for (  ; i < size; i++) 
			{ 
				EEPROM_WritByte(bufaddr, p_buf); 
 
				addr++; 
				bufaddr++; 
				p_buf++; 
				current_size++; 
			} 
			 
			//����Ҫ�ı�����������д�뻺������ 
			if (addr < cur_sector_start_addr + USEING_EACH_SECTOR ) 
			{ 
				CopySector(addr, bufaddr, USEING_EACH_SECTOR  
							- (addr - cur_sector_start_addr));  
			} 
 
			//������ǰ���� 
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
		//�ѻ����������ݿ�������ǰ���� 
		CopySector((EEPROM_ADDR_END - BYTES_EACH_SECTOR + 1) 
					, cur_sector_start_addr, USEING_EACH_SECTOR); 
	} 
	 
	return current_size; 
} 
/*****************************Nothing below this line***************************/







 