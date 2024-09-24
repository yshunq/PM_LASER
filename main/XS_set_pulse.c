//#include "config.h"
//
//const u8  code MAIN_KEY_SET_PULSE = 6;
//const u16 code MAIN_SET_PULSE[]=
//{
//	0, 130,  0,130,
//	1775,1915,0,125,
//	
//	806,878,369,441,
//	1041,1113,369,441,
//	
//	806,878,560,632,
//	1041,1113,560,632,	
//};
//
//void dis_set_pulse_fast_pulse_time(void);
//void dis_set_pulse_normal_pulse_time(void);
//
//void main_xs_set_pulse(void)
//{
//	u8 key;
//	DIS_PICNUM(Pic_SET_PULSE);
//	read_fast_pulse_time();
//	read_normal_pulse_time();
//	dis_set_pulse_fast_pulse_time();
//	dis_set_pulse_normal_pulse_time();
//	do{
//		delay_ms(1);
//		if(KEY_YES!=0x00)
//		{
//			ADS7843_KEY(); //扫描按键
//			key=KEY_FANHUI(MAIN_KEY_SET_PULSE,MAIN_SET_PULSE); 
//			switch(key)
//			{
//				case 1:
//				    XIANG1();
//				    INTERFACE = PAGE_CHOOSE_MODE;
//					goto over_main_xs_set_pulse;
//					break;
//				case 2:
//					if(FAST_PULSE_TIME != 10 || NORMAL_PULSE_TIME != 10){
//						XIANG1();
//						FAST_PULSE_TIME = 10;
//						NORMAL_PULSE_TIME = 10;
//						write_fast_pulse_time();
//						write_normal_pulse_time();
//						goto over_main_xs_set_pulse;
//					}KEY_YES = 0;
//					break;
//				case 3:
//					if(FAST_PULSE_TIME > 10){
//						XIANG1();
//						FAST_PULSE_TIME--;
//						write_fast_pulse_time();
//						dis_set_pulse_fast_pulse_time();
//						delay_ms(50);
//					}else{KEY_YES=0;}
//					break;
//				case 4:
//					if(FAST_PULSE_TIME < 100){
//						XIANG1();
//						FAST_PULSE_TIME++;
//						write_fast_pulse_time();
//						dis_set_pulse_fast_pulse_time();
//						delay_ms(50);
//					}else{KEY_YES=0;}
//					break;
//				case 5:
//					if(NORMAL_PULSE_TIME > 10){
//						XIANG1();
//						NORMAL_PULSE_TIME--;
//						write_normal_pulse_time();
//						dis_set_pulse_normal_pulse_time();
//						delay_ms(50);
//					}else{KEY_YES=0;}
//					break;
//				case 6:
//					if(NORMAL_PULSE_TIME < 100){
//						XIANG1();
//						NORMAL_PULSE_TIME++;
//						write_normal_pulse_time();
//						dis_set_pulse_normal_pulse_time();
//						delay_ms(50);
//					}else{KEY_YES=0;}
//					break; 
//			}
//		}
//
//		WATER_TEMP = Get_ADC_RES_WATER_TEMP();//获取水温度
//		if(WATER_TEMP != 255)
//		{
//			if(WATER_TEMP >= WATER_COLD_UPPER_LIMITS)COLD_WATER_ON;	//温度高了打开制冷
//			if(WATER_TEMP <= WATER_COLD_LOWER_LIMITS)COLD_WATER_OFF;//温度低了关闭制冷
//		}else{COLD_WATER_OFF;}
//		
//		if(HANDLE_PROBE_TEMP != 255)//手柄温度
//		{
//			if(HANDLE_PROBE_TEMP >= HANDLE_PROBE_COLD_UPPER_LIMITS[HANDLE_PROBE_COLE_GEAR])COLD_HANDLE_PROBE_ON;	//温度高了打开制冷
//			if(HANDLE_PROBE_TEMP <= HANDLE_PROBE_COLD_LOWER_LIMITS[HANDLE_PROBE_COLE_GEAR])COLD_HANDLE_PROBE_OFF;//温度低了关闭制冷
//		}else{COLD_HANDLE_PROBE_OFF;}
//
//	}while(1);
//	over_main_xs_set_pulse:
//	_nop_();
//}
//
//void dis_set_pulse_fast_pulse_time(void)
//{
//	DIS_FONT_WEI_NUMBER_CM(Pic_SET_PULSE,1,0x5C,0xF4,0x04,FAST_PULSE_TIME,3,928,385);
//}
// 
//void dis_set_pulse_normal_pulse_time(void)
//{
//	DIS_FONT_WEI_NUMBER_CM(Pic_SET_PULSE,1,0x5C,0xF4,0x04,NORMAL_PULSE_TIME,3,928,575);
//} 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 