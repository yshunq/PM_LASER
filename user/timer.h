#ifndef _TIMER_H
#define _TIMER_H
#include "config.h"

u8 timekeeping_100ms(u8 clear);
void delay_ms(u32 ms);
void Timer0_Init(void);
void Timer1_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);
void Timer4_Init(void);

#endif