#include "config.h"
#include "all_main_ram.h"

//PnM1.x    PnM0.x    Pn.x口工作模式
//  0         0       准双向口
//  0         1       推挽输出
//  1         0       高阻输入
//  1         1       开漏输出



void main(void)
{
	P7 = 0xff;
	P0M0 = 0x4A;
	P0M1 = 0x15;
	P1M0 = 0x3B;
	P1M1 = 0x04;
	P2M0 = 0x6E;
	P2M1 = 0x81;
	P3M0 = 0xB2;
	P3M1 = 0x4D;
	P4M0 = 0x4F;
	P4M1 = 0xB0;
	P5M0 = 0x13;
	P5M1 = 0x04;
	
	/*//-----设置外部晶振-----//
	P_SW2 |= 0x80;
	XOSCCR = 0xC0;
	while (!(XOSCCR & 1));
	CLKDIV = 0x00;
	CKSEL = 0x01;
	P_SW2 &= ~0x80;	*/
	
	//IT1 = 0;	//使能INT1上升沿和下降沿中断
	//IT1 = 1;	//使能INT1下降沿中断
	//EX1 = 1;	//使能INT1中断
	
	Timer0_Init();//1ms
	Timer1_Init();
	//Uart2Init();
	Uart3Init();//设置波特率115200 定时器2
	ADC_Init();

	INTCLKO = EX2;  //使能INT2中断

	EA = 1;		//总中断
	
	START_STOP_FLAG = 1;
	TQ_WORK_FLAG = 1;

	YAG_PRECOMBUSTION_OFF;
	YAG_CHARGE_OFF;
	YAG_SET_OFF;
	yag_close_pwm();
	laser_light_close_pwm();

	TQ_SECOND_PULSE_OFF;//第二脉冲不输出
	TQ_SINGLE_PULSE_ON;//单脉冲模式
	TQ_HIGH_VOLTAGE_OFF;
	MOTOR_STOP_ON;//电机停止
	
	delay_ms(2000);
	TX1_OUT_OVER();//帧结束符
	
	read_tq_total_time();
	read_max_water_temp();
	read_all_tq_set_pwm();
//	read_tq_set_time();
	TQ_SET_TIME = 1;

	XIAN_FLAG = 0;
	
	WAVELENGTH = WL585NM;
	TQ_FREQUENCY_GEAR = 2;
	TQ_ENERGY_GEAR = 100;
 	//TQ_TOTAL_TIME= 8888888;
	TQ_CURE_TIME = 0;
	TQ_SPOT_SIZE = 5;
	TQ_LASER_LEVEL = 5;
	
  	while(1)
	{
    	INTERFACE = PAGE_LOADING;
		jump_interface();
//		TQ_SECOND_PULSE_ON;
//		TQ_HIGH_VOLTAGE_ON;
//		TQ_SINGLE_PULSE_ON;
//		delay_ms(100);
//		TQ_SECOND_PULSE_OFF;
//		TQ_HIGH_VOLTAGE_OFF;
//		TQ_DOUBLE_PULSE_ON;
//		delay_ms(100);
	}
}

void INT2_Isr() interrupt 10
{
	static u8 state_flag = 0;
	static u8 time = 0;
	static u8 value = 0;
	static u8 temp = 0;
	static u8 count = 0;
	static u8 received_data = 0;

	if(state_flag == 0){//等待接收引导码
		if(TQ_SPOT_COUNT > 16 && TQ_SPOT_COUNT < 24){//大于8ms  小于12ms
			state_flag = 1;
			received_data = 0;
			time = 0;		
		}	
	}else{
		if(TQ_SPOT_COUNT < 5){//间距小于2.5ms
			received_data <<= 1;
			received_data++;
		}else if(TQ_SPOT_COUNT < 7){//间距小于3.5ms
			received_data <<= 1;
			//received_data++;
		}else{//报错
			state_flag = 0;
			received_data = 0;
		}
		time++;
		if(time == 4){
			switch(received_data){
				case 0x04:value = 1;break;
				case 0x0E:value = 2;break;
				case 0x0C:value = 3;break;
				case 0x0D:value = 4;break;
				case 0x09:value = 5;break;
				case 0x0B:value = 6;break;
				case 0x0A:value = 7;break;
				case 0x08:value = 8;break;
				case 0x00:value = 9;break;
				case 0x01:value = 10;break;
			}
			if(temp == value){
				count++;
				if(count > 5){
					TQ_SPOT_SIZE = value;
					count = 0;
				}
			}else{
				count = 0;
			}
			temp = value;
			state_flag = 0;
			received_data = 0;
			time = 0;
		}
	}
	
	TQ_SPOT_COUNT = 0;		
}

//void INT1_Isr() interrupt 2 	TQ_SPOT_SIZE
//{
//	//INT1_COUNT++;
//}

