#include "ads7843.h"

void ADS7843_KEY(void) //ɨ�谴��
{
 	if(KEY_YES==0xff)
	{
	  ADS7843_X = KEY_XH;
		ADS7843_X <<= 8;
		ADS7843_X |= KEY_XL;
		
		ADS7843_Y = KEY_YH;
		ADS7843_Y <<= 8;
		ADS7843_Y |= KEY_YL;
	} 
}
/* 
void KEY_ON_Wait(void) //�ȴ��м�����
{
  KEY_YES=0x00;
 	do{
		delay_ms(100);
		ADS7843_KEY(); //ɨ�谴��
		if(KEY_YES!=0x00)
		{
			//XIANG1();
			KEY_YES=0x00;
			break;
    }
	}while(1); //�ȴ�����
}
 
void KEY_YEYNO(void) //�ȵ������ſ�
{
	do{
		delay_ms(100);
		if(KEY_YES==0x00)
		goto over_KEY_YEYNO;
	}while(1);
 	over_KEY_YEYNO:
	_nop_();  
}
 
void KEY_YEYNO2(void) //�ȵ������ſ�
{
	uint8 loop;
 	loop=0xff;
 	do{
	  delay_ms(1);
		if(KEY_YES==0x00)
		loop=0x00;
	}while(loop); 
}
*/
// ɨ��һ���������а������ط��ذ���ֵ
u8 KEY_FANHUI(u8 GS,u16 *ZB_ADD)
{
	uint8 key=0x00;
 	uint8 loop;
 	uint16  add;
 	uint16  xl,yl,xh,yh;
 	for(loop=0x00;loop<GS;loop++)
	{
		add=loop*4;
		xl=ZB_ADD[add];add++;
		xh=ZB_ADD[add];add++;	 
	  yl=ZB_ADD[add];add++;	 
	  yh=ZB_ADD[add];
	  if(ADS7843_X>=xl&&ADS7843_X<=xh)
	  if(ADS7843_Y>=yl&&ADS7843_Y<=yh)
	  {
			key=loop;
		  key++;
			break;
		}
	}
 	return key;
}	
