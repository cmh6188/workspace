/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : JJH5606B
 *
 * Project File           : JJH5606B.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.2.1.5
 *
 * file                   : intc_init.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 16-Jan-2015 13:30:51
 *
 * Created on Date        : 16-Jan-2015 13:31:11
 *
 * Brief Description      : This file contains the function prototype for intc source file.
 *
 *
 *######################################################################
*/

#ifndef  _INTC_INIT_H
#define  _INTC_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"



/**********************  Function Prototype here *************************/

extern void intc_init_fnc (void);
extern void en_int_fnc (vuint32_t priority);


#endif  /*_INTC_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

