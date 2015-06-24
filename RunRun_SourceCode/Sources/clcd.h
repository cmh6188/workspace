#ifndef	___CLCD__H___
#define ___CLCD__H___

/********************************************
port D�� �̿�
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

//LCD ���� ���
#define ALLCLR			0x01	// ȭ���� �����.
#define HOME			0x02	// Ŀ���� Ȩ���� ������.

#define ENTMOD			0x06	// entry mode
 
#define FUNSET			0x28	// function set 

#define DISP_ON			0x0c	// ���÷��̸� �Ҵ�.
#define DISP_OFF		0x08	// ���÷��̸� ����.

#define CURSOR_ON		0x0e	// Ŀ���� �Ҵ�.
#define CURSOR_OFF		0x0c	// Ŀ���� ����.

#define CURSOR_LSHIFT  	0x10	// Ŀ���� ������ �̵���Ų��.
#define CURSOR_RSHIFT	0x14	// Ŀ���� ���������� �̵���Ų��.

#define DISP_LSHIFT		0x18	// ���÷��̸� �������� 
								// �̵���Ų��.
#define DISP_RSHIFT		0x1c	// ���÷��̸� ���������� 
								// �̵���Ų��.

//LCD �Լ���
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
