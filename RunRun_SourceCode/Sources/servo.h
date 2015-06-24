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

#ifndef	___SERVO_____H____FOR__FUTABAS3010__
#define ___SERVO_____H____FOR__FUTABAS3010__


#define MAX_ANGLE	200
#define MIN_ANGLE	0

void servoAngle(int angle);
void moveAngle(int angle);


#endif
