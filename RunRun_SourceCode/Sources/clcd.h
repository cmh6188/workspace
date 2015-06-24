#ifndef	___CLCD__H___
#define ___CLCD__H___

/********************************************
port D를 이용
PORT D : PC7 PC6 PC5 PC4 PC3 PC2 PC1 PC0
LCD Pin: D7	 D6	 D5	 D4	  X	 E	 R/W RS
****************************************/

#define PORTA	0
#define PORTB	1
#define PORTC	2
#define PORTD	3
#define PORTE	4
#define PORTF	5
#define PORTG	6
#define PORTH	7

//LCD 제어 명령
#define ALLCLR			0x01	// 화면을 지운다.
#define HOME			0x02	// 커서를 홈으로 보낸다.

#define ENTMOD			0x06	// entry mode
 
#define FUNSET			0x28	// function set 

#define DISP_ON			0x0c	// 디스플레이를 켠다.
#define DISP_OFF		0x08	// 디스플레이를 끈다.

#define CURSOR_ON		0x0e	// 커서를 켠다.
#define CURSOR_OFF		0x0c	// 커서를 끈다.

#define CURSOR_LSHIFT  	0x10	// 커서를 왼쪽을 이동시킨다.
#define CURSOR_RSHIFT	0x14	// 커서를 오른쪽으로 이동시킨다.

#define DISP_LSHIFT		0x18	// 디스플레이를 왼쪽으로 
								// 이동시킨다.
#define DISP_RSHIFT		0x1c	// 디스플레이를 오른쪽으로 
								// 이동시킨다.

//LCD 함수들
void lcdInit(void);
void checkbusy(void);
void lcdCommand(char command);
void lcdMove(char line, char pos);
void lcdWriteChar(char letter);
void lcdWrite(char * string);
void writeCommand(char command);
void lcdClear(void);
void delayMs(int ms);
void delayUs(int us);
void portSet(unsigned int port,unsigned long int value);
void LCD_PORT(unsigned long int value);
void sensingLCD(void);
void lcdInitPrint(void);
//lcd pins
#define THL_ADC	4
#define THR_ADC	5

#endif
