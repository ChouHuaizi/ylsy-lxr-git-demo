#include "Timer.h"
void Time0_Init()					 //定时器初始化
{
	TMOD = 0x01;
	IE = 0x82;
	TH0 = 0xff;						 //周期0.1ms	 200封顶
	TL0 = 0xa4;												   
	TR0=1;							 //开启中断
}

//void Time2_Init()					 //定时器2初始化
//{
//	T2MOD=0x01;
//	RCAP2H = 0x00;                  // 由原来的0xfc改成0x0c，增大延时时间，便于仿真查看效果；
//	RCAP2L = 0x00;
//	T2CON = 0x00;
//	TH2 = RCAP2H;
//	TL2 = RCAP2L;
//	EA = 1;
//	ET2 = 1;
////	TR2 = 1;
//}