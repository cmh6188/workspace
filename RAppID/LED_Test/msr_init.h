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
 * file                   : msr_init.h
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
 * Brief Description      : This File contain function declaration for SPR code file
 *
 *
 *######################################################################
*/

#ifndef  _MSR_INIT_H
#define  _MSR_INIT_H
/*********************  Initialization Function(s) ************************/

asm void msr_init_fnc (void)
{


/* ----------------------------------------------------------- */

/*   Machine State Setup                     */

/* ----------------------------------------------------------- */


/* ----------------------------------------------------------- */
/*	                  MSR Setup                                */
/* ----------------------------------------------------------- */
   e_lis r12, 0x0000
         /* Load upper 16 bits of register value    */
         /* Execution of SPE APU vector instructions : Disabled    */
         /* Critical Interrupt : Disabled    */
         /* Wait State : Disabled    */
   e_or2i r12,0x0000
         /* Load lower 16 bits of register value    */
         /* External Interrupt : Disabled    */
         /* Problem State : Disabled    */
         /* FP available : Disabled    */
         /* Machine Check : Disabled    */
         /* Debug Interrupt : Disabled    */
         /* Instruction Address Space : Disabled    */
         /* Data Address Space : Disabled    */
         /* Recoverable Interrupt : Disabled    */
   mtmsr r12
         /* Move data to MSR register    */

/* ----------------------------------------------------------- */
/*	                  HID0 Setup                               */
/* ----------------------------------------------------------- */
   e_lis r12, 0x0000
         /* Load upper 16 bits of register value    */
   e_or2i r12,0x0000
         /* Load lower 16 bits of register value    */
   mtspr 1008,r12
         /* Move data to HID0 register    */
         /* Debug Interrupt Clears (DCLREE) : Disabled    */
         /* Debug Interrupt Clears (DCLRCE) : Disabled    */
         /* Critical Interrupt Clears : Disabled    */
         /* Machine Check Interrupt Clears : Disabled    */
         /* Debug APU : Disabled    */
         /* Interrupt Inputs Clear Reservation : Disabled    */
         /* Machine Check Exception : Disabled          */



}

#endif  /*_MSR_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

