#include "eeprom_data.h"

void read_tq_total_time(void)
{
	TQ_TOTAL_TIME = AT24CXX_ReadOneByte(ADH_TQ_TOTAL_TIME);
	TQ_TOTAL_TIME <<= 8;
	TQ_TOTAL_TIME |= AT24CXX_ReadOneByte(ADM_TQ_TOTAL_TIME);
	TQ_TOTAL_TIME <<= 8;
	TQ_TOTAL_TIME |= AT24CXX_ReadOneByte(ADL_TQ_TOTAL_TIME);
	if(TQ_TOTAL_TIME > 9999999){
		TQ_TOTAL_TIME = 9999999;
		write_tq_total_time();
	}	
}

void write_tq_total_time(void)
{
	AT24CXX_WriteOneByte(ADH_TQ_TOTAL_TIME,TQ_TOTAL_TIME/65536);
    AT24CXX_WriteOneByte(ADM_TQ_TOTAL_TIME,TQ_TOTAL_TIME%65536/256);
	AT24CXX_WriteOneByte(ADL_TQ_TOTAL_TIME,TQ_TOTAL_TIME%256);
}
//----------------------------------------------------------------------------//
void read_max_water_temp(void)
{
  	MAX_WATER_TEMP = AT24CXX_ReadOneByte(AD_MAX_WATER_TEMP);
	if(MAX_WATER_TEMP > 90){
		MAX_WATER_TEMP = 50;
	   	write_max_water_temp();
	}
}
 
void write_max_water_temp(void)
{
  	AT24CXX_WriteOneByte(AD_MAX_WATER_TEMP,MAX_WATER_TEMP);
}
//----------------------------------------------------------------------------//
void read_tq_set_pwm(u8 num)
{
	u8 ad;
	ad = 2*num + AD_START_TQ_SET_PWM;
	TQ_SET_PWM[num] = AT24CXX_ReadOneByte(ad);
	TQ_SET_PWM[num] <<= 8;
	TQ_SET_PWM[num] |= AT24CXX_ReadOneByte(ad + 1);	
}

void write_tq_set_pwm(u8 num)
{
	u8 ad;
	ad = 2*num + AD_START_TQ_SET_PWM;
	AT24CXX_WriteOneByte(ad,TQ_SET_PWM[num]/256);
	AT24CXX_WriteOneByte(ad+1,TQ_SET_PWM[num]%256);	
}

void read_all_tq_set_pwm(void)
{
	u8 i;
	for(i=0;i<6;i++){
		read_tq_set_pwm(i);
	}
	if(TQ_SET_PWM[0] >= TQ_SET_PWM[1] || TQ_SET_PWM[1] >= TQ_SET_PWM[2] || TQ_SET_PWM[2] >= TQ_SET_PWM[3] ||
	   TQ_SET_PWM[3] >= TQ_SET_PWM[4] || TQ_SET_PWM[4] >= TQ_SET_PWM[5] || TQ_SET_PWM[0] == 0 || 
	   TQ_SET_PWM[5] > MAX_PWM_VALUE || TQ_SET_PWM[0]%100 != 0 || TQ_SET_PWM[1]%100 != 0 || 
	   TQ_SET_PWM[2]%100 != 0 || TQ_SET_PWM[3]%100 != 0 || TQ_SET_PWM[4]%100 != 0 || TQ_SET_PWM[5]%100 != 0){
		TQ_SET_PWM[0] = 1000;
		TQ_SET_PWM[1] = 4000;
		TQ_SET_PWM[2] = 7000;
		TQ_SET_PWM[3] = 10000;
		TQ_SET_PWM[4] = 13000;
		TQ_SET_PWM[5] = 16000;
		for(i=0;i<6;i++){
			write_tq_set_pwm(i);
		}
	}
}
//----------------------------------------------------------------------------//
//void read_tq_set_time(void)
//{
//  	TQ_SET_TIME = AT24CXX_ReadOneByte(AD_TQ_SET_TIME);
//	if(TQ_SET_TIME > 50 || TQ_SET_TIME == 0){
//		TQ_SET_TIME = 10;
//	   	write_tq_set_time();
//	}
//}
// 
//void write_tq_set_time(void)
//{
//  	AT24CXX_WriteOneByte(AD_TQ_SET_TIME,TQ_SET_TIME);
//}
//----------------------------------------------------------------------------//








