#include "motor.h"
uchar PWM_1 =50,PWM_2 =50,PWM_3 =50,PWM_4 =50,speed=50;//初速度

void motor_Init()		   //初始化
{
	motor_PWM_1=0;			//低电平停车
	motor_PWM_2=0;
	motor_PWM_3=0;
	motor_PWM_4=0;
	motor_IN1_2=1; 			//前进方向
	motor_IN2_2=0;
	motor_IN3_1=1;
	motor_IN4_1=0;
	motor_IN1_3=0; 			//前进方向
	motor_IN2_3=1;
	motor_IN3_4=0;
	motor_IN4_4=1;
	PWM_1 = 0;
	PWM_3 =	0;
	PWM_2 = 0;
	PWM_4 =	0;
}

void  motor_Up()		   	//前进
{
	TR0=1;
	PWM_1 =speed;
	PWM_2 =speed;
	PWM_3 =speed;
	PWM_4 =speed;
	motor_IN1_2=1; 		//往前转
	motor_IN2_2=0;
	motor_IN3_1=1;
	motor_IN4_1=0;
	motor_IN1_3=0; 		//往前转
	motor_IN2_3=1;
	motor_IN3_4=0;
	motor_IN4_4=1;		//往前转
}
void motor_Stop()			 //停止
{
	TR0=1;
	PWM_1 =0;
	PWM_2 =0;
	PWM_3 =0;
	PWM_4 =0;
	motor_IN1_2=0; 		//前进方向
	motor_IN2_2=0;
	motor_IN3_1=0;
	motor_IN4_1=0;
	motor_IN1_3=0; 		
	motor_IN2_3=0;
	motor_IN3_4=0;
	motor_IN4_4=0;
	motor_PWM_1=0;			//低电平停车
	motor_PWM_2=0;
	motor_PWM_3=0;			//低电平停车
	motor_PWM_4=0;
}

void  motor_Set()			//后退
{
	TR0=1;
	PWM_1 =125;
	PWM_2 =125;
	PWM_3 =125;
	PWM_4 =125;
	motor_IN1_2=0; 			//往后转
	motor_IN2_2=1;
	motor_IN3_1=0;
	motor_IN4_1=1;
	motor_IN1_3=1; 		
	motor_IN2_3=0;
	motor_IN3_4=1;
	motor_IN4_4=0;
}

void motor_Left()			 //向左转
{
	TR0=1;
	//左排轮
	PWM_1 = 25;
	PWM_3 =	25;
	//右排轮
	PWM_2 = 125;
	PWM_4 =	125;
	//右前轮
	motor_IN1_2=1; 			 //往前转
	motor_IN2_2=0;
	//左前轮
	motor_IN3_1=1;			 //往前转
	motor_IN4_1=0;
	//后左轮
	motor_IN1_3=0; 			 //往前转
	motor_IN2_3=1;
	//后右轮
	motor_IN3_4=0;			 //往前转
	motor_IN4_4=1;
}
void motor_Right()			 //向右转
{
	TR0=1;
	//左排轮
	PWM_1 = 125;
	PWM_3 =	125;
	//右排轮
	PWM_2 = 25;
	PWM_4 =	25;
	//右前轮
	motor_IN1_2=1; 		
	motor_IN2_2=0;			  //往前转
	//左前轮
	motor_IN3_1=1;			  
	motor_IN4_1=0;			  //往前转
	//后左轮
	motor_IN1_3=0; 	
	motor_IN2_3=1;			  //往前转
	//后右轮
	motor_IN3_4=0;			  
	motor_IN4_4=1;			  //往前转
}

void motor_round_Right()	  //原地右转
{
	TR0=1;
	//左排轮
	PWM_1 = 100;
	PWM_3 =	100;
	//右排轮
	PWM_2 = 100;
	PWM_4 =	100;
	//右前轮
	motor_IN1_2=0; 		
	motor_IN2_2=1;			  //往后转
	//左前轮
	motor_IN3_1=1;
	motor_IN4_1=0;			  //往前转
	//后左轮
	motor_IN1_3=0; 	
	motor_IN2_3=1;			 //往前转
	//后右轮
	motor_IN3_4=1;	
	motor_IN4_4=0;			 //往后转  
}
void motor_round_Left()		 //原地左转
{
	TR0=1;
	//左排轮
	PWM_1 = 100;
	PWM_3 =	100;
	//右排轮
	PWM_2 = 100;
	PWM_4 =	100;
	//右前轮
	motor_IN1_2=1; 		   //往前转
	motor_IN2_2=0;		   
	//左前轮
	motor_IN3_1=0;		   
	motor_IN4_1=1;		   //往后转
	//后左轮
	motor_IN1_3=1; 		   
	motor_IN2_3=0;		   //往后转
	//后右轮
	motor_IN3_4=0;		   
	motor_IN4_4=1;		   //往前转
}
