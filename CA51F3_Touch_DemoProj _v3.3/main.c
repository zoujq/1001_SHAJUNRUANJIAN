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
说明：
------------------------------------------------------------------------------------------------------------
1.ts_configuration.h是触摸的配置文件，可在配置文件中设置触摸通道、灵敏度等。详见ts_configuration.h中的说明。
------------------------------------------------------------------------------------------------------------
2.如果需要使用UART来调试，可在ca51f5_config.h中打开宏定义UART0_EN
------------------------------------------------------------------------------------------------------------
3.触摸库对外的数据接口为KeysFlagSN，用户可根据KeysFlagSN的值来判断触摸键是否按下（如果触摸键按下，KeysFlagSN
的对应位一直为1，触摸键松开，对应位变为0），TS_Key是根据KeysFlagSN的值生成的按键消息，用户如不使用可忽略。
------------------------------------------------------------------------------------------------------------
4.使能了触摸省电模式后，在无按键时，在定义的时间后会进入省电模式，进入省电模式前会关闭TMC中断和触摸中断（注意，总
中断仍是开启的），在触摸省电模式下，CPU会进入STOP模式，在被触摸唤醒后，程序在省电函数（TS_EnterSleepMode）的循环内运行（注意，触摸省电模式程序不
会在主循环内运行），在触摸省电模式下如果还要响应其他中断，用户需在进入触摸省电模式前自行开启其他中断，
如果需要退出省电模式，用户只需要在省电函数循环内加入条件判断，跳出循环即可。

变量TS_SleepEn是控制触摸省电模式的开关，如果希望程序在某些条件下不进入省电模式，只需在此条件下设置TS_SleepEn = 0；


------------------------------------------------------------------------------------------------------------
5.触摸外挂电容(即TK_CAP引脚连接电容)范围：6nF~50nF,建议值：20nF（即203）
------------------------------------------------------------------------------------------------------------
6.触摸引脚串联电阻范围：0~5K，建议值：1K欧姆，如果有抗对讲机等电磁干扰要求， 此电阻至少3K以上。
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
	LVDCON = 0xc1;	//设置LVD复位电压为2V
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
//看门狗时钟源为IRCL
	CKCON |= ILCKE;															 		//使能IRCL
	WDCON  = WDTS(WDTS_IRCL) | WDRE(WDRE_reset);   	//设置看门狗时钟源为ILCKE，模式为复位模式
#elif (RTC_CLK_SELECT == XOSCL)	
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
	WDCON  = WDTS(WDTS_XOSCL) | WDRE(WDRE_reset);   //设置看门狗时钟源为XOSCL，模式为复位模式
#endif
	WDVTHH = 0;																	 		//看门狗复位阈值高八位设置 当前值为5s	
	WDVTHL = 75;															 			//看门狗复位阈值低八位设置
	WDFLG = 0xA5;	
	
	
	ADCFGH = (ADCFGH&0xC0) | VTRIM(read_inner_trim());	//加载ADC内部基准校准值
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
				
				//单按键消息
				case K1:									//K1短按产生的按键消息			
					
				break;
				case (K1|KEY_BREAK):      //K1短按松手产生的按键消息
					break;
				case (K1|KEY_LONG_START):	//K1长按开始产生的消息（长按约1秒时产生）
					break;
				case (K1|KEY_LONG):				//K1长按产生的消息（每隔约300ms产生一次）
					break;
				case (K1|KEY_LONG_BREAK):	//K1长按松手产生的消息
					break;

			}
		}

	}

}
#endif











































