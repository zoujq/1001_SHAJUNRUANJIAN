#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "ca51f_config.h"
#include "includes\ca51f3sfr.h"
#include "includes\ca51f3xsfr.h"
#include "includes\gpiodef_f3.h"
#include <stdio.h>

#include "Library\includes\delay.h"
#include "Library\includes\uart.h"
#include "Library\includes\system_clock.h"
#include "Library\Includes\rtc.h"	
#include "Library\Includes\pwm.h"	
#include "includes\system.h"
#include "Library\includes\adc.h"
#include "Library\includes\wdt.h"
/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"
/*********************************************************************************************************************/	
/********************************************************************************************************
˵����
------------------------------------------------------------------------------------------------------------
1.ts_configuration.h�Ǵ����������ļ������������ļ������ô���ͨ���������ȵȡ����ts_configuration.h�е�˵����
------------------------------------------------------------------------------------------------------------
2.�����Ҫʹ��UART�����ԣ�����ca51f5_config.h�д򿪺궨��UART0_EN
------------------------------------------------------------------------------------------------------------
3.�������������ݽӿ�ΪKeysFlagSN���û��ɸ���KeysFlagSN��ֵ���жϴ������Ƿ��£�������������£�KeysFlagSN
�Ķ�ӦλһֱΪ1���������ɿ�����Ӧλ��Ϊ0����TS_Key�Ǹ���KeysFlagSN��ֵ���ɵİ�����Ϣ���û��粻ʹ�ÿɺ��ԡ�
------------------------------------------------------------------------------------------------------------
4.ʹ���˴���ʡ��ģʽ�����ް���ʱ���ڶ����ʱ�������ʡ��ģʽ������ʡ��ģʽǰ��ر�TMC�жϺʹ����жϣ�ע�⣬��
�ж����ǿ����ģ����ڴ���ʡ��ģʽ�£�CPU�����STOPģʽ���ڱ��������Ѻ󣬳�����ʡ�纯����TS_EnterSleepMode����ѭ�������У�ע�⣬����ʡ��ģʽ����
������ѭ�������У����ڴ���ʡ��ģʽ�������Ҫ��Ӧ�����жϣ��û����ڽ��봥��ʡ��ģʽǰ���п��������жϣ�
�����Ҫ�˳�ʡ��ģʽ���û�ֻ��Ҫ��ʡ�纯��ѭ���ڼ��������жϣ�����ѭ�����ɡ�

����TS_SleepEn�ǿ��ƴ���ʡ��ģʽ�Ŀ��أ����ϣ��������ĳЩ�����²�����ʡ��ģʽ��ֻ���ڴ�����������TS_SleepEn = 0��


------------------------------------------------------------------------------------------------------------
5.������ҵ���(��TK_CAP�������ӵ���)��Χ��6nF~50nF,����ֵ��20nF����203��
------------------------------------------------------------------------------------------------------------
6.�������Ŵ������跶Χ��0~5K������ֵ��1Kŷķ������п��Խ����ȵ�Ÿ���Ҫ�� �˵�������3K���ϡ�
********************************************************************************************************/
unsigned char read_inner_trim(void)				
{
	unsigned char value;
	FSCMD = 0x80;	
	PTSH = 0x00;				
	PTSL = 0x24;      
	FSCMD = 0x81;						
	value = FSDAT;
	FSCMD = 0;
	return value;
}
void SystemInit(void)
{
#ifdef LVD_RST_ENABLE
	LVDCON = 0xc1;	//����LVD��λ��ѹΪ2V
#endif
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	
#endif
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);
#endif
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);
#endif

#if (RTC_CLK_SELECT == IRCL)
//���Ź�ʱ��ԴΪIRCL
	CKCON |= ILCKE;															 		//ʹ��IRCL
	WDCON  = WDTS(WDTS_IRCL) | WDRE(WDRE_reset);   	//���ÿ��Ź�ʱ��ԴΪILCKE��ģʽΪ��λģʽ
#elif (RTC_CLK_SELECT == XOSCL)	
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
	WDCON  = WDTS(WDTS_XOSCL) | WDRE(WDRE_reset);   //���ÿ��Ź�ʱ��ԴΪXOSCL��ģʽΪ��λģʽ
#endif
	WDVTHH = 0;																	 		//���Ź���λ��ֵ�߰�λ���� ��ǰֵΪ5s	
	WDVTHL = 75;															 			//���Ź���λ��ֵ�Ͱ�λ����
	WDFLG = 0xA5;	
	
	
	ADCFGH = (ADCFGH&0xC0) | VTRIM(read_inner_trim());	//����ADC�ڲ���׼У׼ֵ
}
void main(void)
{
	SystemInit();

	EA = 1;

	printf("start\n\r");
	TS_init();	
	

	while(1)
	{		
		Delay_ms(100);
		TS_Action();

		
		printf("5:%d\n\r",TS_PostData[0]&0x0FFF);
		if(KeysFlagSN != 0)
		{
			//printf("KeysFlagSN:%X\n\r",KeysFlagSN);
		}
		if(TS_Key != 0)
		{
			//printf("TS_Key:%X\n\r",TS_Key);
			switch(TS_Key)
			{
				
				//��������Ϣ
				case K1:									//K1�̰������İ�����Ϣ			
					
				break;
				case (K1|KEY_BREAK):      //K1�̰����ֲ����İ�����Ϣ
					break;
				case (K1|KEY_LONG_START):	//K1������ʼ��������Ϣ������Լ1��ʱ������
					break;
				case (K1|KEY_LONG):				//K1������������Ϣ��ÿ��Լ300ms����һ�Σ�
					break;
				case (K1|KEY_LONG_BREAK):	//K1�������ֲ�������Ϣ
					break;

			}
		}

	}

}
#endif











































