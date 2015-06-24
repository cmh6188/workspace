/*
 *######################################################################
 *
 * Project Name           : P01.LedBlinking
 *
 * Revision Number        : 1.0
 *
 * file                   : main.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Project Last Save Date : 29-Dec-2014
 *
 * Created on Date        : 29-Dec-2014
 *
 * Author                 : ����̷����б� ����
 * 
 * Brief Description      : LED�� ��� �Ѵ��� ������ ����
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"
#include "typedefs.h"

/**********************  Function Prototype here *************************/

void delay_ms(uint32_t ms);
void main(void);

/*********************  Initialization Function(s) ************************/


//================================================================
// ms milliseconds ��ŭ �ð� ������ ��
//   DELAY_1MS_CNT ���� �����ϰ� ���ؾ� �� 
//================================================================
#define DELAY_1MS_CNT 2270 
void delay_ms(uint32_t ms)
{
	vuint32_t cnt;
	
	while (ms--)
		for (cnt=0; cnt<DELAY_1MS_CNT; cnt++) {
		}
}

void main(void)
{
	uint32_t i, j;
	
	//- sys_init_fnc() �Լ����� �ý�����(�������͸�) �ʱ�ȭ��
	sys_init_fnc();
	EnableExternalInterrupts();
   
	//- ȸ�ε��� ����, 
	//   LED1: PE4(68��), LED2: PE5(69��), LED3: PE6(70��), LED4: PE7(71��)
	//   LED�� ��� High ����� ��, OFF, Low ����� ��, ON��
	//

	//- PE4, PE5, PE6, PE7�� GPIO�� ������� �ʱ� �����ϴ� ����
	//   siu_init.c�� siu_init_fnc() �Լ��� ���
	//   siu_portE_init_fnc()�� ����, SIU.PCR[68].R = 0x0201; 

	//- �ϴ�, LED ��� OFF
	//   ����: �������Ϳ� �׼����� ���� Macro ��� ������ jdp.h�� ����
	SIU.GPDO[68].B.PDO = 1; // 1�̸� High ���, 0�̸� Low ���
	SIU.GPDO[69].B.PDO = 1;
	SIU.GPDO[70].B.PDO = 1;
	SIU.GPDO[71].B.PDO = 1;
   
	//- LED1���� 0.5�� ON, 0.5�� OFF�� 10ȸ �ݺ�
	while(1) {
		for (i=68; i<=71; i++) {
			for (j=0; j<10; j++) {
				SIU.GPDO[i].B.PDO = 0;
				delay_ms(500);
				SIU.GPDO[i].B.PDO = 1;
				delay_ms(500);
			}
		}
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
