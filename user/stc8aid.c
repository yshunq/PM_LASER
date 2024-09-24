
#include "STC8AID.h"

char	*ID;

/******************************************************************************/
// 函数名称：void Read_ID(void)
// 输入参数： 
// 输出参数：
// 函数功能：读出芯片全球唯一的ID，在ROM的存放地址为0XFDF9H--- 0xFDFFH 
/******************************************************************************/
/*void Read_ID_fromROM(void)
{
	char i;

	ID = (char code *)0xfdf9;	// STC8A8K64S4A10
//	ID = (char code *)0xeff9;	// STC8A8K60S4A10
//	ID = (char code *)0x7ff9;	// STC8A8K32S4A10
//	ID = (char code *)0x3ff9;	// STC8A8K16S4A10

	for (i=0; i<7; i++)
	{
		UartSend(ID[i]);
	}
}
*/
/******************************************************************************/
// 函数名称：void Read_ID(void)
// 输入参数： 
// 输出参数：
// 函数功能：读出芯片全球唯一的ID，在ROM的存放地址为0XF1-0XF7
/******************************************************************************/
/*void Read_ID_fromRAM(void)
{
	uint8 i;

	ID = (char idata *)0xf1;

	for (i=0; i<7; i++)
	{
		UartSend(ID[i]);
	}
}
*/



