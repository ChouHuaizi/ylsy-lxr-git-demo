#include "Bluetooth.h"

//void Bluetooth_Usart_Init()
//{
//  	TMOD=0X20;         	 //定时器T1的工作方式2（8位初值自动重装的8位定时器/计数器）
//  	TH1=0xfd;        	 //T1定时器装初值（波特率为9600，初值为0xfd）
//  	TL1=0xfd;         	 //TH1,TL1需要一致
//  	TR1=1; 		  	 	 //启动定时器1
//  	SCON=0x50;        	 //串行口控制寄存器0101 0000  
//  	PCON=0x00;  	  	 //电源管理寄存器
//  	EA=1;             	 //开总中断  
//  	ES=1;             	 //开串口中断 
// 	PS=1;
//}
void UartConfigurationInit() 			//用TIM2来做蓝牙
{
	T2MOD = 0x01; 	//自动重载
	T2CON = 0x30; 	//T2用做发送接收时钟
	TH2 = 0xFF;  	//9600波特率,11.0592Mhz晶振
	TL2 = 0xDC; 
	RCAP2H = 0xFF; 
	RCAP2L = 0xDC; 
	SCON = 0x50; 	//串口方式1,1个起始位,1个停止位,8位数据，可变波特率
	PCON = 0X00;	//波特率不加倍
 	TR2 = 1;  		//启动T2 
	ES = 1;         //开串口中断
  	EA = 1;         //开总中断
	PS=1;
}
void TIM1_()			 //想用定时器1去给颜色识别模块接受脉冲，脉冲口为P3^5
{
	TMOD=0x51;        //T1计数 T0定时 工作方式1
	
	TH1=0x00;        //计数初值
	TL1=0x00;
	
	TH0=0xE0;
	TL0=0x00;        //11。0592M 晶振10ms
	EA=1;            //开中断
	
	ET0=1;        
	TR0=1;           //启动
	TR1=1;	
}