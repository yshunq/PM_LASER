
#ifndef __UART_H
#define __UART_H

#include "config.h"

extern bit uart3_busy;
extern u8 rx3_ram;
extern u8 rx3_data[20];

extern bit uart2_busy;
extern u8 rx2_ram;
extern u8 rx2_gs;
extern u8 rx2_length;
extern u8 rx2_data[20];

void Uart3Init(void);
void Uart3Send(u8 dat);

void Uart2Init(void);
void Uart2Send(uint8 dat);
void tx2_out_3(u8 dat1,u8 dat2,u8 dat3);
void tx2_out_4(u8 dat1,u8 dat2,u8 dat3,u8 dat4);
void tx2_out_5(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5);
void tx2_out_6(u8 dat1,u8 dat2,u8 dat3,u8 dat4,u8 dat5,u8 dat6);

#endif
