/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : RunRun
 *
 * Project File           : RunRun.rsp
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
 * Project Last Save Date : 10-Jul-2014 21:04:28
 *
 * Created on Date        : 16-Jul-2014 14:51:21
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
#include "control.h"
#include "distanceSensor.h"
#include "rappid_utils.h"
#include "gpio_drv.h"
/************************* INTERRUPT HANDLERS ************************/


extern int sonarStatus;
/************************* INTERRUPT HANDLERS ************************/
long int aimSpeed;

void angleControlPIT (void)
{
	DisableExternalInterrupts();
    PIT.CH[0].TFLG.R = 0x00000001;
    aimSpeed=angleControl();
    EnableExternalInterrupts();
}


void sonarDelay0 (void)
{
	//DisableExternalInterrupts();
	PIT.CH[1].TFLG.R = 0x00000001;

	//EnableExternalInterrupts();
	sonarStatus =SONAR_WAIT_END;
	PIT.CH[1].TCTRL.B.TIE  = 0x0; 
	
	
}

void speedControlPIT (void)
{
	//DisableExternalInterrupts();
    PIT.CH[2].TFLG.R = 0x00000001;
    speedControl(aimSpeed);
   // EnableExternalInterrupts();
}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

