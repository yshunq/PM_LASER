#include "config.h"

void jump_interface(void)
{
	while(1)
	{
		KEY_YES = 0;
		switch(INTERFACE)
		{
			case  PAGE_LOADING:
				main_xs_loading();
				break;
			case  PAGE_TQ_WORK:
				main_xs_tq_work();
				break;
			case  PAGE_ADVANCED_SETTINGS:
				main_xs_advanced_settings();
				break;
			case  PAGE_ADJUST_POWER:
				main_xs_adjust_power();
				break;	 
//			/*case  PAGE_DIODE_LASER_WORK:
//				main_xs_diode_laser_work();
//				break;
//		  	case  PAGE_REF_VOL:
//				main_xs_ref_vol();
//				break;
////			case  PAGE_LANGUAGE:
////				main_xs_language();
////				break;
//			case  PAGE_WATER_SETTING:
//				main_xs_water_setting();
//				break;
//			case  PAGE_HANDLE_SETTING:
//				main_xs_handle_setting();
//				break;
//			case  PAGE_FLOW_SETTING:
//				main_xs_flow_setting();
//				break;
//			case  PAGE_TOTAL_TIME_SETTING:
//				main_xs_total_time_setting();
//				break;
//			case  PAGE_SOUND_SETTING:
//				main_xs_sound_flag_setting();
//				break;
//			case  PAGE_WRITE_HANDLE:
//				main_xs_write_handle();
//				break;
//			case  PAGE_WRITE_MACHINES_ID:
//				main_xs_write_machines_id();
//				break;
//			case  PAGE_CHOOSE_MODE:
//				main_xs_choose_mode();
//				break;
//			case  PAGE_LOGO_FLAG:
//				main_xs_logo_flag();
//				break;			
//			case  PAGE_SET_PULSE:
//				main_xs_set_pulse();
//				break;
//			case  PAGE_CHECK_HANDLE:  
//				main_xs_check_handle();
//			    break;
			
			default:
		     break; 
		} 
	}
}



