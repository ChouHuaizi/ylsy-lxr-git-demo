#include "Timer.h"
void Time0_Init()					 //��ʱ����ʼ��
{
	TMOD = 0x01;
	IE = 0x82;
	TH0 = 0xff;						 //����0.1ms	 200�ⶥ
	TL0 = 0xa4;												   
	TR0=1;							 //�����ж�
}

//void Time2_Init()					 //��ʱ��2��ʼ��
//{
//	T2MOD=0x01;
//	RCAP2H = 0x00;                  // ��ԭ����0xfc�ĳ�0x0c��������ʱʱ�䣬���ڷ���鿴Ч����
//	RCAP2L = 0x00;
//	T2CON = 0x00;
//	TH2 = RCAP2H;
//	TL2 = RCAP2L;
//	EA = 1;
//	ET2 = 1;
////	TR2 = 1;
//}