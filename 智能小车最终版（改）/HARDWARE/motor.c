#include "motor.h"
uchar PWM_1 =50,PWM_2 =50,PWM_3 =50,PWM_4 =50,speed=50;//���ٶ�

void motor_Init()		   //��ʼ��
{
	motor_PWM_1=0;			//�͵�ƽͣ��
	motor_PWM_2=0;
	motor_PWM_3=0;
	motor_PWM_4=0;
	motor_IN1_2=1; 			//ǰ������
	motor_IN2_2=0;
	motor_IN3_1=1;
	motor_IN4_1=0;
	motor_IN1_3=0; 			//ǰ������
	motor_IN2_3=1;
	motor_IN3_4=0;
	motor_IN4_4=1;
	PWM_1 = 0;
	PWM_3 =	0;
	PWM_2 = 0;
	PWM_4 =	0;
}

void  motor_Up()		   	//ǰ��
{
	TR0=1;
	PWM_1 =speed;
	PWM_2 =speed;
	PWM_3 =speed;
	PWM_4 =speed;
	motor_IN1_2=1; 		//��ǰת
	motor_IN2_2=0;
	motor_IN3_1=1;
	motor_IN4_1=0;
	motor_IN1_3=0; 		//��ǰת
	motor_IN2_3=1;
	motor_IN3_4=0;
	motor_IN4_4=1;		//��ǰת
}
void motor_Stop()			 //ֹͣ
{
	TR0=1;
	PWM_1 =0;
	PWM_2 =0;
	PWM_3 =0;
	PWM_4 =0;
	motor_IN1_2=0; 		//ǰ������
	motor_IN2_2=0;
	motor_IN3_1=0;
	motor_IN4_1=0;
	motor_IN1_3=0; 		
	motor_IN2_3=0;
	motor_IN3_4=0;
	motor_IN4_4=0;
	motor_PWM_1=0;			//�͵�ƽͣ��
	motor_PWM_2=0;
	motor_PWM_3=0;			//�͵�ƽͣ��
	motor_PWM_4=0;
}

void  motor_Set()			//����
{
	TR0=1;
	PWM_1 =125;
	PWM_2 =125;
	PWM_3 =125;
	PWM_4 =125;
	motor_IN1_2=0; 			//����ת
	motor_IN2_2=1;
	motor_IN3_1=0;
	motor_IN4_1=1;
	motor_IN1_3=1; 		
	motor_IN2_3=0;
	motor_IN3_4=1;
	motor_IN4_4=0;
}

void motor_Left()			 //����ת
{
	TR0=1;
	//������
	PWM_1 = 25;
	PWM_3 =	25;
	//������
	PWM_2 = 125;
	PWM_4 =	125;
	//��ǰ��
	motor_IN1_2=1; 			 //��ǰת
	motor_IN2_2=0;
	//��ǰ��
	motor_IN3_1=1;			 //��ǰת
	motor_IN4_1=0;
	//������
	motor_IN1_3=0; 			 //��ǰת
	motor_IN2_3=1;
	//������
	motor_IN3_4=0;			 //��ǰת
	motor_IN4_4=1;
}
void motor_Right()			 //����ת
{
	TR0=1;
	//������
	PWM_1 = 125;
	PWM_3 =	125;
	//������
	PWM_2 = 25;
	PWM_4 =	25;
	//��ǰ��
	motor_IN1_2=1; 		
	motor_IN2_2=0;			  //��ǰת
	//��ǰ��
	motor_IN3_1=1;			  
	motor_IN4_1=0;			  //��ǰת
	//������
	motor_IN1_3=0; 	
	motor_IN2_3=1;			  //��ǰת
	//������
	motor_IN3_4=0;			  
	motor_IN4_4=1;			  //��ǰת
}

void motor_round_Right()	  //ԭ����ת
{
	TR0=1;
	//������
	PWM_1 = 100;
	PWM_3 =	100;
	//������
	PWM_2 = 100;
	PWM_4 =	100;
	//��ǰ��
	motor_IN1_2=0; 		
	motor_IN2_2=1;			  //����ת
	//��ǰ��
	motor_IN3_1=1;
	motor_IN4_1=0;			  //��ǰת
	//������
	motor_IN1_3=0; 	
	motor_IN2_3=1;			 //��ǰת
	//������
	motor_IN3_4=1;	
	motor_IN4_4=0;			 //����ת  
}
void motor_round_Left()		 //ԭ����ת
{
	TR0=1;
	//������
	PWM_1 = 100;
	PWM_3 =	100;
	//������
	PWM_2 = 100;
	PWM_4 =	100;
	//��ǰ��
	motor_IN1_2=1; 		   //��ǰת
	motor_IN2_2=0;		   
	//��ǰ��
	motor_IN3_1=0;		   
	motor_IN4_1=1;		   //����ת
	//������
	motor_IN1_3=1; 		   
	motor_IN2_3=0;		   //����ת
	//������
	motor_IN3_4=0;		   
	motor_IN4_4=1;		   //��ǰת
}
