#ifndef _PWM_C_
#define _PWM_C_

/*********************************************************************************************************************/
#include "ca51f_config.h"

#include "includes\ca51f3sfr.h"
#include "includes\ca51f3xsfr.h"
#include "includes\gpiodef_f3.h"
#include "includes\system.h"
#include "Library\includes\pwm.h"
#include <intrins.h>
/*********************************************************************************************************************/
/******************************************************************************
��������PWM_init
����������PWM���ܳ�ʼ��
�������: pwm_ch		PWMͨ��ѡ��
					AlignMod	����ģʽ����
					cks				PWMʱ��Դ���ã�ֻ��PWM0,2,4,6���д������ã�
					toggle		PWM�Ƿ����������
					Prescal		PWMʱ�ӷ�Ƶ����
					Comp			PWM����������ã�ֻ��PWM1,3,5,7���д������ã�
����ֵ�� ��					

******************************************************************************/
void PWM_init(PWM_Channel_TypeDef pwm_ch,
							PWM_AlignMod_TypeDef AlignMod,
							PWM_CKS_TypeDef cks,
							PWM_Toggle_TypeDef toggle,
							unsigned char Prescal,
							PWM_Complementary_TypeDef Comp)
{
	INDEX = pwm_ch;
	if(pwm_ch & 0x01)	//PWM1,PWM3,PWM5,PWM7
	{
		PWMCON = (PWMCON&0xF0) | MS(AlignMod) | MOD(Comp);
		PWMCFG = TOG(toggle) | Prescal;		
	}
	else							//PWM0,PWM2,PWM4,PWM6
	{
		PWMCON = (PWMCON&0xF0) | MS(AlignMod) | CKS(cks);
		PWMCFG = TOG(toggle) | Prescal;		
	}
}

/******************************************************************************
��������	PWM_CfgDivDuty
��������������PWM���ں�ռ�ձ�
�������: pwm_ch		PWMͨ��ѡ��
					DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM_CfgDivDuty(PWM_Channel_TypeDef pwm_ch,unsigned int DIV,unsigned int DUT)
{
	INDEX = pwm_ch;
	PWMDIVH	= (unsigned char)(DIV>>8);
	PWMDIVL	= (unsigned char)(DIV);
	PWMDUTH	= (unsigned char)(DUT>>8);
	PWMDUTL	= (unsigned char)(DUT);	
}

/******************************************************************************
��������	PWM_Update
����������PWM�Ĵ�������
�������: PWMCH_Bits	
����ֵ��  ��					
******************************************************************************/
void PWM_Update(unsigned char PWMCH_Bits)
{
	PWMUPD = PWMCH_Bits;
}

/******************************************************************************
��������	WaitPWMUpdateComplete
�����������ȴ�PWM����ֵ���µ�ʵ�ʼĴ���
�������: ��	
����ֵ��  ��					
******************************************************************************/
void WaitPWMUpdateComplete(void)
{
	while(PWMUPD);
}

/******************************************************************************
��������	PWM_EnContrl
����������PWMʹ��
�������: PWMEn_Bits	��ÿһλ��ӦPWM��һ��ͨ��
����ֵ��  ��					
******************************************************************************/
void PWM_EnContrl(unsigned char PWMEn_Bits)
{
	PWMEN = PWMEn_Bits;
}


/******************************************************************************
��������	PWM_InterruptCfg
��������������PWM���ں�ռ�ձ�
�������: pwm_ch		PWMͨ��ѡ��
					tie				PWM�����ж�����
					zie				PWM����ж�����
					pie				PWM�������ж�
����ֵ��  ��					
******************************************************************************/
void PWM_InterruptCfg(PWM_Channel_TypeDef pwm_ch,
											PWM_TIE_TypeDef tie,
											PWM_ZIE_TypeDef zie,
											PWM_PIE_TypeDef pie,
											PWM_NIE_TypeDef nie,
											unsigned char pwmcmax
											)
{
	INDEX = pwm_ch;
	PWMCON = (PWMCON&0x0F) | TIE(tie) | ZIE(zie) | PIE(pie) | NIE(nie);
	PWMCMAX = pwmcmax;
}

#endif