#ifndef _WDT_C_
#define _WDT_C_
/*********************************************************************************************************************/
#include "ca51f_config.h"
#include "includes\ca51f3sfr.h"
#include "includes\ca51f3xsfr.h"
#include "includes\gpiodef_f3.h"

#include "includes\system.h"
#include "Library\includes\wdt.h"
#include <intrins.h>
/*********************************************************************************************************************/
/*****************************************************************************
��������WDT_init
������������ʼ�����Ź�
���������wdts		���Ź�ʱ��Դ����
					wdre		���Ź�ģʽ����
					wdtch		���Ź�ʱ������
����ֵ�� ��
******************************************************************************/
void WDT_init(WDTS_TypeDef wdts,WDRE_TypeDef wdre,unsigned int wdtvh)
{
	WDCON = WDTS(wdts) | WDRE(wdre);
	WDVTHH = (unsigned char)(wdtvh>>8);
	WDVTHL = (unsigned char)(wdtvh);	
}

/*****************************************************************************
��������WDT_FeedDog
����������ˢ�¿��Ź�
�����������
����ֵ�� ��
******************************************************************************/
void WDT_FeedDog(void)
{
	WDFLG = 0xA5;
}
/*********************************************************************************************************************/
#endif