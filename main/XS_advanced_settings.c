#include "config.h"

const u8  code MAIN_KEY_ADIN1 = 14;
const u16 code MAIN_ADIN1[]=
{
	700,783,479,563,
	807,890,479,563,
	914,997,479,563,
	1021,1104,479,563,
	1128,1211,479,563,
	
	700,783,598,682,
	807,890,598,682,
	914,997,598,682,
	1021,1104,598,682,
	1128,1211,598,682,

	778, 1072, 350, 436, //清零
	803,  923, 710, 779, //返回
	1086, 1118,377,409, //删除
	995, 1115, 710, 779, //确认
};

void dis_adv_password(u8 wei);
u8 comparison_password(u8 wei,u8 *buf);
void dis_version(void);

void main_xs_advanced_settings(void)//显示高级界面
{
	u8 key,wei,adv_psw[6];
	DIS_PICNUM(Pic_ADVANCED_SETTINGS); //显示高级设置页面
	adv_psw[0] = 0;
	adv_psw[1] = 0;
	adv_psw[2] = 0;
	adv_psw[3] = 0;
	adv_psw[4] = 0;
	adv_psw[5] = 0;
	wei = 0;
	dis_version();
	do{
		delay_ms(1);
		if(KEY_YES!=0x00){
			ADS7843_KEY(); //扫描按键
		  	key=KEY_FANHUI(MAIN_KEY_ADIN1,MAIN_ADIN1); 
	 	  	switch(key){
				case 1:if(wei < 6){XIANG1();adv_psw[wei] = 1;wei++;dis_adv_password(wei);}break;
        		case 2:if(wei < 6){XIANG1();adv_psw[wei] = 2;wei++;dis_adv_password(wei);}break;
        		case 3:if(wei < 6){XIANG1();adv_psw[wei] = 3;wei++;dis_adv_password(wei);}break;
				case 4:if(wei < 6){XIANG1();adv_psw[wei] = 4;wei++;dis_adv_password(wei);}break;
				case 5:if(wei < 6){XIANG1();adv_psw[wei] = 5;wei++;dis_adv_password(wei);}break;
				case 6:if(wei < 6){XIANG1();adv_psw[wei] = 6;wei++;dis_adv_password(wei);}break;
				case 7:if(wei < 6){XIANG1();adv_psw[wei] = 7;wei++;dis_adv_password(wei);}break;
				case 8:if(wei < 6){XIANG1();adv_psw[wei] = 8;wei++;dis_adv_password(wei);}break;
				case 9:if(wei < 6){XIANG1();adv_psw[wei] = 9;wei++;dis_adv_password(wei);}break;
				case 10:if(wei < 6){XIANG1();adv_psw[wei] = 0;wei++;dis_adv_password(wei);}break;
				case 11:            //清零
					XIANG1();
					adv_psw[0] = 0;
	   				adv_psw[1] = 0;
	   				adv_psw[2] = 0;
	   				adv_psw[3] = 0;
	   				adv_psw[4] = 0;
	   				adv_psw[5] = 0;
	   				wei = 0;
					dis_adv_password(wei);//显示密码
					break;
				case 12:            //返回
					XIANG1();
					INTERFACE = PAGE_LOADING;
					goto over_main_xs_advanced_settings;
					break;
				case 13:            //删除
					XIANG1();
					adv_psw[wei] = 0;
					if(wei > 0)wei--;
					dis_adv_password(wei);//显示密码
					break;
				case 14:            //确认
					XIANG1();
					comparison_password(wei,adv_psw);
					goto over_main_xs_advanced_settings;
					break;
			}
			KEY_YES = 0;//0连按 1单按
		}
	}while(1);
	over_main_xs_advanced_settings:
	_nop_();
}

void dis_adv_password(u8 wei)//显示密码
{
    u16 x,y;
	u8 add;
	x = 990;
	y = 370;
	add = 25;
	DIS_DEL_DIS(Pic_ADVANCED_SETTINGS,778,350,1072,436,778,350);//覆盖
	switch(wei){
       case  0:
	      DIS_DEL_DIS(Pic_ADVANCED_SETTINGS,778,350,1072,436,778,350);//覆盖
		  break; //0   //XH YH XL YLX
       case  1:
	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
		  break; //1
       case  2:
	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
		  DIS_FONT_C(0xff,0xff,1,0x05,x-add,y,"*");
		  break; //2
       case  3:
	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
		  DIS_FONT_C(0xff,0xff,1,0x05,x-add,y,"*");
 		  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add,y,"*");
   		  break; //3
       case  4:
	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
		  DIS_FONT_C(0xff,0xff,1,0x05,x-add,y,"*");
		  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add,y,"*");
  		  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add,y,"*");
		  break; //4
       case  5:
	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add,y,"*");
    	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add-add,y,"*");
 		  break; //5
       case  6:
   	      DIS_FONT_C(0xff,0xff,1,0x05,x,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add,y,"*");
       	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add,y,"*");
     	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add-add,y,"*");
       	  DIS_FONT_C(0xff,0xff,1,0x05,x-add-add-add-add-add,y,"*");
  		  break; //6
    }
 }


u8 comparison_password(u8 wei,u8 *buf)
{
	if(wei == 6){
		if(buf[0] == 1 && buf[1] == 7 && buf[2] == 1 && buf[3] == 2 && buf[4] == 1 && buf[5] == 2){
			
			TQ_TOTAL_TIME= 0;
			write_tq_total_time();
			
		  	return 0; 
		}
		if(buf[0] == 1 && buf[1] == 4 && buf[2] == 1 && buf[3] == 2 && buf[4] == 1 && buf[5] == 2){
			INTERFACE = PAGE_ADJUST_POWER;
		  	return 0; 
		}

		if(buf[0] == 1 && buf[1] == 2 && buf[2] == 3 && buf[3] == 3 && buf[4] == 2 && buf[5] == 1){
			if(XIAN_FLAG == 1)XIAN_FLAG = 0;
			else{XIAN_FLAG = 1;}
			INTERFACE = PAGE_LOADING;
		  	return 0; 
		}
		
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		buf[4] = 0;
		buf[5] = 0;
		wei = 0;
		dis_adv_password(wei);
  	}else{
		buf[0] = 0;
	  	buf[1] = 0;
	  	buf[2] = 0;
	  	buf[3] = 0;
	  	buf[4] = 0;
	  	buf[5] = 0;
	  	wei = 0;
	  	dis_adv_password(wei);
  	}
	return 1; 
}

void dis_version(void)
{
	u16 x,y,add;
	x = 2;
	y = 1062;
    add = 8;

	DIS_FONT_C(0xff,0xff,3,0x01,x,y,"AV ");
	x = 3*add + x;
	DIS_FONT_NUMBER_C(0xff,0xff,Edition1,0x01,x,y);
	x = add + x;
	DIS_FONT_C(0xff,0xff,1,0x01,x,y,".");
	x = add + x;
	DIS_FONT_NUMBER_C(0xff,0xff,Edition2,0x01,x,y);
}

