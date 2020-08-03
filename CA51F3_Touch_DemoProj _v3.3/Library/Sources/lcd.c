#ifndef _LCD_C_
#define _LCD_C_
/*********************************************************************************************************************/
#include "ca51f_config.h"

#include "includes\ca51f3sfr.h"
#include "includes\ca51f3xsfr.h"
#include "includes\gpiodef_f3.h"
#include "includes\system.h"
#include "Library\includes\lcd.h"
#include <intrins.h>
/*********************************************************************************************************************/
/***********************************************************************************
��������LCD_init
����˵����LCD�Ĵ�����ʼ��
��������� len		LCDʱ��Դѡ��
						dmod	��������ѡ��
						bias	ƫѹ����
						ldrv	������ѹ�ȼ�����
						lxdiv LCDʱ�ӷ�Ƶϵ��
����ֵ��	��						
***********************************************************************************/
void LCD_init(LEN_TypeDef len,DMOD_TypeDef dmod,BIAS_TypeDef bias,LDRV_TypeDef ldrv,unsigned int lxdiv)
{
	LXDIVH = (unsigned char)(lxdiv>>8);
	LXDIVL = (unsigned char)(lxdiv);	
	LXCFG =	 DMOD(dmod) | BIAS(bias) | LDRV(ldrv);
	LXCON =  LEN(len) | LMOD(LMOD_lcd);	 
}

/***********************************************************************************
��������LCD_WriteLram
����˵����д�����ݵ���ʾ����
��������� 	laddr	��ʾ�����ַ
						ldata	��ʾ��������
����ֵ��	��						
***********************************************************************************/
void LCD_WriteLram(unsigned char laddr, unsigned char ldata)
{
	INDEX = laddr;
	LXDAT = ldata;
}

/***********************************************************************************
��������LCD_ReadLram
����˵��������ʾ�����ȡ����
��������� 	laddr		��ʾ�����ַ
����ֵ��	��ʾ��������			
***********************************************************************************/
unsigned char LCD_ReadLram(unsigned char laddr)
{
	INDEX = laddr;
	return LXDAT;
}
/*********************************************************************************************************************/
#endif