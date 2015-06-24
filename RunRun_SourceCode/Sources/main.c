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
 * file                   : main.c
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
#include "clcd.h"

/**********************  Function Prototype here *************************/

void main(void);


/*********************  Initialization Function(s) ************************/

void main(void)
{
/* ----------------------------------------------------------- */
/*	             System Initialization Function                  */
/* ----------------------------------------------------------- */
   sys_init_fnc();
   lcdInitPrint();
/********* Enable External Interrupt *********/
   EnableExternalInterrupts();
   while(1)
   {
	   sensingLCD();
	  
   }

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

