
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/delay.h"
#include "include/lcd_led.h"
#include <intrins.h>
/*********************************************************************************************************************			
	本例程实现4com*9seg、1/3bias LCD显示功能，LCD时钟设置为IRCH，LCD驱动电流设置为最大，不考虑LCD功耗。
*********************************************************************************************************************/			

void main(void)
{	
	unsigned char i;
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("LCD Simple Demo Code\n");
#endif

	//初始化LCD驱动引脚
	P00F = P00_COM0_SETTING;
	P01F = P01_COM1_SETTING;
	P02F = P02_COM2_SETTING;
	P03F = P03_COM3_SETTING;	 
       
	P17F = P17_SEG0_SETTING;
	P37F = P37_SEG1_SETTING; 
	P36F = P36_SEG2_SETTING;  
	P35F = P35_SEG3_SETTING; 
	P34F = P34_SEG4_SETTING;
	P07F = P07_SEG5_SETTING;
	P06F = P06_SEG6_SETTING; 
	P05F = P05_SEG7_SETTING;
	P04F = P04_SEG8_SETTING;	
	
	
	//LCD RAM清零
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}
	

	LXDIVH = 0;				//设置LCD时钟分频，目标帧频率为64HZ
	LXDIVL = 112;	
	LXCFG =	 DMOD(DMOD_130ua) | BIAS(BIAS_1_3) | LDRV(LDRV_7);		//设置LCD驱动电流、偏压(bias)、辉度
	LXCON =  LEN(LEN_IRCH) | LMOD(LMOD_lcd);	 										//设置LCD时钟源，选择LCD模式
	
	//设置LCD全显
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0xFF;
	}
	while(1)
	{
	}
}
#endif
