
#ifndef _PWM_H
#define _PWM_H

#include "config.h"

#define YAG_PWM_CYCLE   2000
#define MAX_PWM_VALUE	FOSC/YAG_PWM_CYCLE/100*100


void yag_voltage_pwm(u16 dat,u16 val);//P0.6
void open_pwm(void);
void yag_close_pwm(void);

void laser_light_pwm(u16 dat,u16 val);
void laser_light_close_pwm(void);


#endif