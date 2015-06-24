#ifndef	___CONTROL__H__
#define ___CONTROL__H__


#define EMIOS_ENCODER_CH	24

void control(void);
long int angleControl(void);
void speedControl(long int aimSpeed);
long int pidControl(long int speedRf,long int feedback);
long int readEnco(void);
long int enToSpeed(long int en);
long int abs(long int value);

#endif
