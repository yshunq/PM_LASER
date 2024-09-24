#include "timer.h"
#include "config.h"

unsigned long DELAY_MS = 0;
unsigned long SYSTEM_COUNT = 0;

void delay_ms(u32 ms)
{
  	DELAY_MS = 0;
	while(DELAY_MS < ms);
}

void Timer0_Init(void)
{
    TMOD = 0x00;                                //模式0
    TH0=(65536-(FOSC/(12000000/1000)))/256;			//65536-(MAIN_Fosc/(12000000/1000))
  	TL0=(65536-(FOSC/(12000000/1000)))%256;
    TR0 = 1;                                    //启动定时器
    ET0 = 1;                                    //使能定时器中断
}

void TM0_Isr() interrupt 1 using 1
{
	DELAY_MS++;
	SYSTEM_COUNT++;

	if(BUZZER_COUNT > 0){
		if(BUZZER_COUNT == 1)BUZZER_OFF;
		BUZZER_COUNT--; 
	}

	if(TQ_WORK_FLAG == 0){
   		TQ_WORK_COUNT_TT++;
		if(TQ_WORK_COUNT_TT >= TQ_WORK_CYCLE){
			TQ_WORK_COUNT_TT = 0;
			TQ_ADD_FLAG = 0;
			TQ_SET_COUNT = TQ_SET_TIME + 1;
			YAG_SET_ON;
		}
	}else{
		TQ_WORK_COUNT_TT = 1000;
	}

	if(TQ_SET_COUNT > 0){
		if(TQ_SET_COUNT == 1){
			YAG_SET_OFF;
		}
		TQ_SET_COUNT--;
	}

}

void Timer1_Init(void)//500us
{
    TMOD = 0x00;                                //模式0
    TH1=(65536-(FOSC/(12000000/500)))/256;		//65536-(MAIN_Fosc/(12000000/1000))
  	TL1=(65536-(FOSC/(12000000/500)))%256;
    TR1 = 1;                                    //启动定时器
    ET1 = 1;                                    //使能定时器中断
}

void TM1_Isr() interrupt 3
{
	TQ_SPOT_COUNT++;	
}

//u32 system_count_retrun(void)
//{
//	return SYSTEM_COUNT;	
//}

u8 timekeeping_100ms(u8 clear)//0时清零 
{	
	static u32 pressStartTime = 0;
	static u32 lastClickTime = 0;
	pressStartTime = SYSTEM_COUNT;
	if(clear == 0)lastClickTime = pressStartTime;
	if((pressStartTime - lastClickTime) > 100){
		return 1;	
	}
	return 0;
}



