/**
  ******************************************************************************
  * @file HT8_it.c
  * @brief This file provides all the interrupt firmware functions.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2019-07-23
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


#include "HT8_it.h"


/**
  * @brief external Interruption 0 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x04))) INT0_ISR(void)
{
	/* user define */
}

/**
  * @brief compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x08))) COMP_ISR(void)
{
	/* user define */
}

/**
  * @brief STM Interruption routine(Multi-Function Interrupt 0).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x0C))) STM_ISR(void)
{

	
	if (_stmaf == 1)
	{
		_stmaf = 0;		
		/* user define */
	}
	if (_stmpf == 1)
	{
		_stmpf = 0;
		/* user define */
	}	
}

/**
  * @brief PTM or CTM Interruption routine(Multi-Function Interrupt 1).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x10))) PTM_CTM_ISR(void)
{	
	if (_ptmaf == 1)
	{
		_ptmaf = 0;		
		/* user define */
	}
	if (_ptmpf == 1)
	{
		_ptmpf = 0;			
		/* user define */
	}	
	if (_ctmaf == 1)
	{
		_ctmaf = 0;
		/* user define */
	}
	if (_ctmpf == 1)
	{
		_ctmpf = 0;
		/* user define */
	}
}

/**
  * @brief LVD or EEPROM Interruption routine(Multi-Function Interrupt 2).
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x14))) LVD_EEPROM_ISR(void)
{
	if (_lvf == 1)
	{
		_lvf = 0;
		/* user define */
	}
	if (_def == 1)
	{
		_def = 0;
		/* user define */
	}
}

/**
  * @brief ADC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x18))) ADC_ISR(void)
{
	/* user define */
}


/**
  * @brief timebase0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x1C))) TB0_ISR(void)
{
	/* user define */
}


/**
  * @brief timebase1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x20))) TB1_ISR(void)
{
	
	/* user define */
}


/**
  * @brief external Interruption 1 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x24))) INT1_ISR(void)
{
	/* user define */
}

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/