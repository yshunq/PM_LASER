#ifndef __ALL_MAIN_RAM_H 
#define __ALL_MAIN_RAM_H 

unsigned char KEY_YES;
unsigned char INTERFACE;
//unsigned int DELAY_MS;
//unsigned char FLAG;

bit XIAN_FLAG;
bit START_STOP_FLAG;
bit TQ_WORK_FLAG;
bit TQ_ADD_FLAG;

unsigned char KEY_YES;
unsigned int  ADS7843_X,ADS7843_Y;
unsigned char KEY_XH,KEY_XL;
unsigned char KEY_YH,KEY_YL; 

xdata unsigned char BUZZER_COUNT;
xdata unsigned char WAVELENGTH;
xdata unsigned char TQ_FREQUENCY_GEAR;
xdata unsigned int TQ_ENERGY_GEAR;
xdata unsigned long TQ_TOTAL_TIME;
xdata unsigned int TQ_CURE_TIME;
xdata unsigned char TQ_SPOT_SIZE;
xdata unsigned char TQ_LASER_LEVEL;

xdata unsigned char WATER_TEMP;
xdata unsigned char MAX_WATER_TEMP;

xdata unsigned int TQ_SET_PWM[6];
xdata unsigned char TQ_SET_TIME;
xdata unsigned int TQ_WORK_COUNT_TT;
xdata unsigned int TQ_WORK_CYCLE;
xdata unsigned char TQ_SET_COUNT;

xdata unsigned int TQ_SPOT_COUNT;






#endif
 
 