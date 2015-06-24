/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : Training_LED_Example
 *
 * Project File           : Training_LED_Example.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.2.1.5
 *
 * file                   : main.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 25-Oct-2013 10:24:04
 *
 * Created on Date        : 25-Oct-2013 10:24:06
 *
 * Brief Description      : This file contains main() function call.
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file contains main() routine which calls system
 *                         initialization routine and interrupt enable routine if defined.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"
#include "CANapi.h"
#include "sbc_hld.h"
#include "gpio_drv.h"
#include "UART_drv_api.h"
#include "pot_hld.h"

/**********************  Function Prototype here *************************/

void main(void);
void PrintMenu(void);
void ProcessGPIO(void);
void ProcessUART(void);
void ProcessCAN(void);
void ProcessADC(void);

/**********************  Global variables here *************************/
/* CAN messages to transmit */
unsigned char msgOKCAN[8] = {1,1,0,0,0,0,0,0};
unsigned char msgErrorCAN[8] = {1,0xFF,0,0,0,0,0,0};
/* UART menu string */
unsigned char menuString[] = "Press 1 to turn on and 0 to turn off LED2";
unsigned char newLine[2] = {0x0A, 0x0D};
uint8_t switchState;
uint16_t potValue;

/*********************  Initialization Function(s) ************************/

void main(void)
{

/* ----------------------------------------------------------- */
/*	             System Initialization Function                  */
/* ----------------------------------------------------------- */
   sys_init_fnc();
   SBC_Init_DBG(); 
/********* Enable External Interrupt *********/
   EnableExternalInterrupts();

	GPIO_SetState(68, 1);
	GPIO_SetState(69, 1);
	GPIO_SetState(70, 1);
	GPIO_SetState(71, 1);
	SetCanRxFilter(1, 0, 0);
	UartBufInit();
	PrintMenu();
   while(1)
   {
		ProcessGPIO();
		ProcessUART();
		ProcessCAN();
		ProcessADC();
   }
}

/******************************************************************************
*   Function: ProcessUART
*
*   Description: Process serial messages 
*
******************************************************************************/
void ProcessUART(void)
{
	unsigned char data;	
	UartRxFillBuf();		/* Check if serial message received */
	if(UartRxBufEmpty() != 1)
	{
		data = UartRxDataByte();	/* If received data byte is 1, turn on LED2 */
		if (data == '1')
		{			
			GPIO_SetState(69, 0);
		}
		else if (data == '0')	/* If received data byte is 0, turn on LED2 */
		{			
			GPIO_SetState(69, 1);
		}   			
		PrintMenu();   			
	}	
}

/******************************************************************************
*   Function: PrintMenu
*
*   Description: Sends menu string over UART
*
******************************************************************************/
void PrintMenu(void)
{
	UartTxMsg((unsigned char *)newLine, 2);
	UartTxMsg((unsigned char *)menuString, 40);
	UartTxMsg((unsigned char *)newLine, 2);
}	

/******************************************************************************
*   Function: ProcessCAN
*
*   Description: Process CAN messages
*
******************************************************************************/
void ProcessCAN(void)
{
	can_msg_struct msgCanRX;
	
	if (CanRxMbFull(0) == 1)	/* Check if CAN message received */
	{
		msgCanRX = CanRxMsg(0);	
	    if (msgCanRX.data[0] == 0)	/* If received data byte is 0, turn off LED3 and send positive response */
	    {
	    	GPIO_SetState(70, 1);
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgOKCAN, 0);
	    }
	    else if (msgCanRX.data[0] == 1)	/* If received data byte is 1, turn on LED3 and send positive response */
	    {
	    	GPIO_SetState(70, 0);
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgOKCAN, 0); 
	    }
	    else		/* If received data byte is not 0 or 1, send a negative response */
	    {
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgErrorCAN, 0);
	    }	    		
	}
}

/******************************************************************************
*   Function: ProcessGPIO
*
*   Description: Processes switch input 
*
******************************************************************************/
void ProcessGPIO(void)
{
	switchState = GPIO_GetState(64); /* Check switch S1 state */
	if (switchState)	/* If Switch S1 is pressed, turn on LED1, other wise turn off LED1*/
	{
		GPIO_SetState(68, 0);		
	}
	else
	{
		GPIO_SetState(68, 1);   			
	}	
}

/******************************************************************************
*   Function: ProcessADC
*
*   Description: Processes ADC input 
*
******************************************************************************/
void ProcessADC(void)
{
	potValue = Pot_Get_Value();
	if(potValue <= 500) 	/* If Potentiometer input is <= 500 turn on LED4, other wise turn off LED4 */
	{
		GPIO_SetState(71, 0);
	}
	else
	{
		GPIO_SetState(71, 1);
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

