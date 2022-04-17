#ifndef __DELAY_H
#define __DELAY_H 
#include <REGX51.H>
#include"Delay.h "
void Delay1us(unsigned  us)		//@11.0592MHz
{
	while(us--)
	{
		_nop_();
		_nop_();
		_nop_();
	}
}

void Delay1ms(unsigned int ms)		//@11.0592MHz
{
	unsigned char i, j;
	while(ms--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}

#endif 