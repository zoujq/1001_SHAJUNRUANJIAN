
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
	������ʵ��4com*9seg��1/3bias LCD��ʾ���ܣ�LCDʱ������ΪIRCH��LCD������������Ϊ��󣬲�����LCD���ġ�
*********************************************************************************************************************/			

void main(void)
{	
	unsigned char i;
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("LCD Simple Demo Code\n");
#endif

	//��ʼ��LCD��������
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
	
	
	//LCD RAM����
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}
	

	LXDIVH = 0;				//����LCDʱ�ӷ�Ƶ��Ŀ��֡Ƶ��Ϊ64HZ
	LXDIVL = 112;	
	LXCFG =	 DMOD(DMOD_130ua) | BIAS(BIAS_1_3) | LDRV(LDRV_7);		//����LCD����������ƫѹ(bias)���Զ�
	LXCON =  LEN(LEN_IRCH) | LMOD(LMOD_lcd);	 										//����LCDʱ��Դ��ѡ��LCDģʽ
	
	//����LCDȫ��
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
