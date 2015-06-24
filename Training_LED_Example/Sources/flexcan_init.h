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
 * file                   : flexcan_init.h
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 29-Oct-2013 14:07:38
 *
 * Created on Date        : 29-Oct-2013 14:07:39
 *
 * Brief Description      : This File contains functions declaration of FlexCAN
 *                          code file
 *
 *
 *######################################################################
*/

#ifndef  _FLEXCAN_INIT_H
#define  _FLEXCAN_INIT_H
/********************  Dependent Include files here **********************/

#include "jdp.h"


/*********************  Receive FIFO Macro here ****************************/

/**********************  Function Prototype here *************************/

uint8_t flexcan_init_fnc(void);
uint8_t flexcan_0_init_fnc(void);
uint8_t flexcan_1_init_fnc(void);
uint8_t flexcan_2_init_fnc(void);
uint8_t flexcan_3_init_fnc(void);
uint8_t flexcan_4_init_fnc(void);
uint8_t flexcan_5_init_fnc(void);


#endif  /*_FLEXCAN_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

