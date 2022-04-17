#include "sys.h"
#include "1602_LCD.h"
#include "Bluetooth.h"
#include "motor.h"
#include "Timer.h"
#include "RGB.h"
#include "delay.h"
void dat_deal_with(uchar receive);
void delay(unsigned int k)	;
void compare_choice(uint temp);
void display_RGB();
sbit guangmin=P2^0;
sbit key=P1^5;					
uchar jd,receive=0;
//显示数组
uchar flag=0;//避障标志位 
void main()
{
	dianji =1;
	yanse =0;
	jd=0;
	beep=1;	
	R_LED=0;
	G_LED=0;
	B_LED=0;
	 parameter_Init();
//	Init_Lcd();	   	//1602初始化
	motor_Init();	//电机初始化
	Time0_Init();	//定时器1初始化	（电机PWM驱动）
//	LCD_write_command(0x01);
//	Write_LCD(1, 0, "Ready!");
	dianji =1;
	yanse =0;
	TIM1_();
//	Time2_Init();
	UartConfigurationInit() ;  //打开他就是设置定时器2为中断，需要把定时器一关闭（Bluetooth_Usart_Init） 中断优先级设置为4
//	Bluetooth_Usart_Init();	//蓝牙串口初始化
//	TR0=0;					//关闭定时器
		flag=0;
	while(1)
	{
	PWM_1 =100;	 
	motor_IN3_1=1;
	motor_IN4_1=0;
		dianji =1;
//		display_RGB();			 //显示RGB值
	}
}
 
void Time0_Int()interrupt 1
{
	
	uchar beep_ON_OFF=0;
	if(dianji==1)
{
	TH0 = 0xff;			  //ff aF 0.1ms
	TL0 = 0xa4;
	if(jd<PWM_1)	motor_PWM_1=1;
	else 			motor_PWM_1=0;

	if(jd<PWM_2)	motor_PWM_2=1;
	else 			motor_PWM_2=0;

	if(jd<PWM_3)	motor_PWM_3=1;
	else 			motor_PWM_3=0;

	if(jd<PWM_4)	motor_PWM_4=1;
	else 			motor_PWM_4=0;

//	if(guangmin==0&&flag==0)			  //当识别到有物体的时候，往后退一下用后退可解除停止
//	{
//		motor_Set();
//		beep_ON_OFF=1;
//		delay(100);
//		motor_Stop();
//		beep=~beep;
//	}else beep=1;
	jd = (jd+1);
	jd = jd%200;
   }

//   if(yanse==1)						//颜色识别
//   {
//		 Color_recognition();
//	}

}  
void Bluetooth_Usart() interrupt 4      //中断函数
{
	RI = 0; 		
	receive=SBUF;
	dat_deal_with(receive);	   	//处理蓝牙接受的数据

//	TI=0;					  //清除发送完成标志位
//	while(!TI);			      //等待发送数据完成

}
void dat_deal_with(uchar receive)
{

	if(receive=='1')	 		//前进
	{
		motor_Up();
		flag=0;
			
	 }	
	else if(receive=='2')	 		//后退
	{
		motor_Set();
		flag=1;	
	 }
	else if(receive=='3')	 		//停止
	{
		motor_Stop();
	 }
	 else if(receive=='4')	 		//左转
	{
		motor_Left();	
	 }
	 else if(receive=='5')	 		//右转
	{
		motor_Right();	
	 }
	 else if(receive=='6')
	 {
	 	speed=50;					  //一档
	 }
	 else if(receive=='7')
	 {
	 	speed=100;					  //二档
	 }
	 else if(receive=='8')
	 {
	 	speed=200;					  //三档
	 }
	 else if(receive == '9')
	 {
	 	motor_round_Left();				//原地左转
	 }
	 else if(receive == ':')
	 {
	 	motor_round_Right();		   //原地右转
	 }
	 else if(receive == '!')
	 {
	 	 dianji =0;
	 	yanse =1;
	 }
	
}
	



void display_RGB()
{		DisplayOneChar(9, 0, 'B');
	 	DisplayOneChar(11, 0, disp_R[0]); 
		DisplayOneChar(12, 0, disp_R[1]); 
		DisplayOneChar(13, 0, disp_R[2]);
		DisplayOneChar(15, 0, flag_R);

		DisplayOneChar(0, 1, 'R');
		DisplayOneChar(2, 1, disp_G[0]); 
		DisplayOneChar(3, 1, disp_G[1]); 
		DisplayOneChar(4, 1, disp_G[2]);
		DisplayOneChar(6, 1, flag_G);

		DisplayOneChar(9, 1, 'G');
		DisplayOneChar(11, 1, disp_B[0]); 
		DisplayOneChar(12, 1, disp_B[1]); 
		DisplayOneChar(13, 1, disp_B[2]);  
		DisplayOneChar(15, 1, flag_B);
}

	

