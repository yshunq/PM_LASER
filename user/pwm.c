#include "pwm.h"

void yag_voltage_pwm(u16 dat,u16 val)//P0.6
{
	PWMCFG45 = 0x00;	//启动PWM0模块
	PWMSET |= 0x10;		//使能PWM0模块
	P_SW2 = 0x80;
	
	PWM4CKS = 0x00;		//PWM0时钟为系统时钟
	
	PWM4CH = (FOSC/dat)>>8;		//设置PWM0周期为 FOSC/dat 个PWM时钟
	PWM4CL = FOSC/dat;			//如dat等于2000，则FOSC/2000 = 5529 = 1599H
	
	PWM46T1H = val >> 8;;		//在计数值为T1值的地方PWM00通道输出低电平
	PWM46T1L = val;

	PWM46T2H = 0x00;	//在计数值为T2值的地方PWM00通道输出高电平
	PWM46T2L = 0x00;

	PWM46CR = 0x80;			//使能PWM00输出
	P_SW2 = 0x00;			
	PWMCFG45 = 0x01;		//启动PWM0模块
}
//PWM输出频率 = 11059200/PWM0C
/*
void open_pwm(void)
{
	PWMCFG01 = 0x01;		//使能PWM0模块
}
*/
void yag_close_pwm(void)
{
	PWMCFG45 = 0x00;
	P46 = 0;
}
//------------------------------------------------------//
void laser_light_pwm(u16 dat,u16 val)//P0.6
{
	PWMCFG01 = 0x00;	//启动PWM0模块
	PWMSET |= 0x01;		//使能PWM0-0x01  PWM1-0x02  PWM3-0x04  PWM4-0x08  PWM5-0x10
	P_SW2 = 0x80;
	
	PWM0CKS = 0x00;		//PWM0时钟为系统时钟
	
	PWM0CH = (FOSC/dat)>>8;		//设置PWM0周期为 FOSC/dat 个PWM时钟
	PWM0CL = FOSC/dat;			//如dat等于2000，则FOSC/2000 = 5529 = 1599H
	
	PWM06T1H = 0x00;		//在计数值为T1值的地方PWM00通道输出低电平
	PWM06T1L = 0x00;

	PWM06T2H = val >> 8;	//在计数值为T2值的地方PWM00通道输出高电平
	PWM06T2L = val;

	PWM06CR = 0x80;			//使能PWM00输出
	P_SW2 = 0x00;			
	PWMCFG01 = 0x01;		//启动PWM0模块
}
//PWM输出频率 = 11059200/PWM0C
/*
void open_pwm(void)
{
	PWMCFG01 = 0x01;		//使能PWM0模块
}
*/
void laser_light_close_pwm(void)
{
	PWMCFG01 = 0x00;
	P06 = 1;
}



