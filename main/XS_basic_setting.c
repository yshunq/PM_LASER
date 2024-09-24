/*#include "config.h"

const u8  MAIN_KEY_BASIC_SETTING = 4;
const u16 MAIN_BASIC_SETTING[]=
{
	171,300,663,822,
	789,958,663,822,
	918,1061,5,113,
	 53, 173,5,113,
};
 
void main_xs_basic_setting(void)
{
	u8 key;
	DIS_PICNUM(Pic_BASIC_SETTING);
	//DIS_FONT_WEI_NUMBER_CM(0,1,0xff,0xff,0x03,LANGUAGE,7,0,0);
	do{
		delay_ms(1);
		if(KEY_YES!=0x00)
		{
			ADS7843_KEY(); //扫描按键
			key=KEY_FANHUI(MAIN_KEY_BASIC_SETTING,MAIN_BASIC_SETTING); 
			switch(key)
			{
				case 1:  //
					DIS_DEL_DIS(Pic_BASIC_SETTING_DOWN,171,663,300,822,171,663);
					XIANG1();
					if(LANGUAGE > 0)LANGUAGE--;
					else{LANGUAGE = 1;}
					write_language();
					goto over_main_xs_basic_setting;
					break;
				case 2:  //
					DIS_DEL_DIS(Pic_BASIC_SETTING_DOWN,789,663,958,822,789,663);
					XIANG1();
				  if(LANGUAGE < 1)LANGUAGE++;
					else{LANGUAGE = 0;}
					write_language();
					goto over_main_xs_basic_setting;
					break;
				case 3:  //
					DIS_DEL_DIS(Pic_BASIC_SETTING_DOWN,918,5,1061,113,918,5);
				  XIANG1();
				  INTERFACE = PAGE_ADVANCED_SETTINGS;
					goto over_main_xs_basic_setting;
					break;
				case 4:
					DIS_DEL_DIS(Pic_BASIC_SETTING_DOWN,53,5,173,113,53,5);
					XIANG1();
				  INTERFACE = PAGE_CHOOSE;
					goto over_main_xs_basic_setting;
					break;
			}
			KEY_YES = 0;
		}
		
		WATER_TEMP = Get_ADC_RES_WATER_TEMP();//获取水温度
		if(WATER_TEMP != 255)
		{
			if(WATER_TEMP >= WATER_COLD_UPPER_LIMITS)COLD_WATER_ON;	//温度高了打开制冷
			if(WATER_TEMP <= WATER_COLD_LOWER_LIMITS)COLD_WATER_OFF;//温度低了关闭制冷
		}else{COLD_WATER_OFF;}
		
		if(HANDLE_PROBE_TEMP != 255)//手柄温度
		{
			if(HANDLE_PROBE_TEMP >= HANDLE_PROBE_COLD_UPPER_LIMITS)COLD_HANDLE_PROBE_ON;	//温度高了打开制冷
			if(HANDLE_PROBE_TEMP <= HANDLE_PROBE_COLD_LOWER_LIMITS)COLD_HANDLE_PROBE_OFF;//温度低了关闭制冷
		}else{COLD_HANDLE_PROBE_OFF;}
		
	}while(1);
	over_main_xs_basic_setting:
	_nop_();
}
*/
 
 
 
 
 
 
 
 
 
 
 
 