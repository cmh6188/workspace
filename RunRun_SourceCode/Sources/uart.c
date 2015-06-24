#include "uart.h"


void TransmitCharacter(uint8_t ch)
{
	LINFLEX_0.BDRL.B.DATA0 = ch;  			/* write character to transmit buffer */
	while (1 != LINFLEX_0.UARTSR.B.DTF) {}  /* Wait for data transmission completed flag */
	LINFLEX_0.UARTSR.R = 0x0002; 			/* clear the DTF flag and not the other flags */	
}

void TransmitData (char TransData[]) 
{
	uint8_t	j=0;                                /* Dummy variable */	
	while(TransData[j]){
		TransmitCharacter(TransData[j]);  		/* Transmit a byte */	
		j++;
	}
}


void intToChar(long int value,int stringSize,char *string) 
{ 
  int i; 
  stringSize -=2; 
  
  if(value>=0)  {
     for(i=0;i<stringSize;i++){ 
    
      string[stringSize-i] = (char)(value %  10 +'0'); 
      value /=10; 
      string[0] = (char)(value %  10 +'0'); 
      string[stringSize+1] = 0x00; 
    }
  } else { 
    string[0]='-'; 
    value = -value; 
    
    for(i=1;i<stringSize;i++){ 
      string[stringSize-i+1] =(char)( value %  10 +'0'); 
      value /=10; 
    } 
    string[1] = (char)(value %  10 +'0'); 
    string[stringSize+1] = 0x00; 
  } 

} 
