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
 * file                   : mpu_init.c
 *
 * Target Compiler        : Diab
 *
 * Target Part            : MPC5606B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 16-Jan-2015 13:26:25
 *
 * Created on Date        : 16-Jan-2015 13:27:40
 *
 * Brief Description      : This File Contains Entry configuration for MPU
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains function containing entries
 *                         which defines the regions and master access to the
 *                         regions in supervisor and user mode. It also handles
 *                         enabling of MPU.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "mpu_init.h"




/*********************  Initialization Function(s) ************************/

void mpu_init_fnc(void)
{

    MPU.CESR.B.VLD = 0;
        /* MPU Entries : Invalid*/

}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

