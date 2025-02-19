#include "cut_tq_work.h"

void cut_tq_work_wavelength(void)
{
	if(WAVELENGTH == WL532NM)DIS_DEL_DIS(Pic_TQ_WORK_CUT1,1,1,458,458,104,121);
	else if(WAVELENGTH == WL650NM)DIS_DEL_DIS(Pic_TQ_WORK_CUT1,460,1,917,458,104,121);
	else if(WAVELENGTH == WL585NM)DIS_DEL_DIS(Pic_TQ_WORK_CUT1,919,1,1376,458,104,121);
	else if(WAVELENGTH == WL1320NM)DIS_DEL_DIS(Pic_TQ_WORK_CUT1,1378,1,1835,458,104,121);
	else if(WAVELENGTH == WL1064NM)DIS_DEL_DIS(Pic_TQ_WORK_CUT1,1,460,458,917,104,121);
}

void cut_tq_work_wavelength_cover(void)
{
	DIS_DEL_DIS(Pic_TQ_WORK,104,121,561,578,104,121);
}

void cut_tq_work_laser_level(void)
{
	switch(TQ_LASER_LEVEL){
		//case  0x00:DIS_DEL_DIS(Pic_TQ_WORK,1453,973,1744,1002,1453,973);break;
		case  0x00:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,  1,268, 31,1453,973);break;
		case  0x01:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1, 33,268, 63,1453,973);break;
		case  0x02:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1, 65,268, 95,1453,973);break;
		case  0x03:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1, 97,268,127,1453,973);break;
		case  0x04:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,129,268,159,1453,973);break;
		case  0x05:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,161,268,191,1453,973);break;
		case  0x06:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,193,268,223,1453,973);break;
		case  0x07:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,225,268,255,1453,973);break;
		case  0x08:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,257,268,287,1453,973);break;
		case  0x09:DIS_DEL_DIS(Pic_TQ_WORK_CUT2,1,289,268,319,1453,973);break;
	}	
}

void cut_tq_work_start_pic(void)
{
	DIS_DEL_DIS(Pic_TQ_WORK_DOWN,1396,176,1804,540,1396,176);
}

void cut_tq_work_stop_pic(void)
{
	DIS_DEL_DIS(Pic_TQ_WORK,1396,176,1804,540,1396,176);
}






 