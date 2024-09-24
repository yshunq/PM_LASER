#ifndef _CONFIG_H
#define _CONFIG_H

//-----数据类型定义-----//
typedef  signed    char    int8;    // 8位有符号整型数
typedef  signed    int     int16;   //16位有符号整型数
typedef  signed    long    int32;   //32位有符号整型数
typedef  unsigned  char    uint8;   // 8位无符号整型数
typedef  unsigned  int     uint16;  //16位无符号整型数
typedef  unsigned  long    uint32;  //32位无符号整型数

typedef  unsigned  char    u8;   // 8位无符号整型数
typedef  unsigned  int     u16;  //16位无符号整型数
typedef  unsigned  long    u32;  //32位无符号整型数

//-----通用头文件-----//
#include <STC8A.h>
#include <intrins.h>
#include "uart.h"
#include "stc8aid.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include "all_extern_ram.h"
#include "all_fonction.h"
#include "24cxx.h"
#include "ads7843.h"
#include "display.h"
#include "cut_tq_work.h"
#include "dis_tq_work.h"
#include "eeprom_data.h"
#include "other.h"


#define Edition1	1
#define Edition2	0

//#define Picture_Language 30*LANGUAGE

#define DIS_ALL		0
#define DIS_PART	1

//-----全局运行参数定义-----//
#define FOSC   33177600L  //系统主时钟频率，即振荡器频率÷12
#define	BRT1	(65536 - FOSC / 115200 / 4)
#define	BRT2	(65536 - FOSC / 9600 / 4)
#define	BRT3	(65536 - FOSC / 115200 / 4)

#define WL585NM		1
#define WL650NM		2
#define WL532NM		3
#define WL1064NM	4
#define WL1320NM	5

#define WATER_ERROR	1

//--------------------------------------------------//
#define  PAGE_LOADING						0
#define  PAGE_TQ_WORK						1
#define  PAGE_ADVANCED_SETTINGS				2
#define  PAGE_ADJUST_POWER					3


//--------------------------------------------------//
#define  Pic_LOADING						1
#define  Pic_TQ_WORK						2
#define  Pic_TQ_WORK_DOWN					3
#define  Pic_TQ_WORK_CUT1					4
#define  Pic_TQ_WORK_CUT2					5
#define  Pic_ADVANCED_SETTINGS				6
#define  Pic_WATERWAY_ERROR					7
#define  Pic_TEMP_ERROR						8
#define  Pic_NTC_OPEN_CIRCUIT				9
#define  Pic_NTC_SHORT_CIRCUIT				10
#define  Pic_SIMMER_ERROR					11
#define  Pic_ADJUST_POWER					12



//--------------------------------------------------//
#define  ADH_TQ_TOTAL_TIME		0
#define  ADM_TQ_TOTAL_TIME		1
#define  ADL_TQ_TOTAL_TIME		2
#define  AD_MAX_WATER_TEMP		3
#define  AD_START_TQ_SET_PWM	4  //4 - 15				
//#define  AD_TQ_SET_TIME			16








#define  XIANG1();		BUZZER_ON;BUZZER_COUNT = 80;

#define  BUZZER_ON		P10 = 0
#define  BUZZER_OFF		P10 = 1

#define  YAG_PRECOMBUSTION_ON		P26 = 0
#define  YAG_PRECOMBUSTION_OFF		P26 = 1

#define  YAG_CHARGE_ON				P23 = 0
#define  YAG_CHARGE_OFF				P23 = 1

#define  YAG_SET_ON		P22 = 0;
#define  YAG_SET_OFF	P22 = 1;

#define  TQ_SECOND_PULSE_ON		P36 = 0
#define  TQ_SECOND_PULSE_OFF	P36 = 1

#define  TQ_HIGH_VOLTAGE_ON		P51 = 0
#define  TQ_HIGH_VOLTAGE_OFF	P51 = 1

#define  TQ_SINGLE_PULSE_ON		P50 = 1
#define  TQ_DOUBLE_PULSE_ON		P50 = 0

#define  MOTOR_LEFT_ON		P13 = 1;P14 = 0
#define  MOTOR_RIGHT_ON		P13 = 0;P14 = 1
#define  MOTOR_STOP_ON		P13 = 0;P14 = 0




sbit CHECK_WATERWAY = P5^2;
sbit CHECK_PRECOMBUSTION_KEY = P2^7;
sbit YAG_SRART_KEY = P4^7;





#endif