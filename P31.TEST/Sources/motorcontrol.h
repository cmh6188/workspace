/*
 * motorcontrol.h
 *
 *  Created on: Jan 11, 2015
 *      Author: ����̷����б� ����
 *        Note: 2015�� NGV ���л� �� ���� ����, ����, ������ ���մϴ�.        
 */

#include "jdp.h"


#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

#define MCTL_SWHEEL_RAW_MAX	(9200)	// 2.3/0.00025
#define MCTL_SWHEEL_RAW_MID	(6000)	// 1.5/0.00025
#define MCTL_SWHEEL_RAW_MIN	(2800)     // 0.7/0.00025

#define MCTL_SWHEEL_MAX		(100)
#define MCTL_SWHEEL_MIN		(-100)

#define MCTL_ENGINE_MAX	(2047)
#define MCTL_ENGINE_MIN	(-2047)

void MCTL_Init(void);
void MCTL_RotateSwheel(int16_t angle);
void MCTL_RotateEngine(int16_t speed);
void MCTL_BrakeEngle(void);

#endif /* MOTORCONTROL_H_ */
