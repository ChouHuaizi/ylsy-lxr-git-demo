#ifndef __SYS_H
#define __SYS_H


#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define High 1
#define Low  0
sfr T2MOD=0XC9;
sbit R_LED=P2^4;
sbit G_LED=P2^5;
sbit B_LED=P2^6;
sbit beep=P2^1;









#endif /*__SYS_H*/