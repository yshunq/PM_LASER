#ifndef __EEPROM_DATA_H
#define __EEPROM_DATA_H
#include "config.h"

void read_tq_total_time(void);
void write_tq_total_time(void);
void read_max_water_temp(void);
void write_max_water_temp(void);
void read_tq_set_pwm(u8 num);
void write_tq_set_pwm(u8 num);
void read_all_tq_set_pwm(void);
void read_tq_set_time(void);
void write_tq_set_time(void);
	
#endif
















