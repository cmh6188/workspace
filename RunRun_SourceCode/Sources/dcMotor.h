/* [FUTABA_S3010_DEVICE Driver]
 * control frequency : 15.25
 * max : 2646 us
 * min : 380 us
 * 
 * [servo motor connection]
 * white line : control signal (PWM) - PE7 
 * red line   : power
 * black line : GND
 * 
 * [board-MPC5606B]
 * system clk : 64MHZ
 * GLOBAL prescaler : 64 => 1MHZ
 * MODE : PWM BUFFERED
 * B reg - set control signal freqency : 0xFFFF reg value
 * A reg - control duty                : range 380(0 degree) to 2646(200 degree)
 * 
 * jjhbaram@naver.com
 * 
 * code by JiHun Cho 2014-4-29
 */

#ifndef	___DC__MOTOR____H___
#define ___DC__MOTOR____H___


#define LEFT_MOTOR_EMIOS_O_CHANNEL		4	
#define RIGHT_MOTOR_EMIOS_O_CHANNEL		5	

//define of line scan channel
#define DC_ENALBLE			12	
#define DC_FAULTSTATUS		13	
#define DC1_OUT2			14	
#define DC2_OUT2			15	



void dcControl(long int duty);
void rightDC(long int duty);
void leftDC(long int duty);


#endif
