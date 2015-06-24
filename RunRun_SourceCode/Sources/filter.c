/*
 * filter.c
 *
 *  Created on: Jun 18, 2014
 *      Author: RuleTheComputer
 */


#include "filter.h"

int medianFilter(int *array,int arraySize,int midValue){
	selectionSort(array,arraySize);
	return array[midValue];		
}


void selectionSort(int *array,int arraySize){
	int i,temp,maxAddress;
	for(i=arraySize-1;i>=0;i--){
		maxAddress=maxAdd(array,i+1);	
		temp = array[maxAddress];
		array[maxAddress] = array[i];
		array[i] = temp;		
	}	
}

int maxAdd(int* array,int arraySize){
	int i,maxAdd;
	maxAdd = 0;
	for(i=arraySize-1;i>=0;i--){
		maxAdd = array[i]>array[maxAdd]?i:maxAdd;
	}
	return maxAdd;
}

unsigned long int lowPassfilter(unsigned long int preData,unsigned long int presentData){
	static const int gain = 9;
	unsigned long int lowPassedData;
	
	lowPassedData = (gain)*preData + (10-gain)*presentData;
	lowPassedData /=10;
	
	return lowPassedData;	
}
