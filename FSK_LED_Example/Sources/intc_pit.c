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
 * file                   : intc_pit.c
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
 * Brief Description      : This  file contains  the interrupt service routine  for the Periodic Interrupt Timer
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when PIT(Periodic Interrupt
 *                         Timer) function is defined in INTC peripheral.This
 *                         file contains the Interrupt handlers routines for PIT.
 *                         In Interrupt handlers routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_pit.h"
#include "gpio_drv.h"

#define DC_STEP		6400
#define MIN_DC		6400
#define MAX_DC		64000


/************************* INTERRUPT HANDLERS ************************/

void PIT_Ch0_ISR (void)
{
	uint32_t tmp;
	
    PIT.CH[0].TFLG.R = 0x00000001;
    
    /* If switch S3 is pressed and S4 is not pressed */
    if (GPIO_GetState(66) && !GPIO_GetState(67))
    {
        /* Increase PWM  Duty Cycle */	
        tmp = EMIOS_0.CH[23].CADR.R;
        if(tmp < MAX_DC)
        {
        	tmp = tmp + DC_STEP;
        }
        EMIOS_0.CH[23].CADR.R = tmp;    	
    }
    /* If switch S4 is pressed and S3 is not pressed */
    else if(GPIO_GetState(67) && !GPIO_GetState(66))
    {
        /* Decrease PWM Duty Cycle */	
        tmp = EMIOS_0.CH[23].CADR.R;
        if(tmp > MIN_DC)
        {
        	tmp = tmp - DC_STEP;
        }
        EMIOS_0.CH[23].CADR.R = tmp;     	
    }    

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

