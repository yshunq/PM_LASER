#include "other.h"

u8 check_waterway(void)
{
	if(CHECK_WATERWAY == 1){
		delay_ms(1);
		if(CHECK_WATERWAY == 1){
			return WATER_ERROR;
		}	
	}
	return 0;
}

u16 count_tq_work_set_vol(void)
{
	u32 temp,gear,pwm;
   	gear = TQ_ENERGY_GEAR/50;//µµÎ»±äÎª1 - 20µµ
	if(gear == 1)pwm = TQ_SET_PWM[0];
	else{
		temp = gear/4;
		if(temp > 5)temp = 5;
		if(temp == 0){
			pwm = (TQ_SET_PWM[1] - TQ_SET_PWM[0])*(gear - 1)/(4-1) + TQ_SET_PWM[0];		
		}else if(temp == 5){
			pwm = TQ_SET_PWM[5];
		}else{
			pwm = (TQ_SET_PWM[temp+1] - TQ_SET_PWM[temp])*(gear%4)/4 + TQ_SET_PWM[temp];	
		}		
	}
	return (u16)pwm;	
}

void count_tq_work_laser_level(void)
{
	switch(TQ_LASER_LEVEL)
	{
		case  0x00:laser_light_close_pwm();break;
		case  0x01:laser_light_pwm(YAG_PWM_CYCLE,1720);break;
		case  0x02:laser_light_pwm(YAG_PWM_CYCLE,2150);break;
		case  0x03:laser_light_pwm(YAG_PWM_CYCLE,2580);break;
		case  0x04:laser_light_pwm(YAG_PWM_CYCLE,3010);break;
		case  0x05:laser_light_pwm(YAG_PWM_CYCLE,3440);break;
		case  0x06:laser_light_pwm(YAG_PWM_CYCLE,3870);break;
		case  0x07:laser_light_pwm(YAG_PWM_CYCLE,4300);break;
		case  0x08:laser_light_pwm(YAG_PWM_CYCLE,4730);break;
		case  0x09:laser_light_pwm(YAG_PWM_CYCLE,5160);break;
	}

	// 7740 - 5V
	// 6880 - 4.36V
	// 6020 - 3.82V
	// 5160 - 3.27V
}





