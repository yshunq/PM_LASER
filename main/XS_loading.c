#include "config.h"

const u8  code MAIN_KEY_KEEP_LOADING = 3;
const u16 code MAIN_KEEP_LOADING[]=
{
	0,1919,0,859,
	256,1919,860,1079,
	0,255,860,1079,
};

void main_xs_loading(void)
{
	u8 key;
	DIS_PICNUM(Pic_LOADING);
	do{
		delay_ms(1);
		if(KEY_YES!=0x00){
			ADS7843_KEY(); //扫描按键
			key=KEY_FANHUI(MAIN_KEY_KEEP_LOADING,MAIN_KEEP_LOADING); 
			switch(key){
				case 1:	//工作界面
				  	XIANG1();
				  	INTERFACE = PAGE_TQ_WORK;
					goto over_main_xs_loading;
					break;
				case 2:	//工作界面
				  	XIANG1();
				  	INTERFACE = PAGE_TQ_WORK;
					goto over_main_xs_loading;
					break;
				case 3:	//密码界面
				  	XIANG1();
				  	INTERFACE = PAGE_ADVANCED_SETTINGS;
					goto over_main_xs_loading;
					break;
			}KEY_YES = 0;
		}

//		if(timekeeping_100ms(1)){
//			timekeeping_100ms(0);
//			P40 = ~P40;
//		}
	}while(1);	
	over_main_xs_loading:
	_nop_();
}














// 