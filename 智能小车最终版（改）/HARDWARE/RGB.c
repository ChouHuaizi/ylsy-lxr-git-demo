#include "RGB.h"
#include "delay.h"
uchar ge,shi,bai ;
uchar flag_R=48,flag_G=48,flag_B=48;
uchar disp_R[3];  //红
uchar disp_G[3];  //绿
uchar disp_B[3];  //蓝
uchar count;          //颜色标志位（0:红 1:绿 2:蓝）
uint temp;
uchar dianji,yanse;
sbit s2=P0^3;        //TCS3200 S2 	 P0^4
sbit s3=P0^4;        //TCS3200 S3	 P0^3
                     //TCS3200 S0 模块内部默认上拉	5V
                     //TCS3200 S1 模块内部默认上拉	5V
                     //TCS3200 OE 模块内部接地
					 //TCS3200 OUT 接P3^5给脉冲
void Color_recognition()
{
	uint temp_[3];
	uint num;
	TR0=0;              //关闭定时
	TR1=0;              //关闭计数
	//   count+1实现先检测绿色,再检测蓝色,然后检测红色,循环检测       
	if(count==0)
	{
		count++;    
		s2=1;s3=1;             //选择滤波器为绿色     
		
		temp=(8<<TH1)+TL1;    //计算这段时间内 TCS230 的输出脉冲数	
//		temp/=rp;			
		conversion(temp);
		 temp_[0] = temp;
		disp_G[2]=ge;         //因为这次的中断，是上次选择滤波器的数值
		disp_G[1]=shi;
		disp_G[0]=bai;
		
	}	
	else if(count==1)
	{            
		count++;
		s2=1;s3=0;            //选择滤波器为蓝色
		temp=(8<<TH1)+TL1;    //计算这段时间内 TCS230 的输出脉冲数	
//		temp/=gp;			
		conversion(temp);
		temp_[1] = temp;
		disp_B[2]=ge;         //因为这次的中断，是上次选择滤波器的数值
		disp_B[1]=shi;
		disp_B[0]=bai;
	}	
	else if(count==2)
	{            
		count=0;
		s2=0;s3=0;            //选择滤波器为红色
		
		temp=(8<<TH1)+TL1;    //计算这段时间内 TCS230 的输出脉冲数	
//		temp/=bp;		
		conversion(temp);
		temp_[2] = temp;
		disp_R[2]=ge;         //因为这次的中断，是上次选择滤波器的数值
		disp_R[1]=shi;
		disp_R[0]=bai;
	
	}
	num++;
	if(num==150)
	{		
	
		compare(temp_[0],temp_[1],temp_[2]);//变量进去	
		dianji =1;					//打开电机
	 	yanse =0;					//关闭颜色识别
		num=0;						//计数值清零
		
		beep=~beep;					//识别一次蜂鸣器响两次
		delay(100);
		beep=~beep;
		delay(100);
		beep=~beep;
		delay(100);
		beep=~beep;
		delay(100);
	}
	//定时器计数器重赋初值
	TH0=0xE0;
	TL0=0x00; //11。0592M 晶振，为10ms
	TL1=0x00;//计数器清零
	TH1=0x00;//计数器清零
	TR0=1;   //打开定时器
	TR1=1;   //打开计数器
}
void conversion(uint temp_data)  
{  	 

    bai=temp_data/100+0x30 ;
    temp_data=temp_data%100;   //取余运算
    shi=temp_data/10+0x30 ;
    ge=temp_data%10+0x30;      //取余运算
}

uint compare(uint G,uint B,uint R)
{
	if(G>B)
	{
		if(G>R)
		{
		flag_G++;
		R_LED=~R_LED;
		delay(200);
		R_LED=~R_LED;
		return G;
		 }
		   else 
		   {	
			B_LED=~B_LED;
			delay(200);
			B_LED=~B_LED;
			flag_R++;
			return R;
			    
		   }
	}
	else {
	if(B>R)
	{
		flag_B++;
		G_LED=~G_LED;
		delay(200);
		G_LED=~G_LED;
	  	 return B;
	}
	  else
	  {
		flag_R++;
		B_LED=~B_LED;
		delay(200);
		B_LED=~B_LED;
		  return R;
	  } 
	  
	  }
	  	
}

void parameter_Init()
{
	s2=0;           //初始设定S2引脚
	s3=0;           //初始设定S3引脚
}

