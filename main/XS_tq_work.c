#include "config.h"

const u8  code MAIN_KEY_TQ_WORK = 14;
const u16 code MAIN_TQ_WORK[]=
{
	  154,326,160,291, //1320
	  340,508,158,291, //1064
	  392,543,310,429, //532
	  278,380,403,575, //650
	  146,262,322,462, //585

	  1396,1804,176,540, //6

	  67,180,683,852,	 //7
	  491,608,683,852,	 //8
	  1313,1436,683,852, //9
	  1740,1868,683,852, //10

	  1443,1518,981,1056, //11
	  1657,1741,981,1056, //12

	  808,1124,623,913,
	  0,258,917,1079,	  //13
};

u8 check_temp_error(u8 temp);

void main_xs_tq_work(void)
{
	u8 key,last_down,error_flag,buff_temp,actual_temp,start_key_down_flag,precombustion_flag,key_flag,temp_error,water_error,sopt_size;
	u16 touch_count,i,temp,pwm_value;
	DIS_PICNUM(Pic_TQ_WORK);

	TQ_CURE_TIME = 0;

	sopt_size = TQ_SPOT_SIZE;

	cut_tq_work_wavelength();
	dis_tq_work_frequency_gear(DIS_ALL);
	dis_tq_work_energy_gear(DIS_ALL);
	dis_tq_work_total_time(DIS_ALL);
	dis_tq_work_cure_time(DIS_ALL);	
	dis_tq_work_spot_size(DIS_ALL);
	dis_tq_work_energy_density(DIS_ALL);
	cut_tq_work_laser_level();

	YAG_PRECOMBUSTION_OFF;
	YAG_CHARGE_OFF;
	YAG_SET_OFF;

	START_STOP_FLAG = 1;
	TQ_WORK_FLAG = 1;
	TQ_ADD_FLAG = 1;
	error_flag = 0;
	last_down = 0;
	touch_count = 0;
	buff_temp = 0xff;
	actual_temp = 0;
	start_key_down_flag = 1;
	precombustion_flag = 1;
	temp_error = 0;
	water_error = 0;

	pwm_value = count_tq_work_set_vol();
	yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);

	count_tq_work_laser_level();

	key_flag = YAG_SRART_KEY;

	if(XIAN_FLAG == 0){
		DIS_FONT_C(0xff,0xff,9,0x01,0,0,"ACT_TEMP:");

		DIS_FONT_C(0xff,0xff,9,0x01,0,16,"MAX_TEMP:");
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,MAX_WATER_TEMP,3,9*8,16);

		DIS_FONT_C(0xff,0xff,9,0x01,0,32,"PWM_VOLT:");
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,pwm_value,5,9*8,32);

		DIS_FONT_C(0xff,0xff,9,0x01,0,48,"SET_TIME:");
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,TQ_SET_TIME,5,9*8,48);
	}

	

	do{
		delay_ms(1);
		if(KEY_YES!=0x00 && touch_count == 0){
			ADS7843_KEY(); //扫描按键
			key=KEY_FANHUI(MAIN_KEY_TQ_WORK,MAIN_TQ_WORK); 
			switch(key){
				case 1:
					if(WAVELENGTH != WL1320NM && START_STOP_FLAG == 1){
				  		XIANG1();
				  		WAVELENGTH = WL1320NM;
						cut_tq_work_wavelength();
						MOTOR_LEFT_ON;
						for(i=0;i<9;i++){
					   		delay_ms(250);
							cut_tq_work_wavelength_cover();
							delay_ms(250);
							cut_tq_work_wavelength();
						}
						MOTOR_STOP_ON;
					}KEY_YES = 0;
					break;
				case 2:
					if(WAVELENGTH != WL1064NM && START_STOP_FLAG == 1){
				  		XIANG1();
				  		WAVELENGTH = WL1064NM;
						cut_tq_work_wavelength();
						MOTOR_LEFT_ON;
						for(i=0;i<9;i++){
					   		delay_ms(250);
							cut_tq_work_wavelength_cover();
							delay_ms(250);
							cut_tq_work_wavelength();
						}
						MOTOR_STOP_ON;
					}KEY_YES = 0;
					break;
				case 3:
					if(WAVELENGTH != WL532NM && START_STOP_FLAG == 1){
				  		XIANG1();
				  		WAVELENGTH = WL532NM;
						cut_tq_work_wavelength();
						MOTOR_RIGHT_ON;
						for(i=0;i<9;i++){
					   		delay_ms(250);
							cut_tq_work_wavelength_cover();
							delay_ms(250);
							cut_tq_work_wavelength();
						}
						MOTOR_STOP_ON;
					}KEY_YES = 0;
					break;
				case 4:
					if(WAVELENGTH != WL650NM && START_STOP_FLAG == 1){
				  		XIANG1();
				  		WAVELENGTH = WL650NM;
						cut_tq_work_wavelength();
						MOTOR_LEFT_ON;
						for(i=0;i<9;i++){
					   		delay_ms(250);
							cut_tq_work_wavelength_cover();
							delay_ms(250);
							cut_tq_work_wavelength();
						}
						MOTOR_STOP_ON;
					}KEY_YES = 0;
					break;
				case 5:
					if(WAVELENGTH != WL585NM && START_STOP_FLAG == 1){
				  		XIANG1();
				  		WAVELENGTH = WL585NM;
						cut_tq_work_wavelength();
						MOTOR_LEFT_ON;
						for(i=0;i<9;i++){
					   		delay_ms(250);
							cut_tq_work_wavelength_cover();
							delay_ms(250);
							cut_tq_work_wavelength();
						}
						MOTOR_STOP_ON;
					}KEY_YES = 0;
					break;
				case 6:	//启动 停止
					if(TQ_WORK_FLAG == 1){
						XIANG1();
						start_key_down_flag = 0;
					}KEY_YES = 0;
					break;
				case 7:
					if(TQ_FREQUENCY_GEAR > 1 && START_STOP_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,67,683,180,852,67,683);
						XIANG1();
				  		TQ_FREQUENCY_GEAR--;
						dis_tq_work_frequency_gear(DIS_PART);
						dis_tq_work_energy_density(DIS_PART);
						touch_count = 100;
						last_down = 7;
					}else{KEY_YES = 0;}
					break;
				case 8:
					if(TQ_FREQUENCY_GEAR < 10 && START_STOP_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,491,683,608,852,491,683);
						XIANG1();
				  		TQ_FREQUENCY_GEAR++;
						dis_tq_work_frequency_gear(DIS_PART);
						dis_tq_work_energy_density(DIS_PART);
						touch_count = 100;
						last_down = 8;
					}else{KEY_YES = 0;}
					break;
				case 9:
					if(TQ_ENERGY_GEAR > 50 && START_STOP_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,1313,683,1436,852,1313,683);
						XIANG1();
				  		TQ_ENERGY_GEAR -= 50;
						dis_tq_work_energy_gear(DIS_PART);
						dis_tq_work_energy_density(DIS_PART);
						touch_count = 100;
						last_down = 9;
					}else{KEY_YES = 0;}
					break; 
				case 10:
					if(TQ_ENERGY_GEAR < 1000 && START_STOP_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,1740,683,1868,852,1740,683);
						XIANG1();
				  		TQ_ENERGY_GEAR += 50;
						dis_tq_work_energy_gear(DIS_PART);
						dis_tq_work_energy_density(DIS_PART);
						touch_count = 100;
						last_down = 10;
					}else{KEY_YES = 0;}
					break;
				case 11:
					if(TQ_LASER_LEVEL > 0 && TQ_WORK_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,1448,1002,1502,1036,1448,1002);
						XIANG1();
				  		TQ_LASER_LEVEL--;
						cut_tq_work_laser_level();
						touch_count = 100;
						last_down = 11;
					}else{KEY_YES = 0;}
					break; 
				case 12:
					if(TQ_LASER_LEVEL < 9 && TQ_WORK_FLAG == 1){
				  		DIS_DEL_DIS(Pic_TQ_WORK_DOWN,1669,1002,1724,1036,1669,1002);
						XIANG1();
				  		TQ_LASER_LEVEL++;
						cut_tq_work_laser_level();
						touch_count = 100;
						last_down = 12;
					}else{KEY_YES = 0;}
					break;
				case 13:
					if(TQ_WORK_FLAG == 1){
						XIANG1();
						TQ_SPOT_SIZE++;
						if(TQ_SPOT_SIZE > 10)TQ_SPOT_SIZE = 1;
						sopt_size = TQ_SPOT_SIZE;
						dis_tq_work_spot_size(DIS_PART);
						dis_tq_work_energy_density(DIS_PART);
					}KEY_YES = 0;
					break;
				case 14:	//返回
					if(START_STOP_FLAG == 1){
						DIS_DEL_DIS(Pic_TQ_WORK_DOWN,0,917,258,1079,0,917);
					  	XIANG1();
					  	INTERFACE = PAGE_LOADING;
						goto over_main_xs_tq_work;
					}KEY_YES = 0;
					break;
			}
		}else if(KEY_YES == 0 && touch_count == 0){
			switch(last_down){
				case 7:DIS_DEL_DIS(Pic_TQ_WORK,67,683,180,852,67,683);break;
				case 8:DIS_DEL_DIS(Pic_TQ_WORK,491,683,608,852,491,683);break;
				case 9:
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					if(XIAN_FLAG == 0)DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,pwm_value,5,9*8,32);
					DIS_DEL_DIS(Pic_TQ_WORK,1313,683,1436,852,1313,683);break;
				case 10:
					pwm_value = count_tq_work_set_vol();
					yag_voltage_pwm(YAG_PWM_CYCLE,pwm_value);
					if(XIAN_FLAG == 0)DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,pwm_value,5,9*8,32);
					DIS_DEL_DIS(Pic_TQ_WORK,1740,683,1868,852,1740,683);break;
				case 11:
					count_tq_work_laser_level();
					DIS_DEL_DIS(Pic_TQ_WORK,1448,1002,1502,1036,1448,1002);break;
				case 12:
					count_tq_work_laser_level();
					DIS_DEL_DIS(Pic_TQ_WORK,1669,1002,1724,1036,1669,1002);break;
			}last_down = 0;	
		}

		if(touch_count > 0)touch_count--;

	   	if(start_key_down_flag == 0){//有按键按下
			if(START_STOP_FLAG == 1){//进入预燃状态
				cut_tq_work_start_pic();
				for(i=0;i<2;i++){//预燃两次
					YAG_CHARGE_OFF;
					YAG_PRECOMBUSTION_ON;
					temp = 0;
					while(temp < 1000){
						delay_ms(1);
						temp++;
						precombustion_flag = CHECK_PRECOMBUSTION_KEY;
						if(precombustion_flag == 0)goto over_precombustion_flish;
					}
					YAG_PRECOMBUSTION_OFF;
					delay_ms(1000);
				}
				over_precombustion_flish:
				if(precombustion_flag == 0){//预燃正确
					YAG_CHARGE_ON;
					START_STOP_FLAG = 0;
				}else{//预燃失败
					START_STOP_FLAG = 1;
					DIS_PICNUM(Pic_SIMMER_ERROR);
					XIANG1();
					delay_ms(200);
					XIANG1();
					KEY_YES = 0;
					while(KEY_YES == 0);
					XIANG1();
					INTERFACE = PAGE_LOADING;
					goto over_main_xs_tq_work;
				}
			}else{//退出预燃状态
				START_STOP_FLAG = 1;
				YAG_PRECOMBUSTION_OFF;
				YAG_CHARGE_OFF;
				//YAG_SET_OFF;
				cut_tq_work_stop_pic();
			}
			start_key_down_flag = 1;
		}
		
		if(key_flag != YAG_SRART_KEY){//判断按键状态
			key_flag = YAG_SRART_KEY;
			if(START_STOP_FLAG == 0){//准备的状态下
				if(key_flag == 0){
					TQ_WORK_CYCLE = 1000/TQ_FREQUENCY_GEAR;
					BUZZER_ON;
					delay_ms(1000);
					BUZZER_OFF;
					if(YAG_SRART_KEY == 0){//还继续按下才有输出
						TQ_WORK_COUNT_TT = 1000;
						TQ_WORK_FLAG = 0;
					}
				}else{
					TQ_WORK_FLAG = 1;
					XIANG1();	
				}
			}
		}
		
		if(TQ_ADD_FLAG == 0){
			TQ_ADD_FLAG = 1;
			if(TQ_TOTAL_TIME < 9999999){
				TQ_TOTAL_TIME++;
				write_tq_total_time();
				dis_tq_work_total_time(DIS_PART);
			}
			if(TQ_CURE_TIME < 99999){
				TQ_CURE_TIME++;
				dis_tq_work_cure_time(DIS_PART);		
			}
		}	  
		
		if(timekeeping_100ms(1)){//100ms
			timekeeping_100ms(0);//清零计数

			if(sopt_size != TQ_SPOT_SIZE){
				sopt_size = TQ_SPOT_SIZE;
				dis_tq_work_spot_size(DIS_PART);
				dis_tq_work_energy_density(DIS_PART);
			}
			//--------------------水路报警--------------------//
			if(check_waterway() == WATER_ERROR)water_error++;else{water_error = 0;}
			if(water_error >= 5){
				DIS_PICNUM(Pic_WATERWAY_ERROR);
				i = 0;
				while(check_waterway() == WATER_ERROR){
					i++;
					delay_ms(1);
					if(i > 500){
						i = 0;
						XIANG1();
					}
					if(KEY_YES != 0)break;
				}
				INTERFACE = PAGE_LOADING;
				goto over_main_xs_tq_work;		
			}
			//--------------------温度报警--------------------//
			actual_temp = get_water_temp();//读取温度
			if(XIAN_FLAG == 0 && actual_temp != buff_temp){
				buff_temp = actual_temp;
				dis_tq_work_temp(actual_temp);
			}
			temp = check_temp_error(actual_temp);//读取返回值
			if(temp > 0)temp_error++;else{temp_error = 0;}
			if(temp > 0 && temp_error >= 5){//故障
				if(temp == 1){
					DIS_PICNUM(Pic_NTC_OPEN_CIRCUIT);
				}else if(temp == 2){
					DIS_PICNUM(Pic_NTC_SHORT_CIRCUIT);
				}else if(temp == 3){
					DIS_PICNUM(Pic_TEMP_ERROR);
				}
				i = 0;
				DIS_FONT_C(0xff,0xff,9,0x01,0,0,"ACT_TEMP:");
				DIS_FONT_C(0xff,0xff,9,0x01,0,16,"MAX_TEMP:");
				DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,MAX_WATER_TEMP,3,9*8,16);
				while(temp > 0){
					i++;
					delay_ms(1);
					if(i > 500){
						i = 0;
						XIANG1();
						actual_temp = get_water_temp();//读取温度
						dis_tq_work_temp(actual_temp);
						temp = check_temp_error(actual_temp);//读取返回值
					}
					if(KEY_YES != 0)break;
				}
				INTERFACE = PAGE_LOADING;
				goto over_main_xs_tq_work;
			}	
		}
	}while(1);
	over_main_xs_tq_work:
	_nop_();
	YAG_PRECOMBUSTION_OFF;
	YAG_CHARGE_OFF;
	YAG_SET_OFF;
	laser_light_close_pwm();
}

u8 check_temp_error(u8 temp)
{
	if(temp == 255){//开路
		return 1;				
	}else if(temp == 254){//短路
		return 2;
	}else if(temp >= (MAX_WATER_TEMP + 10)){//温度过高报警
		return 3;
	}//else if(temp < (WATER_TEMP + 10)){//温度正常
		return 0;
	//}	
} 
 
 
 
 
 
 
 
 
 
 