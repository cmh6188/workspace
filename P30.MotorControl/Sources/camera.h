/*
 * camera.c
 *
 *  Created on: Feb 23, 2015
 *      Author: 연세대학교 기계공학과 정재학
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "jdp.h"

#define CAM_CH0 		0x1
#define CAM_CH1 		0x2
#define CAM_CH_ALL	0x4//0xf
#define CAM_CH_NUM	2

uint8_t CAM_CLK	= 40; //micro sec //(0.25)	// MHz
uint32_t CAM_SIG = CAM_CLK*128 + 10;	 //micro sec 
uint8_t CAM_READ[128]	= {0,};


//void CAM_PIT3_ISR(void);
//void CAM_EMIOS1_F10_F11_ISR(void);
//void CAM_Enable(uint16_t channels);
void CAM_Init(uint16_t channels);
void CAM_Clock_ISR();
void CAM_Signal_ISR();
void CAM_Get();

uint32_t CAM_Get(uint16_t channels);


#endif /* CAMERA_H_ */
