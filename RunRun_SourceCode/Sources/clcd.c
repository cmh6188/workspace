#include "clcd.h"
#include "jdp.h"
#include "gpio_drv.h"
#include "adc_drv.h"
#include "uart.h"

extern int distance[3];

extern unsigned short int maxRV;
extern unsigned short int maxLV;
extern unsigned short int minRV;
extern unsigned short int minLV;

extern unsigned short int thLV;
extern unsigned short int thRV;
void delayMs(int ms){
	volatile int i;
	for(i=0;i<ms;i++){
		delayUs(1000);
	}
}

//64Mhz
//1 clock pulse = 0.000000015625 sec = 0.000015625 ms = 0.015625 us 
//0.015625 : 1 = 1 = x
//x = 1 / 0.015625 = 64
void delayUs(int us){
	volatile int i,j;
	for(i=0;i<us;i++){
		for(j=0;j<64;j++);
	}
}


void LCD_PORT(unsigned long int value){
	//portSet(2,value);
	
	GPIO_SetState(32,(unsigned char)(value&0x01));
    GPIO_SetState(33,(unsigned char)((value&0x02)>>1));
    GPIO_SetState(34,(unsigned char)((value&0x04)>>2));
    GPIO_SetState(35,(unsigned char)((value&0x08)>>3));
    GPIO_SetState(36,(unsigned char)((value&0x10)>>4));
    GPIO_SetState(37,(unsigned char)((value&0x20)>>5));
    GPIO_SetState(38,(unsigned char)((value&0x40)>>6));
    GPIO_SetState(39,(unsigned char)((value&0x80)>>7));
    
	//SIU.GPDO[32].R=value;
	//SIU.PGPDO[1].R=value;
}
void lcdInit(void){
	
	delayMs(15);
	writeCommand(0x30);
	delayMs(5);
	writeCommand(0x30);
	delayMs(1);
	//delayUs(1000);
	writeCommand(0x32);
	//writeCommand(0x30);
	
	lcdCommand(FUNSET);
	lcdCommand(DISP_OFF);
	lcdCommand(ALLCLR);
	lcdCommand(ENTMOD);

	lcdCommand(DISP_ON);		// 화면을 켠다.
}


void lcdCommand(char command)
{
	checkbusy();
	writeCommand(command);
	if(command == ALLCLR || command == HOME)
		delayUs(2000);
}


/*********************************
wirte command diagram

1.RS_low 2.R/W_low 3. E_high and 1byte data
4. E_low 
**********************************/
void writeCommand(char command)
{
	unsigned long int temp;
	//명령어 전송 :  RS=0, RW =0 , E=1
	//상위 4비트
	
	temp = ((unsigned long int)command & 0xF0 ) | 0x04;

	LCD_PORT(temp);
	
	LCD_PORT(temp & ~0x04);		//E=0
	
	//하위 4비트
	temp = ((unsigned long int)command <<4) | 0x04;

	LCD_PORT(temp);
	
	LCD_PORT(temp & ~0x04); // E=0
	

	//만약 안뜨면 여기에 지연 해야함 ( lcd마다 다름)
	delayUs(1);

}

//20*4
void lcdMove(char line, char pos)
{
	char address;
	
	switch(line){
	default:
	case 0:	
		address = pos;
		break;	
		
	case 1:	
		address = pos;
		address |=0x40;
		break;
	case 2:
		address = pos + 20;
		break;
	case 3:
		address = pos +  20;
		address |=0x40;
	}
	address |= 0x80;

	lcdCommand(address);
}

void lcdWriteChar(char letter)
{	
	unsigned long int temp;
	
	checkbusy();	
	//상위 4비트
	temp = ((unsigned long int)letter & 0xF0) | 0x05;
	/**********************
		lcd write diagram
	RS = 1, RW = 0 , E =1
	RS = 1, RW = 0 , E =0
	**********************/
	//data 보내기 
	LCD_PORT(temp);	
	LCD_PORT(temp & ~0x04);	

	//하위 4비트
	temp = ((unsigned long int)letter <<4) | 0x05;
	//data 보내기 
	LCD_PORT(temp);	
	LCD_PORT(temp & ~0x04);
	
}


void lcdWrite(char * string)
{

	while(*string)
	{
		lcdWriteChar(*string);
		string++;		
	}
	
}
/********************************
모든 명령은 50us 이내에 실행이 됨.
그렇기 때문에, 간단히 딜레이만 줌
*********************************/
void checkbusy(void)
{
	delayUs(100);
}


void lcdClear(void)
{
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<20;j++){
			lcdMove((char)i,(char)j);
			lcdWrite(" ");
		}
	}
}


void lcdInitPrint(void){
	
	lcdInit();
	lcdMove(0,0);
	
	lcdWrite("[Run Run!!][d]     "); 
	lcdMove(1,0);
	lcdWrite("L:[M]      [m]     "); 
	lcdMove(2,0);
	lcdWrite("R:[M]      [m]     ");
	lcdMove(3,0);
	lcdWrite("t:[L]      [R]     ");	

}

void sensingLCD(void){
	char buf[5];
		
	lcdMove(0,14);		
	intToChar(distance[0],5,buf);
	lcdWrite(buf);
	//print left Max
	lcdMove(1,5);	
	intToChar(maxLV,5,buf);
	lcdWrite(buf);
	//print left Min
	lcdMove(1,14);	
	intToChar(minLV,5,buf);
	lcdWrite(buf);
	
	//print Right Max
	lcdMove(2,5);	
	intToChar(maxRV,5,buf);
	lcdWrite(buf);
	//print right Min
	lcdMove(2,14);	
	intToChar(minRV,5,buf);
	lcdWrite(buf);
	
	//print thV
	lcdMove(3,5);	
	thLV=A2D_GetSingleCh_10bit(THL_ADC);
	intToChar(thLV,5,buf);
	lcdWrite(buf);
	
	lcdMove(3,14);		
	thRV=A2D_GetSingleCh_10bit(THR_ADC);
	intToChar(thRV,5,buf);
	lcdWrite(buf);
}
