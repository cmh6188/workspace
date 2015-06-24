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
 * file                   : sys_init.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 16-Jul-2014 15:31:47
 *
 * Created on Date        : 16-Jul-2014 15:33:24
 *
 * Brief Description      : This file contains system initialization code
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file contains function which calls respective
 *                         peripheral initialization functions
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "sys_init.h"


/*********************  Initialization Function(s) ************************/

void sys_init_fnc (void)
{

/* ----------------------------------------------------------- */
/*	               System Initialization Functions              */
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/*                  Reset Determination Goes Here             */
/* ----------------------------------------------------------- */

/* ----------------------------------------------------------- */
/*	        Initialize the Interrupt Controller (INTC)             */
/* ----------------------------------------------------------- */
    intc_init_fnc();
    IVPRInitialize();

/* ----------------------------------------------------------- */
/*	        Initialize the Software Watchdog (SWT)             */
/* ----------------------------------------------------------- */
    swt_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the System Clock, Mode Entry (ME) & CMU             */
/* ----------------------------------------------------------- */
    sysclk_module_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Real Time Clock (RTC)             */
/* ----------------------------------------------------------- */
    rtc_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the System Timer Module (STM)             */
/* ----------------------------------------------------------- */
    stm_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Periodic Interrupt Timer (PIT)             */
/* ----------------------------------------------------------- */
    pit_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Analog to Digital Converter (ADC)             */
/* ----------------------------------------------------------- */
    adc_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Enhanced Modular I/O (eMIOS)             */
/* ----------------------------------------------------------- */
    emios_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the LINFlex             */
/* ----------------------------------------------------------- */
    linflex_init_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the Mode Entry Post Configuration             */
/* ----------------------------------------------------------- */
    mode_entry_post_config_fnc();

/* ----------------------------------------------------------- */
/*	        Initialize the System Integration Unit (SIU)             */
/* ----------------------------------------------------------- */
    siu_init_fnc();


}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

