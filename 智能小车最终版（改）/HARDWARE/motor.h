#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"
/******************
1����ǰ����
�󣺻ƣ�L���̣�H��
�ң��죨L���ȣ�H��
 	�ң�L���ף�H��
	�֣�L���ڣ�H��

	������P10-P15  
	�ϵ���P32-P37

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

void  motor_Up();	   //��ǰ
void  motor_Stop();	   //ֹͣ
void  motor_Set();	   //���
void motor_Left();	   //����ת
void motor_Right();	   //����ת
void motor_Init();	   //��ʼ��
void motor_round_Left();//ԭ����ת
void motor_round_Right();//ԭ����ת
extern uchar PWM_1 ,PWM_2,PWM_3 ,PWM_4 ,speed;










#endif /*__MOTOR_H*/