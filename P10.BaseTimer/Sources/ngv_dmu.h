/*
 * ngv_dmu.h
 *
 *  Created on: Dec 29, 2014
 *      Author: ����̷����б� ����
 */

#ifndef NGV_DMU_H_
#define NGV_DMU_H_

#include "typedefs.h"

#define NGV_DMU_TRUE 	1
#define NGV_DMU_FALSE 	0

#define NGV_DMU_OK 		0
#define NGV_DMU_NOK 	1

#define SYSCLK_IRC_16MHZ	0
#define SYSCLK_PLL_32MHZ	1
#define SYSCLK_PLL_64MHZ	2

//- NGV_DMU_SYSCLK�� �� �� �� �� �ϳ� ����
#define NGV_DMU_SYSCLK		SYSCLK_PLL_32MHZ

#endif /* NGV_DMU_H_ */
