/*
 * filter.h
 *
 *  Created on: Jun 18, 2014
 *      Author: RuleTheComputer
 */

#ifndef ___FILTER_H_
#define ___FILTER_H_

void selectionSort(int *array,int arraySize);
int maxAdd(int* array,int arraySize);
int medianFilter(int *array,int arraySize,int midValue);
unsigned long int lowPassfilter(unsigned long int preData,unsigned long int presentData);


#endif /* FILTER_H_ */
