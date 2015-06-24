/*
 * distanceSensor.h
 *
 *  Created on: Jun 18, 2014
 *      Author: RuleTheComputer
 */

#ifndef	___DISTANCESENSOR__H__
#define ___DISTANCESENSOR__H__

#define SONAR0_CONTROL_CH	40U
#define SONAR0_EMIOS_CH		0U

#define SONAR_TRIGAR		0
#define SONAR_WAIT_RISING	1
#define SONAR_SENSING		2
#define SONAR_WAIT_ECHO		3
#define SONAR_WAIT_END		4

#define MAX_SONAR_SENSOR	3

#define OBJECT_NOT_DETECTED	9999

int sonarGetDistance(void);
void sonarSensing(void);
int counterToDistance(unsigned int counter);

int adcToDistance(int adcValue);
int getDistance(int channel);
int isObjectDetected(void);
#endif
