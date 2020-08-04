
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
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//����ADC�ο���ѹΪVDD
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());							//�����ڲ�1.5VУ׼ֵ
	ADCFGL = ACKD(7) | ADCHS(ADC_CH4);	//ѡ��ADC4ͨ��

	
	ADCON |= AST(1);																//����ADCת��
	while(!(ADCON & ADIF));													//�ȴ�ADCת�����
	ADCON |= ADIF;																	//���ADC�жϱ�־
	AD_Value = ADCDH*256 + ADCDL;										//��ȡADֵ
	AD_Value >>= 4;	
	return AD_Value;
}

unsigned int get_bat_ad_value()
{
	unsigned int AD_Value;
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//����ADC�ο���ѹΪVDD
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());							//�����ڲ�1.5VУ׼ֵ
	ADCFGL = ACKD(7) | ADCHS(ADC_CH6);	//ѡ��ADC6ͨ��
	
	ADCON |= AST(1);																//����ADCת��
	while(!(ADCON & ADIF));													//�ȴ�ADCת�����
	ADCON |= ADIF;																	//���ADC�жϱ�־
	AD_Value = ADCDH*256 + ADCDL;										//��ȡADֵ
	AD_Value >>= 4;	
	return AD_Value;
}
/*********************************************************************************************************************
	��������P00Ϊ��������P00Ϊ��ͬģʽ������IO�÷���P00��ͬ��
*********************************************************************************************************************/
void main(void)
{
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
	//uart_printf("GPIO Demo Code\n");
#endif

/**************************************************************************************************/
	//P00F = OUTPUT;		//P00����Ϊ�������ģʽ
	uart_printf("start\n\r");
	
  P32F = OUTPUT;						//R
	P33F = OUTPUT;						//B
	P00F = OUTPUT;						//G
	
	P30F = OUTPUT;						//backlight
	P31F = OUTPUT;						//speak
	
	//NTC ADC start
	P13F = OUTPUT;//NTC VCC	
	P14F = P14_ADC4_SETTING;	//����P14ΪADC���Ź���

	//charge check
	P15F = INPUT;						//CHARG_CHECK
	
	//bat adc
	P16F = P16_ADC6_SETTING;	//����P16ΪBAT ADC���Ź���

	
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
	P00F = INPUT;			//P00����Ϊ����ģʽ
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
	P00F = OUTPUT;						//P00����Ϊ�������ģʽ
	P00C |= 0x80;							//P00ʹ�ܸ߹����ģʽ
/***********************************************************************************/	

	
/***********************************************************************************/	
	P00F = INPUT|PU_EN;				//P00����Ϊ����ģʽ��ʹ����������
	P00C |= 0x20;							//��������ѡ��Ϊǿ����
// 	P00C &= ~0x20;					//��������ѡ��Ϊ������
/***********************************************************************************/



/***********************************************************************************/	
	P00F = INPUT|PD_EN;				//P00����Ϊ����ģʽ��ʹ����������
	P00C |= 0x10;							//��������ѡ��Ϊǿ����
// 	P00C &= ~0x10;					//��������ѡ��Ϊ������
/***********************************************************************************/	


/***********************************************************************************/	
	P00F = P00_COM0_SETTING;		//P00����ΪCOM���Ź���
/***********************************************************************************/	
	
	while(1)
	{

	}
}
#endif
