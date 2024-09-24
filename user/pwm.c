#include "pwm.h"

void yag_voltage_pwm(u16 dat,u16 val)//P0.6
{
	PWMCFG45 = 0x00;	//����PWM0ģ��
	PWMSET |= 0x10;		//ʹ��PWM0ģ��
	P_SW2 = 0x80;
	
	PWM4CKS = 0x00;		//PWM0ʱ��Ϊϵͳʱ��
	
	PWM4CH = (FOSC/dat)>>8;		//����PWM0����Ϊ FOSC/dat ��PWMʱ��
	PWM4CL = FOSC/dat;			//��dat����2000����FOSC/2000 = 5529 = 1599H
	
	PWM46T1H = val >> 8;;		//�ڼ���ֵΪT1ֵ�ĵط�PWM00ͨ������͵�ƽ
	PWM46T1L = val;

	PWM46T2H = 0x00;	//�ڼ���ֵΪT2ֵ�ĵط�PWM00ͨ������ߵ�ƽ
	PWM46T2L = 0x00;

	PWM46CR = 0x80;			//ʹ��PWM00���
	P_SW2 = 0x00;			
	PWMCFG45 = 0x01;		//����PWM0ģ��
}
//PWM���Ƶ�� = 11059200/PWM0C
/*
void open_pwm(void)
{
	PWMCFG01 = 0x01;		//ʹ��PWM0ģ��
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
	PWMCFG01 = 0x00;	//����PWM0ģ��
	PWMSET |= 0x01;		//ʹ��PWM0-0x01  PWM1-0x02  PWM3-0x04  PWM4-0x08  PWM5-0x10
	P_SW2 = 0x80;
	
	PWM0CKS = 0x00;		//PWM0ʱ��Ϊϵͳʱ��
	
	PWM0CH = (FOSC/dat)>>8;		//����PWM0����Ϊ FOSC/dat ��PWMʱ��
	PWM0CL = FOSC/dat;			//��dat����2000����FOSC/2000 = 5529 = 1599H
	
	PWM06T1H = 0x00;		//�ڼ���ֵΪT1ֵ�ĵط�PWM00ͨ������͵�ƽ
	PWM06T1L = 0x00;

	PWM06T2H = val >> 8;	//�ڼ���ֵΪT2ֵ�ĵط�PWM00ͨ������ߵ�ƽ
	PWM06T2L = val;

	PWM06CR = 0x80;			//ʹ��PWM00���
	P_SW2 = 0x00;			
	PWMCFG01 = 0x01;		//����PWM0ģ��
}
//PWM���Ƶ�� = 11059200/PWM0C
/*
void open_pwm(void)
{
	PWMCFG01 = 0x01;		//ʹ��PWM0ģ��
}
*/
void laser_light_close_pwm(void)
{
	PWMCFG01 = 0x00;
	P06 = 1;
}



