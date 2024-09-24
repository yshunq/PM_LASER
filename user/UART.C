#include "uart.h"

bit uart3_busy;
u8 rx3_ram;
u8 rx3_data[20];

bit uart2_busy;
u8 rx2_ram;
u8 rx2_gs;
u8 rx2_length;
u8 rx2_data[20];

//----------------------------------------------------------------------------------------------------//
void Uart3Init(void)
{
	P0M1 &= ~(1 << 1);	//P01推挽输出
  	P0M0 |= (1 << 1);
	P_SW2 &= ~0x02;            //S3_S0=0 (P0.0/RxD3, P0.1/TxD3)
	//P_SW2 |= 0x02;           //S3_S0=1 (P5.0/RxD3_2, P5.1/TxD3_2)
	
	S3CON = 0x50;
	T3L = BRT3;
	T3H = BRT3 >> 8;
	T4T3M = 0x0a;
	uart3_busy = 0;
	rx3_ram=10;
	IE2 |= 0x08;
}

void Uart3Send(u8 dat)
{
	while (uart3_busy);
	uart3_busy = 1;
	S3BUF = dat;
}

void Uart3Isr() interrupt 17
{
	static u8 flag = 0;
	u8 dat;
	if (S3CON & 0x02)
	{
		S3CON &= ~0x02;
		uart3_busy = 0;
	}
	if (S3CON & 0x01)
	{
		S3CON &= ~0x01;
		dat = S3BUF;
		switch(rx3_ram)
    {
			case 10:if(dat==0xAA)rx3_ram--;else{rx3_ram=10;flag=0x00;}break;
			case  9:
				switch(dat)
				{
					case 0x73:flag=0xff; //有按键
						break;
					case 0x72:flag=0x00; //没按键
						KEY_YES=flag;
						break;
	      }
				rx3_ram--;
				break; 
			case  8:KEY_XH=dat; rx3_ram--; break;
			case  7:KEY_XL=dat; rx3_ram--; break;
			case  6:KEY_YH=dat; rx3_ram--; break;
			case  5:KEY_YL=dat; rx3_ram--; KEY_YES = flag; break;
			case  4:rx3_ram--; break;
			case  3:rx3_ram--; break;
			case  2:rx3_ram--; break;
			case  1:rx3_ram=10;break;
			default:rx3_ram=10;flag=0x00;break; 		   		   		        
    }
	}
}


//------------------------------------------------------------------------------------------//
/*void UART2_IOPORT_CHANGE(void)
{
	//P1M1 &= ~(1 << 1);	//P11推挽输出
	//P1M0 |= (1 << 1);
		
	P_SW2 &= ~0x01;			//RXD/P1.0, TXD/P1.1
	//P_SW2 |= 0x01;    	//RXD_2/P4.6, TXD_2/P4.7
}
*/
//----------------------------------------------------------------------------//
// 函数名称：uart2Init 
// 输入参数：无 
// 输出参数：无 
// 函数功能：设置好定时器2的工作模式 
//----------------------------------------------------------------------------//
//void Uart2Init(void)
//{
//	P_SW2 &= ~0x01;			//RXD/P1.0, TXD/P1.1
//	
//	S2CON |= 0x10;
//	T2L = BRT2;
//	T2H = BRT2 >> 8;
//	AUXR |= 0x14;
//	uart2_busy = 0;
//	rx2_ram=100;
//	rx2_gs=0x00;
//	IE2 |= 0x01;
//}
//
////----------------------------------------------------------------------------//
//// 函数名称：uartSendData 
//// 输入参数：ucData: 发送字节 
//// 输出参数：无 
//// 函数功能：使用串口发送一个字节数据 
////----------------------------------------------------------------------------//
//void Uart2Send(uint8 dat)
//{
//    while (uart2_busy);
//    uart2_busy = 1;
//    S2BUF = dat;
//}
//
////----------------------------------------------------------------------------//
//// 函数名称： 
//// 输入参数：无 
//// 输出参数：无 
//// 函数功能：串口0服务函数 
////----------------------------------------------------------------------------//
//void Uart2Isr() interrupt 8
//{
//	u8 value,db;
//	if (S2CON & S2TI){
//		S2CON &= ~S2TI;	//清除S2TI位
//		uart2_busy = 0;
//	}
//	if (S2CON & S2RI){
//		S2CON &= ~S2RI;         //清除S2RI位
//		value = S2BUF;
//		switch(rx2_ram){
//			case 100:if(value==0xAA)rx2_ram--;else{rx2_ram=100;rx2_gs=0x00;}break;
//			case  99:if(value==0xAA)rx2_ram--;else{rx2_ram=100;rx2_gs=0x00;}break;
//			case  98:if(value < 20){rx2_length=value;rx2_ram=value;rx2_ram--;}else{rx2_ram=100;rx2_gs=0x00;}break;	
//			default:
//				if(rx2_ram==0x00){//接收完成
//					rx2_data[rx2_gs]=value;
//					switch(rx2_data[0]){
//						/*case 0x10:
//							SHOTS_TOTAL = rx2_data[1];
//							SHOTS_TOTAL <<= 8;
//							SHOTS_TOTAL |= rx2_data[2];
//							SHOTS_TOTAL <<= 8;
//							SHOTS_TOTAL |= rx2_data[3];
//							break;*/
//						case 0x51:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2] + rx2_data[3] + rx2_data[4] + rx2_data[5] + rx2_data[6];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[7] == db && rx2_data[8] == 0xFE){
//								RX_PROBE_MODE = rx2_data[2];
//								RX_PROBE_ID = rx2_data[3];
//								RX_PROBE_TOTAL = rx2_data[4];
//								RX_PROBE_TOTAL <<= 8;
//								RX_PROBE_TOTAL |= rx2_data[5];
//								RX_PROBE_TOTAL <<= 8;
//								RX_PROBE_TOTAL |= rx2_data[6];	 
//							}break;
//						case 0x53:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[3] == db && rx2_data[4] == 0xFE){
//								HANDLE_PROBE_TEMP = rx2_data[2];	 
//							}break;
//						case 0x60:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[3] == db && rx2_data[4] == 0xFE){
//								LCD_KEY_RETURN_VALUE = rx2_data[2];	 
//							}break;
//						case 0x70:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[3] == db && rx2_data[4] == 0xFE){
//								HANDLE_KEY_FLAG = ~rx2_data[2];	 
//							}break;
//						case 0x89:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2] + rx2_data[3] + rx2_data[4] + rx2_data[5];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[6] == db && rx2_data[7] == 0xFE){
//								RX_ADD_FINISH_FLAG = rx2_data[2];
//								RX_PROBE_TOTAL = rx2_data[3];
//								RX_PROBE_TOTAL <<= 8;
//								RX_PROBE_TOTAL |= rx2_data[4];
//								RX_PROBE_TOTAL <<= 8;
//								RX_PROBE_TOTAL |= rx2_data[5];	 
//							}break;
//						case 0xC1:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2] + rx2_data[3];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[4] == db && rx2_data[5] == 0xFE){
//								RX_Edition[0] = rx2_data[2];
//								RX_Edition[1] = rx2_data[3];	 
//							}break; 
//						case 0xCD:
//							db = 0xAA + 0xAA + rx2_length + rx2_data[0] + rx2_data[1] + rx2_data[2] + rx2_data[3] + rx2_data[4];
//							if(rx2_data[1] == DEVICE_TYPE && rx2_data[5] == db && rx2_data[6] == 0xFE){
//								AHANDLE_YEAR = rx2_data[2];
//								AHANDLE_MONTHS = rx2_data[3];
//								AHANDLE_DAY = rx2_data[4];	 
//							}break; 
//					}
//					rx2_ram=100;
//					rx2_gs =0x00;
//				}else{
//					rx2_data[rx2_gs]=value;
//					rx2_ram--;
//					rx2_gs++;
//				}
//				break; 		   		   		        
//		}
//	}
//}
//
//void tx2_out_3(u8 dat1,u8 dat2,u8 dat3)
//{
//	u8 temp;
//	temp = 0xAA + 0xAA +0x05 + dat1 + dat2 + dat3;
//	Uart2Send(0xAA);
//	Uart2Send(0xAA);
//	Uart2Send(0x05);
//	Uart2Send(dat1);
//	Uart2Send(dat2);
//	Uart2Send(dat3);
//	Uart2Send(temp);
//	Uart2Send(0xFE);
//}
//
//void tx2_out_4(u8 dat1,u8 dat2,u8 dat3,u8 dat4)
//{
//	u8 temp;
//	temp = 0xAA + 0xAA +0x06 + dat1 + dat2 + dat3 + dat4;
//	Uart2Send(0xAA);
//	Uart2Send(0xAA);
//	Uart2Send(0x06);
//	Uart2Send(dat1);
//	Uart2Send(dat2);
//	Uart2Send(dat3);
//	Uart2Send(dat4);
//	Uart2Send(temp);
//	Uart2Send(0xFE);
//}
//
//void tx2_out_5(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5)
//{
//	u8 temp;
//	temp = 0xAA + 0xAA +0x07 + dat1 + dat2 + dat3 + dat4 + dat5;
//	Uart2Send(0xAA);
//	Uart2Send(0xAA);
//	Uart2Send(0x07);
//	Uart2Send(dat1);
//	Uart2Send(dat2);
//	Uart2Send(dat3);
//	Uart2Send(dat4);
//	Uart2Send(dat5);
//	Uart2Send(temp);
//	Uart2Send(0xFE);
//}
//
//void tx2_out_6(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5,u8 dat6)
//{
//	u8 temp;
//	temp = 0xAA + 0xAA +0x08 + dat1 + dat2 + dat3 + dat4 + dat5 + dat6;
//	Uart2Send(0xAA);
//	Uart2Send(0xAA);
//	Uart2Send(0x08);
//	Uart2Send(dat1);
//	Uart2Send(dat2);
//	Uart2Send(dat3);
//	Uart2Send(dat4);
//	Uart2Send(dat5);
//	Uart2Send(dat6);
//	Uart2Send(temp);
//	Uart2Send(0xFE);
//}
















