/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : FSK_LED_Example
 *
 * Project File           : FSK_LED_Example.rsp
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
 * Project Last Save Date : 28-Oct-2013 16:04:30
 *
 * Created on Date        : 28-Oct-2013 16:04:31
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
#include "pot_hld.h"
#include "photo_sensor_hld.h"
#include "freemaster.h"

/**********************  Function Prototype here *************************/

void main(void);
void ProcessCAN(void);
void ProcessADC(void);

/**********************  Global variables here *************************/
/* CAN messages to transmit */
unsigned char msgOKCAN[8] = {1,1,0,0,0,0,0,0};
unsigned char msgErrorCAN[8] = {1,0xFF,0,0,0,0,0,0};

uint16_t potValue;		/* Potentiometer ADC input value*/
uint16_t photoSensorValue;	/* Photo sensor ADC input value */

/*********************  Initialization Function(s) ************************/

void main(void)
{

/* ----------------------------------------------------------- */
/*	             System Initialization Function                  */
/* ----------------------------------------------------------- */
   sys_init_fnc();
   /* Initialize SBC */
   SBC_Init_DBG();   

   /* FreeMASTER internal variables initialization */
   FMSTR_Init();
   
/********* Enable External Interrupt *********/
   EnableExternalInterrupts();
   
   /* Turn off LEDs */  
   GPIO_SetState(68, 1);
   GPIO_SetState(69, 1);
   GPIO_SetState(70, 1);
   GPIO_SetState(71, 1);
   
   /* Initialize CAN filter */ 
   SetCanRxFilter(1, 0, 0);

   while(1)
   {
		FMSTR_Poll();
	  	ProcessCAN();
	  	ProcessADC();
   }
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
	
	if (CanRxMbFull(0) == 1)		/* Check if CAN message received */
	{
	    msgCanRX = CanRxMsg(0);	
	    if (msgCanRX.data[0] == 0)	/* If first data byte is 0, turn off LED3 and send positive response */
	    {
	    	GPIO_SetState(70, 1);
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgOKCAN, 0);
	    }
	    else if (msgCanRX.data[0] == 1)/* If first data byte is 1, turn on LED3 and send positive response */
	    {
	    	GPIO_SetState(70, 0);
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgOKCAN, 0); 
	    }
	    else			/* If first data byte is not 0 or 1, send a negative response */
	    {
	    	CanTxMsg (2, 1, 8, (uint8_t *)msgErrorCAN, 0);
	    }	    		
	}
}

/******************************************************************************
*   Function: ProcessADC
*
*   Description: Processes Potentiometer and Photo sensor ADC inputs 
*
******************************************************************************/

void ProcessADC(void)
{
	potValue = Pot_Get_Value();
	if(potValue <= 500) /* If Potentiometer input is <= 500 turn on LED1, otherwise turn off LED1 */
	{
		GPIO_SetState(68, 0);
	}
	else
	{
		GPIO_SetState(68, 1);
	}
	
	photoSensorValue = Photo_Sensor_Get_Value();
	if(photoSensorValue <= 500) /* If Photo sensor input is <= 500 turn on LED2, otherwise turn off LED2 */
	{
		GPIO_SetState(69, 0);
	}
	else
	{
		GPIO_SetState(69, 1);
	}	
} 

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

