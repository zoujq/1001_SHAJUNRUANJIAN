
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
#include "include/adc.h"
#include <intrins.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>

/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"		   
/*********************************************************************************************************************/
unsigned char read_inner_trim(void)				
{
	unsigned char value;
	FSCMD = 0x80;	
	PTSH  = 0x00;				
	PTSL  = 0x24;      
	FSCMD = 0x81;						
	value = FSDAT;
	FSCMD = 0;
	return (value&0x3F);
}

unsigned int get_ntc_ad_value()
{
	unsigned int AD_Value;
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//设置ADC参考电压为VDD
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());							//加载内部1.5V校准值
	ADCFGL = ACKD(7) | ADCHS(ADC_CH4);	//选择ADC4通道

	
	ADCON |= AST(1);																//启动ADC转换
	while(!(ADCON & ADIF));													//等待ADC转换完成
	ADCON |= ADIF;																	//清除ADC中断标志
	AD_Value = ADCDH*256 + ADCDL;										//读取AD值
	AD_Value >>= 4;	
	return AD_Value;
}

unsigned int get_bat_ad_value()
{
	unsigned int AD_Value;
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//设置ADC参考电压为VDD
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());							//加载内部1.5V校准值
	ADCFGL = ACKD(7) | ADCHS(ADC_CH6);	//选择ADC6通道
	
	ADCON |= AST(1);																//启动ADC转换
	while(!(ADCON & ADIF));													//等待ADC转换完成
	ADCON |= ADIF;																	//清除ADC中断标志
	AD_Value = ADCDH*256 + ADCDL;										//读取AD值
	AD_Value >>= 4;	
	return AD_Value;
}
/*********************************************************************************************************************
	本例程以P00为例，设置P00为不同模式，所有IO用法与P00相同。
*********************************************************************************************************************/
void main(void)
{
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
	//uart_printf("GPIO Demo Code\n");
#endif

/**************************************************************************************************/
	//P00F = OUTPUT;		//P00设置为推挽输出模式
	uart_printf("start\n\r");
	
  P32F = OUTPUT;						//R
	P33F = OUTPUT;						//B
	P00F = OUTPUT;						//G
	
	P30F = OUTPUT;						//backlight
	P31F = OUTPUT;						//speak
	
	//NTC ADC start
	P13F = OUTPUT;//NTC VCC	
	P14F = P14_ADC4_SETTING;	//设置P14为ADC引脚功能

	//charge check
	P15F = INPUT;						//CHARG_CHECK
	
	//bat adc
	P16F = P16_ADC6_SETTING;	//设置P16为BAT ADC引脚功能

	
	P32=0;
	P33=0;
	P00=0;
	P30=0;
	P31=1;
	while(1)
	{

			
		uart_printf("get_bat_ad_value(%d)\n\r",get_bat_ad_value());
		uart_printf("get_ntc_ad_value(%d)\n\r",get_ntc_ad_value());
		

		Delay_ms(2000);
	}
	
	uart_printf("test2\n");
/***********************************************************************************/		


/***********************************************************************************/		
	P00F = INPUT;			//P00设置为输入模式
	while(1)
	{
		if(P00)
		{
#ifdef PRINT_EN
			uart_printf("P00 Input High!\n");
#endif
		}
		else
		{
#ifdef PRINT_EN
			uart_printf("P00 Input Low!\n");
#endif
		}
	}
/***********************************************************************************/	
	
	
	

/***********************************************************************************/	
	P00F = OUTPUT;						//P00设置为推挽输出模式
	P00C |= 0x80;							//P00使能高灌电流模式
/***********************************************************************************/	

	
/***********************************************************************************/	
	P00F = INPUT|PU_EN;				//P00设置为输入模式并使能上拉电阻
	P00C |= 0x20;							//上拉电阻选择为强上拉
// 	P00C &= ~0x20;					//上拉电阻选择为弱上拉
/***********************************************************************************/



/***********************************************************************************/	
	P00F = INPUT|PD_EN;				//P00设置为输入模式并使能下拉电阻
	P00C |= 0x10;							//下拉电阻选择为强下拉
// 	P00C &= ~0x10;					//下拉电阻选择为弱下拉
/***********************************************************************************/	


/***********************************************************************************/	
	P00F = P00_COM0_SETTING;		//P00设置为COM引脚功能
/***********************************************************************************/	
	
	while(1)
	{

	}
}
#endif
