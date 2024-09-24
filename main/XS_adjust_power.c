#include "config.h"

const u8  code MAIN_KEY_ADJUST_POWER = 16;
const u16 code MAIN_ADJUST_POWER[]=
{
	478,596,190,312,
	790,915,190,312,
	478,596,328,448,
	790,915,328,448,
	478,596,469,588,
	790,915,469,588,

	1005,1130,190,312,
	1319,1446,190,312,
	1005,1130,328,448,
	1319,1446,328,448,
	1005,1130,469,588,
	1319,1446,469,588,

	742,863,732,854,
	1052,1180,732,854,
	0,150,0,150,
	1760,1919,0,150,
};
void dis_adjust_power_tq_set_pwm(u8 num);
void dis_adjust_power_tq_set_time(void);
void main_xs_adjust_power(void)
{
	u8 key,last_down,num;
	u16 pwm_value;
	DIS_PICNUM(Pic_ADJUST_POWER);
	read_all_tq_set_pwm();
	dis_adjust_power_tq_set_pwm(0);
	dis_adjust_power_tq_set_pwm(1);
	dis_adjust_power_tq_set_pwm(2);
	dis_adjust_power_tq_set_pwm(3);
	dis_adjust_power_tq_set_pwm(4);
	dis_adjust_power_tq_set_pwm(5);
	dis_adjust_power_tq_set_time();

	TQ_ENERGY_GEAR = 50;
	pwm_value = count_tq_work_set_vol();
	yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
	do{
		delay_ms(1);
		if(KEY_YES!=0x00)
		{
			ADS7843_KEY(); //É¨Ãè°´¼ü
			key=KEY_FANHUI(MAIN_KEY_ADJUST_POWER,MAIN_ADJUST_POWER); 
			if(key <= 12 && key > 0){
				XIANG1();
				num = (key-1)/2;
				if(key%2 == 1){//¼õ¼õ
					if(num == 0){
						if(TQ_SET_PWM[num] > 100)TQ_SET_PWM[num] -= 100;	
					}else{
						if(TQ_SET_PWM[num] > (TQ_SET_PWM[num-1] + 100))TQ_SET_PWM[num] -= 100;	
					}
					dis_adjust_power_tq_set_pwm(num);
					last_down = num + 1;
					delay_ms(100);
				}else{//¼Ó¼Ó
					if(num == 5){
						if(TQ_SET_PWM[num] < MAX_PWM_VALUE)TQ_SET_PWM[num] += 100;	
					}else{
						if(TQ_SET_PWM[num] < (TQ_SET_PWM[num+1] - 100))TQ_SET_PWM[num] += 100;	
					}
					dis_adjust_power_tq_set_pwm(num);
					last_down = num + 1;
					delay_ms(100);
				}
			}else if(key == 13){
//				if(TQ_SET_TIME > 1){
//					XIANG1();
//					TQ_SET_TIME--;
//					dis_adjust_power_tq_set_time();
//					last_down = 13;
//					delay_ms(100);
//				}else{KEY_YES = 0;}
			}else if(key == 14){
//				if(TQ_SET_TIME < 50){
//					XIANG1();
//					TQ_SET_TIME++;
//					dis_adjust_power_tq_set_time();
//					last_down = 13;
//					delay_ms(100);
//				}else{KEY_YES = 0;}
			}else if(key == 15){
				XIANG1();
				INTERFACE = PAGE_LOADING;
				goto over_main_xs_adjust_power;
			}else if(key == 16){
				XIANG1();
				TQ_SET_PWM[0] = 1000;
				TQ_SET_PWM[1] = 4000;
				TQ_SET_PWM[2] = 7000;
				TQ_SET_PWM[3] = 10000;
				TQ_SET_PWM[4] = 13000;
				TQ_SET_PWM[5] = 16000;
				//TQ_SET_TIME = 10;
				write_tq_set_pwm(0);
				write_tq_set_pwm(1);
				write_tq_set_pwm(2);
				write_tq_set_pwm(3);
				write_tq_set_pwm(4);
				write_tq_set_pwm(5);
				//write_tq_set_time();
				goto over_main_xs_adjust_power;	
			}
		}else{
			switch(last_down){
				case 1:
					TQ_ENERGY_GEAR = 50;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(0);
					break;
				case 2:
					TQ_ENERGY_GEAR = 200;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(1);
					break;
				case 3:
					TQ_ENERGY_GEAR = 400;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(2);
					break;
				case 4:
					TQ_ENERGY_GEAR = 600;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(3);
					break;
				case 5:
					TQ_ENERGY_GEAR = 800;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(4);
					break;
				case 6:
					TQ_ENERGY_GEAR = 1000;
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					write_tq_set_pwm(5);
					break;
				//case 13:write_tq_set_time();break;
			}last_down = 0;
		}
	}while(1);
	over_main_xs_adjust_power:
	_nop_();
	yag_close_pwm();
}

void dis_adjust_power_tq_set_pwm(u8 num)
{
	u16 x,y;
	switch(num){
		case 0:x= 636;y=227;break;
		case 1:x= 636;y=365;break;
		case 2:x= 636;y=503;break;
		case 3:x=1166;y=227;break;
		case 4:x=1166;y=365;break;
		case 5:x=1166;y=503;break;
	}
	DIS_FONT_WEI_NUMBER_CM(Pic_ADJUST_POWER,1,0x00,0x00,0x05,TQ_SET_PWM[num],5,x,y);
}

void dis_adjust_power_tq_set_time(void)
{
	DIS_FONT_WEI_NUMBER_CM(Pic_ADJUST_POWER,1,0x00,0x00,0x05,TQ_SET_TIME,2,932,768);
}

			  



