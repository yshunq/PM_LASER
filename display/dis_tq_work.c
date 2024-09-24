#include "dis_tq_work.h"

void dis_tq_work_frequency_gear(u8 dis)
{
	static u8 buff = 0;
	DIS_FONT_WEI_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x07,2,dis,TQ_FREQUENCY_GEAR,buff,298,742);
	buff = TQ_FREQUENCY_GEAR;
}

void dis_tq_work_energy_gear(u8 dis)
{
	static u16 buff = 0;
	DIS_FONT_WEI_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x07,4,dis,TQ_ENERGY_GEAR,buff,1525,742);
	buff = TQ_ENERGY_GEAR;
}

void dis_tq_work_total_time(u8 dis)
{
	static u32 buff = 0;
	DIS_FONT_WEI_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x03,7,dis,TQ_TOTAL_TIME,buff,290,965);
	buff = TQ_TOTAL_TIME;
}

void dis_tq_work_cure_time(u8 dis)
{
	static u16 buff = 0;
	DIS_FONT_WEI_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x03,5,dis,TQ_CURE_TIME,buff,592,965);
	buff = TQ_CURE_TIME;
} 

void dis_tq_work_spot_size(u8 dis)
{
	static u8 buff = 0;
	DIS_FONT_WEI_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x07,2,dis,TQ_SPOT_SIZE,buff,924,735);
	buff = TQ_SPOT_SIZE;
}

void dis_tq_work_energy_density(u8 dis)
{
	static u32 buff = 0;
	u32 temp,square,power;
	temp = TQ_SPOT_SIZE;
	square = 314*temp*temp;

	temp = TQ_ENERGY_GEAR;
	power = temp*1000/square;

	temp = TQ_FREQUENCY_GEAR;
	power = temp*power;

	DIS_FONT_WEI_DECIMAL_TWO_VALUE(Pic_TQ_WORK,1,0xff,0xff,0x09,6,dis,power,buff,815,315);
	buff = power;
}

void dis_tq_work_temp(u8 temp)
{
	DIS_DEL_DIS(Pic_TQ_WORK,72,0,96,16,72,0);
	if(temp >= 254){
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,temp,3,9*8,0);
	}else if(temp <= 10){
		DIS_FONT_C(0xff,0xff,1,0x01,72,0,"-");
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,10-temp,2,10*8,0);
	}else{
		DIS_FONT_WEI_NUMBER_CM(Pic_TQ_WORK,0,0xff,0xff,0x01,temp-10,2,9*8,0);	
	}	
}




