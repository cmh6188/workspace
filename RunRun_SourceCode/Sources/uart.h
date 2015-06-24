#ifndef	___UART___H
#define	___UART___H

#include "typedefs.h"
#include "jdp.h"


void TransmitCharacter(uint8_t ch);
void TransmitData (char TransData[]) ;
void intToChar(long int value,int stringSize,char *string) ;

#endif
