#ifndef _SYSTEM_CLOCK_C_
#define _SYSTEM_CLOCK_C_
/*********************************************************************************************************************/
#include "ca51f_config.h"
#include "includes\ca51f3sfr.h"
#include "includes\ca51f3xsfr.h"
#include "includes\gpiodef_f3.h"

#include "includes\system.h"
#include "Library\includes\system_clock.h"
#include <intrins.h>
/*********************************************************************************************************************/

/***********************************************************************************
函数名  ：		Sys_Clk_Set_IRCH										 	
功能描述：		设置系统时钟为IRCH
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_IRCH(void)
{
	CKCON |= IHCKE;											//IRCH时钟使能
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCH;	//系统时钟切换到IRCH
}
/***********************************************************************************/



/***********************************************************************************
函数名  ：		Sys_Clk_Set_IRCL										 	
功能描述：		设置系统时钟为IRCL
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_IRCL(void)
{
	CKCON |= ILCKE;											//IRCL时钟使能
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCL;	//系统时钟切换到IRCL	
}
/***********************************************************************************/



/***********************************************************************************
函数名  ：		Sys_Clk_Set_XOSCL										 	
功能描述：		设置系统时钟为XOSCL
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_XOSCL(void)
{
	P32F = P32_XOSC_IN_SETTING;					//设置P32为晶振引脚
	P33F = P33_XOSC_OUT_SETTING;				//设置P33为晶振引脚

	CKCON |= XLCKE;											//使能XOSCL时钟
	while(!(CKCON & XLSTA));						//等待XOSCL时钟稳定
	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;	//切换系统时钟到XOSCL	
}
/***********************************************************************************/



/***********************************************************************************
函数名  ：		Sys_Clk_Set_PLL										 	
功能描述：		设置系统时钟为PLL
输入参数：		Multiple   倍频倍数
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_PLL(unsigned char Multiple)	
{
	if(Multiple < 2 || Multiple > 8) return;		//倍频倍数范围为 2~8，超出此范围返回

	PLLCON = PLLON(1) | MULFT(Multiple-2);			//设置倍频倍数并使能PLL
	while(!(PLLCON & PLSTA));										//等待PLL时钟稳定
	CKSEL = (CKSEL&0xF8) | CKSEL_PLL;						//切换系统时钟到PLL
}
/***********************************************************************************/



/***********************************************************************************
函数名  ：		Sys_Clk_Set_TFRC										 	
功能描述：		设置系统时钟为TFRC
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_TFRC(void)
{
	CKCON |= TFCKE;													//使能TFRC时钟
	CKSEL = (CKSEL&0xF8) | CKSEL_TFRC;			//切换系统时钟到TFRC
}
/***********************************************************************************/


/*********************************************************************************************************************/
#endif
