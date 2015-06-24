/*
 *######################################################################
 *
 * Project Name           : P05.LedSwichHW
 *
 * Revision Number        : 1.0
 *
 * file                   : main.c
 *
 * Target Compiler        : Codewarrior
 *
 * Target Part            : MPC5606B
 *
 * Project Last Save Date : 01-Jan-2015
 *
 * Created on Date        : 01-Jan-2015
 *
 * Author                 : ����̷����б� ���� (2015�� NGV ���л� �� ���� ����, ����, ������ ���մϴ�.)
 * 
 * Brief Description      : LED�� ����ġ�� ������ ���� (����)
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "ngv_dmu.h"
#include "rappid_ref.h"
#include "rappid_utils.h"
#include "sys_init.h"
#include "gpio.h"
#include "demoled.h"
#include "demoswitch.h"

/**********************  Function Prototype here *************************/

void delay_ms(uint32_t ms);
void InitPeripherals(void);
void main(void);

/*********************  Initialization Function(s) ************************/


//================================================================
// ms milliseconds ��ŭ �ð� ������ ��
//   DELAY_1MS_CNT ���� �����ϰ� ���ؾ� �� 
//================================================================
#if NGV_DMU_SYSCLK == SYSCLK_IRC_16MHZ
#define DELAY_1MS_CNT 2270
#elif NGV_DMU_SYSCLK == SYSCLK_PLL_32MHZ
#define DELAY_1MS_CNT (2270*2)
#elif NGV_DMU_SYSCLK == SYSCLK_PLL_64MHZ
#define DELAY_1MS_CNT (2270*4)
#endif

void delay_ms(uint32_t ms)
{
	vuint32_t cnt;
	
	while (ms--)
		for (cnt=0; cnt<DELAY_1MS_CNT; cnt++) {
		}
}

void InitPeripherals(void)
{
	sys_init_fnc();
	DLED_Init();
	DSW_Init();
	
	EnableExternalInterrupts();
}


void main(void)
{
	uint16_t dipsw;
	uint16_t n;
	uint16_t sts0_old=DSW_OFF, sts1_old=DSW_OFF, sts0_new, sts1_new;
	uint16_t cnt0=0, cnt1=0;
	  
	InitPeripherals();
	
	dipsw = DSW_GetDipAll();
	
	//- ù ��° ����
	if (dipsw==0x1) {
		
		while (1) {

			if (DSW_GetTactAll() & 0x1) {
				
				if ((n%10)==0)
					DLED_Toggle(DLED_LED1);
				if ((n%20)==0)
					DLED_Toggle(DLED_LED2);
				if ((n%30)==0)
					DLED_Toggle(DLED_LED3);
				if ((n%50)==0)
					DLED_Toggle(DLED_LED4);

			} else {
				DLED_SetAll(0);
			}

			if (++n == 300)
				n = 0;
			
			delay_ms(10);
		}

	}

	//- �� ��° ����
	else if (dipsw==0x2) {
		
		while (1) {

			// ��ư ����
			sts0_new = DSW_Get(DSW_S1);
			sts1_new = DSW_Get(DSW_S2);
	
			// ��ư�� ��������?
			if ((sts0_new==DSW_ON) && (sts0_old==DSW_OFF)) {
				DLED_Set(DLED_LED1, DLED_ON);
				cnt0 = 0;
			}
			if ((sts1_new==DSW_ON) && (sts1_old==DSW_OFF)) {
				DLED_Set(DLED_LED2, DLED_ON);
				cnt1 = 0;
			}
	
			// 2�ʰ� ��������?
			if (++cnt0 >= 200) {
				cnt0 = 200;
				DLED_Set(DLED_LED1, DLED_OFF);
			}
			if (++cnt1 >= 200) {
				cnt1 = 200;
				DLED_Set(DLED_LED2, DLED_OFF);
			}
	
			// ���� ������ ��ư �˻縦 ���� ó��
			sts0_old = sts0_new;
			sts1_old = sts1_new;
	
			delay_ms(10);
		}
		
	}

	//- �� ��° ����
	else if (dipsw==0x4) {

		for(;;) {

			// ��ư ����
			sts0_new = DSW_Get(DSW_S1);
	
			// ��ư�� ��������?
			if ((sts0_new==DSW_ON) && (sts0_old==DSW_OFF)) {
				if (++cnt0 == 8)
					cnt0 = 0;
				DLED_Set(DLED_LED2, cnt0&0x1 ? DLED_ON : DLED_OFF);
				DLED_Set(DLED_LED3, cnt0&0x2 ? DLED_ON : DLED_OFF);
				DLED_Set(DLED_LED4, cnt0&0x4 ? DLED_ON : DLED_OFF);
			}
	
			// 0.25�ʰ� ��������
			if (++cnt1 == 25) {
				cnt1 = 0;
				DLED_Toggle(DLED_LED1);
			}
	
			// ���� ������ ��ư �˻縦 ���� ó��
			sts0_old = sts0_new;
	
			delay_ms(10);
		}
		
	}
		

	// �̵� ���� �ƴϸ�...
	while(1) {
		DLED_Toggle(DLED_LED4);
		delay_ms(100);
	}
}

 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/
