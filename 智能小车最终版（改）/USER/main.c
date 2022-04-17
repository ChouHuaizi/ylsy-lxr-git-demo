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
//��ʾ����
uchar flag=0;//���ϱ�־λ 
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
//	Init_Lcd();	   	//1602��ʼ��
	motor_Init();	//�����ʼ��
	Time0_Init();	//��ʱ��1��ʼ��	�����PWM������
//	LCD_write_command(0x01);
//	Write_LCD(1, 0, "Ready!");
	dianji =1;
	yanse =0;
	TIM1_();
//	Time2_Init();
	UartConfigurationInit() ;  //�����������ö�ʱ��2Ϊ�жϣ���Ҫ�Ѷ�ʱ��һ�رգ�Bluetooth_Usart_Init�� �ж����ȼ�����Ϊ4
//	Bluetooth_Usart_Init();	//�������ڳ�ʼ��
//	TR0=0;					//�رն�ʱ��
		flag=0;
	while(1)
	{
	PWM_1 =100;	 
	motor_IN3_1=1;
	motor_IN4_1=0;
		dianji =1;
//		display_RGB();			 //��ʾRGBֵ
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

//	if(guangmin==0&&flag==0)			  //��ʶ���������ʱ��������һ���ú��˿ɽ��ֹͣ
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

//   if(yanse==1)						//��ɫʶ��
//   {
//		 Color_recognition();
//	}

}  
void Bluetooth_Usart() interrupt 4      //�жϺ���
{
	RI = 0; 		
	receive=SBUF;
	dat_deal_with(receive);	   	//�����������ܵ�����

//	TI=0;					  //���������ɱ�־λ
//	while(!TI);			      //�ȴ������������

}
void dat_deal_with(uchar receive)
{

	if(receive=='1')	 		//ǰ��
	{
		motor_Up();
		flag=0;
			
	 }	
	else if(receive=='2')	 		//����
	{
		motor_Set();
		flag=1;	
	 }
	else if(receive=='3')	 		//ֹͣ
	{
		motor_Stop();
	 }
	 else if(receive=='4')	 		//��ת
	{
		motor_Left();	
	 }
	 else if(receive=='5')	 		//��ת
	{
		motor_Right();	
	 }
	 else if(receive=='6')
	 {
	 	speed=50;					  //һ��
	 }
	 else if(receive=='7')
	 {
	 	speed=100;					  //����
	 }
	 else if(receive=='8')
	 {
	 	speed=200;					  //����
	 }
	 else if(receive == '9')
	 {
	 	motor_round_Left();				//ԭ����ת
	 }
	 else if(receive == ':')
	 {
	 	motor_round_Right();		   //ԭ����ת
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

	

