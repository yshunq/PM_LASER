#include "display.h"

void TX1_OUT_OVER(void) //帧结束符
{  	
	Uart3Send(0xCC);
 	Uart3Send(0x33);
 	Uart3Send(0xC3);
 	Uart3Send(0x3C);
}

//显示保存在终端的全屏图片
//picnum为显示图片的索引号
void DIS_PICNUM(u8 picnum)
{
  Uart3Send(0xAA);
	Uart3Send(0x70);
	Uart3Send(picnum);
	TX1_OUT_OVER(); //帧结束符
}

//将Flash中的索引号为picnum的图片分割显示在x,y
void DIS_DEL_DIS(u8 picnum,u16 xs,u16 ys,u16 xe,u16 ye,u16 x,u16 y)
{
	Uart3Send(0xAA);
	Uart3Send(0x71);
	Uart3Send(picnum);
	Uart3Send(xs>>8);
	Uart3Send(xs);
	Uart3Send(ys>>8);
	Uart3Send(ys);
	Uart3Send(xe>>8);
	Uart3Send(xe);
	Uart3Send(ye>>8);
	Uart3Send(ye);
	Uart3Send(x>>8);
	Uart3Send(x);
	Uart3Send(y>>8);
	Uart3Send(y);
	TX1_OUT_OVER(); //帧结束符
}

//----------------------下面是可以选择颜色的全部函数-------------------------------------//
//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//gs 发送个数
//C_dots 字体的大小  (0x00 - 6*12) (0x01 - 8*16) (0x02 - 12*24) (0x03 - 16*32) (0x04 - 20*40) (0x05 - 24*48) (0x06 - 28*56) (0x07 - 32*64)
//x  x轴坐标
//y  y轴坐标
//*buf  字符
void DIS_FONT_C(u8 color1,u8 color2,u8 gs,u8 C_dots,u16 x,u16 y,u8 *buf) //显示字符  颜色  个数  大小  xy 字符
{
  uint8 loop;
	Uart3Send(0xAA);
	Uart3Send(0x98);
	Uart3Send(x>>8);
	Uart3Send(x);
	Uart3Send(y>>8);
	Uart3Send(y);
	Uart3Send(0x00);//字库
	Uart3Send(0x81);
	Uart3Send(C_dots);//字体大小
	Uart3Send(color1);
	Uart3Send(color2);//显示出文字颜色 (F800 红 FFFF白)
	Uart3Send(0x00);
	Uart3Send(0x00);
	for(loop=0x00;loop<gs;loop++)
	{
		Uart3Send(*buf);
		buf++;
	}
	TX1_OUT_OVER(); //帧结束符
}

//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//data 显示数据
//C_dots 显示大小
//x  x轴坐标
//y  y轴坐标
void DIS_FONT_NUMBER_C(u8 color1,u8 color2,u8 datat,u8 C_dots,u16 x,u16 y)//显示一个数字  颜色  数据  大小  x  y
{
	switch(datat)
	{
	  case  0:DIS_FONT_C(color1,color2,1,C_dots,x,y,"0");break;//0
	  case  1:DIS_FONT_C(color1,color2,1,C_dots,x,y,"1");break;//1
	  case  2:DIS_FONT_C(color1,color2,1,C_dots,x,y,"2");break;//2
	  case  3:DIS_FONT_C(color1,color2,1,C_dots,x,y,"3");break;//3
	  case  4:DIS_FONT_C(color1,color2,1,C_dots,x,y,"4");break;//4
	  case  5:DIS_FONT_C(color1,color2,1,C_dots,x,y,"5");break;//5
	  case  6:DIS_FONT_C(color1,color2,1,C_dots,x,y,"6");break;//6
	  case  7:DIS_FONT_C(color1,color2,1,C_dots,x,y,"7");break;//7
	  case  8:DIS_FONT_C(color1,color2,1,C_dots,x,y,"8");break;//8
	  case  9:DIS_FONT_C(color1,color2,1,C_dots,x,y,"9");break;//9
	  case 10:DIS_FONT_C(color1,color2,1,C_dots,x,y,".");break;//.
	  case 11:DIS_FONT_C(color1,color2,1,C_dots,x,y,"V");break;//V
	  case 12:DIS_FONT_C(color1,color2,1,C_dots,x,y,"A");break;//A
	  case 13:DIS_FONT_C(color1,color2,1,C_dots,x,y,"B");break;//B
	  case 14:DIS_FONT_C(color1,color2,1,C_dots,x,y," ");break;//空格
  }
}

//color  颜色  红色：color1=0x08 color2=0x00     白色：color1=0xFF color2=0xFF   黑色：color1=0x00 color2=0x00
//C_dots 显示大小
//data 表示显示的数据
//wei 表示显示的位数
//x  x轴坐标
//y  y轴坐标
void DIS_FONT_WEI_NUMBER_CM(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u32 datat,u8 wei,u16 x,u16 y)//剪切图片 左0中1右2 颜色1 颜色2 字体大小 显示数值 位数 x坐标 y坐标
{
  uint8 xian[8];
	uint8 x_add,y_add,i;
	uint16 xs,ys;
	uint32 temp;
	i = 0;
	xian[0] = (uint8)(datat%10);
	xian[1] = (uint8)((datat/10)%10);
	xian[2] = (uint8)((datat/100)%10);
	xian[3] = (uint8)((datat/1000)%10);
	xian[4] = (uint8)((datat/10000)%10);
	xian[5] = (uint8)((datat/100000)%10);
	xian[6] = (uint8)((datat/1000000)%10);
	xian[7] = (uint8)((datat/10000000)%10);
	switch(C_dots)//显示的位数
	{
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}
	if(pic < 255)DIS_DEL_DIS(pic,x,y,x+(wei*x_add),y+y_add,x,y);
	temp = datat;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	
	if(i > wei)i = wei;
	if(duiqi == 0)xs = x;//左对齐
	else if(duiqi == 1)xs = (wei - i)*(x_add/2)+x;//居中
	else{xs = (wei - i)*x_add+x;}//右对齐
	ys = y;
	do{
		i--;
		DIS_FONT_NUMBER_C(color1,color2,xian[i],C_dots,xs,ys);//显示一个数字
		xs = xs + x_add;
		_nop_();
		_nop_();
	}while(i>0);
}

//显示前后对比数据
void DIS_FONT_WEI_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 flag,u32 value,u32 buff,u16 x,u16 y)
{
	u8 i,wei1,wei2,pic_buff;
	u16 x_add,y_add,xs,ys;
	u32 temp,buff_temp;
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}	 	
	
	temp = value;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei1 = i;
	if(i > wei)wei1 = wei;

	temp = buff;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	wei2 = i;
	if(i > wei)wei2 = wei;
	
	if(wei1 != wei2 || flag == DIS_ALL){
		temp = wei;
		DIS_DEL_DIS(pic,x,y,temp*x_add+x,y_add+y,x,y);
	}

	i = wei1;

	if(duiqi == 0)xs = (i - 1)*x_add + x;
	else if(duiqi == 1)xs = (wei - i)*(x_add/2) + x + ((i - 1)*x_add);
	else{xs = (wei - 1)*x_add + x;}
	ys = y;
	
	temp = value;
	buff_temp = buff;
	do{
		i--;
		if(wei1 != wei2 || flag == DIS_ALL)pic_buff = 255;
		else{pic_buff = pic;}
		if(wei1 != wei2 || flag == DIS_ALL || temp%10 != buff_temp%10){
			DIS_FONT_WEI_NUMBER_CM(pic_buff,duiqi,color1,color2,C_dots,temp%10,1,xs,ys);	
		}
		temp = temp/10;
		buff_temp = buff_temp/10;
		xs = xs - x_add;
		_nop_();
		_nop_();
	}while(i>0);
}

////显示前后对比数据  小数点一位
//void DIS_FONT_WEI_DECIMAL_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 flag,u32 value,u32 buff,u16 x,u16 y)
//{
//	u8 x_add,y_add,i,wei1,wei2,pic_buff,j;
//	u16 xs,ys;
//	u32 temp,buff_temp;
//	switch(C_dots){//显示的位数
//		case  0x00: x_add =  6;y_add = 12;break;
//		case  0x01: x_add =  8;y_add = 16;break;
//		case  0x02: x_add = 12;y_add = 24;break;
//		case  0x03: x_add = 16;y_add = 32;break;
//		case  0x04: x_add = 20;y_add = 40;break;
//		case  0x05: x_add = 24;y_add = 48;break;
//		case  0x06: x_add = 28;y_add = 56;break;
//		case  0x07: x_add = 32;y_add = 64;break;
//		case  0x08: x_add = 40;y_add = 80;break;
//		case  0x09: x_add = 48;y_add = 96;break;
//		case  0x0A: x_add = 56;y_add = 112;break;
//	}	 	
//	
//	temp = value/10;
//	i = 0;
//	do{
//	   i++;
//	   temp/=10;
//	}while(temp>0);
//	wei1 = i + 2; 	//算上小数点  和  小数位
//	if(i > wei)wei1 = wei;
//
//	temp = buff/10;
//	i = 0;
//	do{
//	   i++;
//	   temp/=10;
//	}while(temp>0);
//	wei2 = i + 2; 	//算上小数点  和  小数位
//	if(i > wei)wei2 = wei;
//
//	if(wei1 != wei2 || flag == DIS_ALL){DIS_DEL_DIS(pic,x,y,wei*x_add+x,y_add+y,x,y);}
//
//	i = wei1;
//
//	if(duiqi == 0)xs = (i - 1)*x_add + x;
//	else if(duiqi == 1)xs = (wei - i)*(x_add/2) + x + ((i - 1)*x_add);
//	else{xs = (wei - 1)*x_add;}
//	ys = y;
//	
//	temp = value;
//	buff_temp = buff;
//	j = 0;
//	do{
//		i--;
//		if(wei1 != wei2 || flag == DIS_ALL)pic_buff = 255;
//		else{pic_buff = pic;}
//		
//		if(j != 1){
//			if(wei1 != wei2 || flag == DIS_ALL || temp%10 != buff_temp%10){
//				DIS_FONT_WEI_NUMBER_CM(pic_buff,duiqi,color1,color2,C_dots,temp%10,1,xs,ys);	
//			}
//			temp = temp/10;
//			buff_temp = buff_temp/10;
//		}else{
//			if(wei1 != wei2 || flag == DIS_ALL)DIS_FONT_C(color1,color2,1,C_dots,xs,ys,".");	
//		}
//		xs = xs - x_add;
//		j++;
//		_nop_();
//		_nop_();
//	}while(i>0);
//}



//显示前后对比数据  小数点两位
void DIS_FONT_WEI_DECIMAL_TWO_VALUE(u8 pic,u8 duiqi,u8 color1,u8 color2,u8 C_dots,u8 wei,u8 flag,u32 value,u32 buff,u16 x,u16 y)
{
	u8 x_add,y_add,i,wei1,wei2,pic_buff,j;
	u16 xs,ys;
	u32 temp,buff_temp;
	switch(C_dots){//显示的位数
		case  0x00: x_add =  6;y_add = 12;break;
		case  0x01: x_add =  8;y_add = 16;break;
		case  0x02: x_add = 12;y_add = 24;break;
		case  0x03: x_add = 16;y_add = 32;break;
		case  0x04: x_add = 20;y_add = 40;break;
		case  0x05: x_add = 24;y_add = 48;break;
		case  0x06: x_add = 28;y_add = 56;break;
		case  0x07: x_add = 32;y_add = 64;break;
		case  0x08: x_add = 40;y_add = 80;break;
		case  0x09: x_add = 48;y_add = 96;break;
		case  0x0A: x_add = 56;y_add = 112;break;
	}	 	
	
	temp = value;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	if(i <= 3)wei1 = 4;else{if(i > wei)i = wei;wei1 = i + 1;}//小数点算一个位

	temp = buff;
	i = 0;
	do{
	   i++;
	   temp/=10;
	}while(temp>0);
	if(i <= 3)wei2 = 4;else{if(i > wei)i = wei;wei2 = i + 1;}//小数点算一个位

	if(wei1 != wei2 || flag == DIS_ALL){DIS_DEL_DIS(pic,x,y,wei*x_add+x,y_add+y,x,y);}

	i = wei1;

	if(duiqi == 0)xs = (i - 1)*x_add + x;
	else if(duiqi == 1)xs = (wei - i)*(x_add/2) + x + ((i - 1)*x_add);
	else{xs = (wei - 1)*x_add;}
	ys = y;
	
	temp = value;
	buff_temp = buff;
	j = 0;
	do{
		i--;
		if(wei1 != wei2 || flag == DIS_ALL)pic_buff = 255;
		else{pic_buff = pic;}
		
		if(j != 2){
			if(wei1 != wei2 || flag == DIS_ALL || temp%10 != buff_temp%10){
				DIS_FONT_WEI_NUMBER_CM(pic_buff,duiqi,color1,color2,C_dots,temp%10,1,xs,ys);	
			}
			temp = temp/10;
			buff_temp = buff_temp/10;
		}else{
			if(wei1 != wei2 || flag == DIS_ALL)DIS_FONT_C(color1,color2,1,C_dots,xs,ys,".");	
		}
		xs = xs - x_add;
		j++;
		_nop_();
		_nop_();
	}while(i>0);
}








