/**
  ******************************************************************************
  * @file CodeConfig.c
  * @ brief CodeConfig setting file.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2020-10-24
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/

#include "CodeConfig.h"

void System_Init()
{	
	SysClock_Init();
	GPIO_Init();
	ADC_Init();
	UART_Init(12);
//end System Init
}

void System_Setting()
{
//Begin System Setting
	EMI_ENABLE();

	ADC_SelectChannel(ADC_CH0);
	ADC_ENABLE();
	UART_CLEAR_ISR_FLAG();
	UART_ISR_ENABLE();
	UART_RIE_ENABLE();
	UART_ENABLE();
	UART_TX_ENABLE();
	UART_RX_ENABLE();
//end System Setting
}
