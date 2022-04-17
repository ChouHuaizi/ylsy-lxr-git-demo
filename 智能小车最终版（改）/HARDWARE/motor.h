#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
/******************
1方向（前进）
左：黄（L）绿（H）
右：红（L）橙（H）
 	灰（L）白（H）
	褐（L）黑（H）

	蓝到褐P10-P15  
	紫到红P32-P37

******************/
sbit motor_PWM_2=P1^0;
sbit motor_IN1_2=P1^1;
sbit motor_IN2_2=P1^2;
sbit motor_IN3_1=P1^3;
sbit motor_IN4_1=P1^4;
sbit motor_PWM_1=P1^5;

sbit motor_PWM_3=P3^2;
sbit motor_IN1_3=P3^3;
sbit motor_IN2_3=P3^4;
sbit motor_IN3_4=P1^7;
sbit motor_IN4_4=P3^6;
sbit motor_PWM_4=P3^7;

void  motor_Up();	   //向前
void  motor_Stop();	   //停止
void  motor_Set();	   //向后
void motor_Left();	   //向左转
void motor_Right();	   //向右转
void motor_Init();	   //初始化
void motor_round_Left();//原地左转
void motor_round_Right();//原地右转
extern uchar PWM_1 ,PWM_2,PWM_3 ,PWM_4 ,speed;










#endif /*__MOTOR_H*/