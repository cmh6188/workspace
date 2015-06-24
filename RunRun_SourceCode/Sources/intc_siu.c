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
 * file                   : intc_siu.c
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
 * Brief Description      : This  file contains  the interrupt service routine  for the SIU
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when SIU function is defined
 *                         in INTC peripheral.This file contains the Interrupt
 *                         handlers routines for SIU. In Interrupt handlers
 *                         routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_siu.h"
#include "distanceSensor.h"

/************************* INTERRUPT HANDLERS ************************/

void sonarInt0 (void)
{
    SIU.ISR.R = 0x000000FF;
    sonarSensing();
}



 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

