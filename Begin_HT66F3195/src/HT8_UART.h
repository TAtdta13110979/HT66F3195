/**
  ******************************************************************************
  * @file HT8_UART.h
  * @brief This file  contains the headers of the UART.
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

#ifndef _HT8_UART_H_
#define	_HT8_UART_H_


#include "HT8_MCU_IP_SEL.h"


/****************** UART Enable switch ********************************
* PS: If UART_DISABLE , TX and RX switch are Null.
**********************************************************************/

#define	UART_ENABLE()			{_uarten = 1;}				//UART function enable
#define	UART_DISABLE()			{_uarten = 0;}				//UART function disable

#define	UART_TX_ENABLE()		{_txen = 1;}				//TX function enable
#define	UART_TX_DISABLE()		{_txen = 0;}				//TX function disable

#define	UART_RX_ENABLE()		{_rxen = 1;}				//RX function enable
#define	UART_RX_DISABLE()		{_rxen = 0;}				//RX function disable

#define	UART_ISR_ENABLE()		{_uarte = 1;}				//UART interrupt enable
#define	UART_ISR_DISABLE()		{_uarte = 0;}				//UART interrupt disable
#define	UART_CLEAR_ISR_FLAG()	{_uartf = 0;}				//clear UART interrupt flag
#define	UART_SET_ISR_FLAG()		{_uartf = 1;}				//set UART interrupt flag

#define UART_RIE_ENABLE()		{_rie = 1;}                 //UART receiver interrupt enable
#define UART_RIE_DISABLE()		{_rie = 0;}                 //UART receiver interrupt disable

#define UART_TIIE_ENABLE()		{_tiie = 1;}                 //UART transmitter idle interrupt enable
#define UART_TIIE_DISABLE()		{_tiie = 0;}                 //UART transmitter idle interrupt disable

#define UART_TEIE_ENABLE()		{_teie = 1;}                 //UART transmitter empty interrupt enable
#define UART_TEIE_DISABLE()		{_teie = 0;}                 //UART transmitter empty interrupt disable

#define UART_Addr_Det_ENABLE()	{_adden = 1;}                //UART Address detect function enable
#define UART_Addr_Det_DISABLE()	{_adden = 0;}                //UART Address detect function disable

#define UART_RX_Wake_ENABLE()	{_wake = 1;}                 //UART RX pin falling edge wake-up function enable
#define UART_RX_Wake_DISABLE()	{_wake = 0;}                 //UART RX pin falling edge wake-up function disable

#define UART_TXBRK_ENABLE()		{_txbrk = 1;}                //UART transmit break character function enable
#define UART_TXBRK_DISABLE()	{_txbrk = 0;}                //UART transmit break character function disable

/****************function and mode select******************************/
/**********************************************************************/

/************* speed mode select**********************
* Single selection. 
*/
//	#define		HIGH_MODE			1			//High speed Mode
	#define		LOW_MODE			1			//Low speed Mode,default
/** end of speed mode select **/


/************* detect mode select*********************
* Custom options.
* PS: But EVENPR_MODE and ODDPR_MODE are only one.
*/
	
//	#define		EVENPR_MODE			1			//Even parity Mode
//	#define		ODDPR_MODE			1			//Odd  parity Mode
//	#define		NF_MODE				1			//Noise Mode
//	#define		FERR_MODE			1			//Framing error Mode
//	#define		OERR_MODE			1			//Overrun error Mode

/** end of detect mode select **/


/************* Function select************************
* Custom options. 
*/

//	#define		TWO_STOPS_MODE		1			//Number of stop bits select ( 1 or 2 )
//	#define		NINE_BIT_MODE		1			//Number of data bits select ( 8 or 9 )	

/** end of Function select **/




/************************************************************
PS:If Fsys = 8MHZ, BaudRate input values reference table.
   ----------------------------------------------------------
   | Baud Rate values | 4800 | 9600 | 19200 | 38400 | 57600 | 
   ----------------------------------------------------------
   | High speed Mode  | 0x67 | 0x33 |  0x19 |  0x0c |  0x08 | 
   ----------------------------------------------------------
   | Low speed Mode   | 0x19 | 0x0c |  ---- |  ---- |  ---- |   
   ----------------------------------------------------------   
*************************************************************/	
void	UART_Init(u8 BaudRate);				//UART initialization function, input Baud Rate values
void	UART_Transmit(u16 data);			//UART transmit function

extern vu16  g_nUART_ISR_Value[2];
extern vu8	 g_nUART_err_Flag;	//uart error flag

#endif

/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/
