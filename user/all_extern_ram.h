#ifndef __ALL_EXTERN_RAM_H__
#define __ALL_EXTERN_RAM_H__

#include "config.h"

extern unsigned char KEY_YES;
extern unsigned char INTERFACE;
//extern unsigned int DELAY_MS;
//extern unsigned char FLAG;

extern bit XIAN_FLAG;
extern bit START_STOP_FLAG;
extern bit TQ_WORK_FLAG;
extern bit TQ_ADD_FLAG;

extern unsigned char KEY_YES;
extern unsigned int  ADS7843_X,ADS7843_Y;
extern unsigned char KEY_XH,KEY_XL;
extern unsigned char KEY_YH,KEY_YL; 

extern xdata unsigned char BUZZER_COUNT;
extern xdata unsigned char WAVELENGTH;
extern xdata unsigned char TQ_FREQUENCY_GEAR;
extern xdata unsigned int TQ_ENERGY_GEAR;
extern xdata unsigned long TQ_TOTAL_TIME;
extern xdata unsigned int TQ_CURE_TIME;
extern xdata unsigned char TQ_SPOT_SIZE;
extern xdata unsigned char TQ_LASER_LEVEL;

extern xdata unsigned char WATER_TEMP;
extern xdata unsigned char MAX_WATER_TEMP;

extern xdata unsigned int TQ_SET_PWM[6];
extern xdata unsigned char TQ_SET_TIME;
extern xdata unsigned int TQ_WORK_COUNT_TT;
extern xdata unsigned int TQ_WORK_CYCLE;
extern xdata unsigned char TQ_SET_COUNT;

extern xdata unsigned int TQ_SPOT_COUNT;


#endif