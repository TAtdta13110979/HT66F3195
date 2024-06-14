/**
  ******************************************************************************
  * @file HT8_UART.c
  * @brief This file provides all the UART firmware functions.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2019-08-02
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

#include "HT8_UART.h"

vu16 g_nUART_ISR_Value[2];	//uart receive buff
vu8	 g_nUART_err_Flag;	//uart error flag

/**
  * @brief UART initialization function.
  * @param[in] uart baud rate.
  * It can be 0x00~0xff.
  * @retval None
  */
/************************************************************
PS:If Fsys = 16MHZ, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
   -------------------------------------------------------------------
   | High speed Mode  | 0xcf | 0x67 |  0x33 |  0x19 |  0x10 | 0x08 |
   | error rate       | 0.16%| 0.16%| 0.16% | 0.16% |  2.1% |-3.5% |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x33 | 0x19 | 0x0c  |  ---- |  ---- |    
   | error rate       | 0.16%| 0.16%| 0.16% |  ---- |  ---- |
   -------------------------------------------------------------------  

PS:If Fsys = 12MHZ, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 |115200|
   -------------------------------------------------------------------
   | High speed Mode  | 0x9b | 0x4d |  0x26 |  0x13 |  0x0c | ---- |
   | error rate       | 0.16%| 0.16%| 0.16% | -2.3% | 0.16% | ---- |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x26 | 0x13 | 0x09  |  0x04 |  ---- | ---- |  
   | error rate       | 0.16%|-2.3% |-2.3%  | -2.3% |  ---- | ---- |
   -------------------------------------------------------------------  

PS:If Fsys = 8MHZ, BaudRate input values reference table.
   -------------------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 | 
   -------------------------------------------------------------------
   | High speed Mode  | 0x67 | 0x33 |  0x19 |  0x0c |  0x08 | 
   | error rate       | 0.16%| 0.16%| 0.16% | 0.16% | -3.5% |
   -------------------------------------------------------------------
   | Low speed Mode   | 0x19 | 0x0c |  ---- |  ---- |  ---- |    
   | error rate       | 0.16%| 0.16%| 
   -------------------------------------------------------------------  
**********************************************************************/
void UART_Init(u8 BaudRate)
{		
	#ifdef	EVENPR_MODE
		_pren = 1; _prt = 0; 	/*Even parity Mode config*/
	
	#elif	ODDPR_MODE
		_pren = 1; _prt = 1;	/*Odd parity Mode config*/
		
	#else
		_pren = 0;	
	#endif
	
	/**************************************/	
	
	#ifdef	NINE_BIT_MODE
		_bno = 1;
	#else	/* 9 Number of data bits*/
		_bno = 0;
	#endif	/* 8 Number of data bits*/

	/**************************************/
	
	#ifdef	HIGH_MODE
		_brgh = 1;/*High speed Mode*/	
	#else
		_brgh = 0;/*Low speed Mode*/
	#endif	

	/**************************************/

	#ifdef	TWO_STOPS_MODE
		_stops = 1;
	#else	/* 2 Number of stop bits*/
		_stops = 0;
	#endif	/* 1 Number of stop bits*/

	/**************************************/

	_brg = BaudRate;	//Baud Rate values config
}

/**********************************************************************/

/************************* UART transmit data **************************/



/**
  * @brief UART transmit function.
  * @par:transmit data.
  * @retval
  * None
  */
void UART_Transmit(u16 data)
{
	/* Initialization */
	_tx8 = 0;		


	/* waitting UART transmitter free */
	while(!_txif)
	{
		_nop();
	}				
	/* end */
	
	/**************************************/
	
	/* Write data to UART transmitter */
	#ifdef	NINE_BIT_MODE
		#if defined(EVENPR_MODE) || defined(ODDPR_MODE)
			_txr_rxr = data;	//MSB is parity bit
		#else
			if( data > 255)
			{
				_tx8 = 1;		//MSB is data bit
			}
			_txr_rxr = data;
		#endif	
	#else
		_txr_rxr = data;
	#endif
	/* Write end */

	/**************************************/

	/* Waitting UART transmit data finished*/
	while(!_tidle)		
	{
		_nop();
	}	
	/* transmit finished */
}


/**
  * @brief UART receive Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x2C))) UART_ISR(void)
{
	g_nUART_ISR_Value[0] = 0;//clear first receive data buff
	g_nUART_ISR_Value[1] = 0;//clear second receive data buff
	g_nUART_err_Flag = 0;	//clear error flag
	
/**************************************/

	/* parity error flag*/
	#ifdef	EVENPR_MODE	
		if (_perr)
		{
			/* Even parity error,user can set error flag in here */
			g_nUART_err_Flag |= 0x80;
		}
	#endif	

	#ifdef	ODDPR_MODE
		if (_perr)
		{
			/* Odd parity error,user can set error flag in here */
			g_nUART_err_Flag |= 0x80;
		}
	#endif
	/* end */
			
/**************************************/	
			
	/* noise error flag*/	
	#ifdef	NF_MODE
		if (_nf)
		{
			/* Noise error,user can set error flag in here */
			g_nUART_err_Flag |= 0x40;
		}
	#endif
	/* end */
		
/**************************************/
		
	/* framing error flag*/	
	#ifdef	FERR_MODE
		if (_ferr)
		{
			/* Framing error,user can set error flag in here */
			g_nUART_err_Flag |= 0x20;
		}
	#endif
	/* end */
			
/**************************************/
			
	/* Overrun error flag */
	#ifdef	OERR_MODE
		if (_oerr)
		{
			/* Overrun error,user can set error flag in here */
			g_nUART_err_Flag |= 0x10;
		}
	#endif
	/* end */

	#if defined(EVENPR_MODE) || defined(ODDPR_MODE) || defined(NF_MODE) || defined(FERR_MODE) || defined(OERR_MODE)
		if (g_nUART_err_Flag & 0xf0)
		{
			_acc = _usr;
			_acc = _txr_rxr;	//read USR and TXR_RXT register to clear error flag
			g_nUART_ISR_Value[0] = 0;//clear first receive data buff
			g_nUART_ISR_Value[1] = 0;//clear second receive data buff
			return;		
		}
	#endif
	
/**************************************/
	
	/* receive data success */
	if(_rxif)
	{
		#ifdef	NINE_BIT_MODE
			#if defined(EVENPR_MODE) || defined(ODDPR_MODE)
				g_nUART_ISR_Value[0] = _txr_rxr;	//first Byte,MSB is parity bit
				
			#else
				if(_rx8==1)
				{
					_acc = _usr;
					g_nUART_ISR_Value[0] = _txr_rxr + 256;	//first Byte,MSB=1 is data bit
				}
				else
				{
					_acc = _usr;
					g_nUART_ISR_Value[0] = _txr_rxr;	//first Byte,MSB=0 is data bit
				}
			#endif	
			if(_rxif)
			{
				#if defined(EVENPR_MODE) || defined(ODDPR_MODE)
					g_nUART_ISR_Value[1] = _txr_rxr;	//second Byte,MSB is parity bit
					
				#else
					if(_rx8==1)
					{
						_acc = _usr;
						g_nUART_ISR_Value[1] = _txr_rxr + 256;	//second Byte,MSB=1 is data bit				
					}
					else
					{
						_acc = _usr;
						g_nUART_ISR_Value[1] = _txr_rxr;//second Byte,MSB=0 is data bit
					}
				#endif
			}
			
		#else
			_acc = _usr;
			g_nUART_ISR_Value[0] = _txr_rxr;	//first Byte
			if (_rxif)
			{
				_acc = _usr;
				g_nUART_ISR_Value[1] = _txr_rxr;//second Byte
			}
		#endif
		/* end */	
	}
}

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/