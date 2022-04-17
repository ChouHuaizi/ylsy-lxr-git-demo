#include "RGB.h"
#include "delay.h"
uchar ge,shi,bai ;
uchar flag_R=48,flag_G=48,flag_B=48;
uchar disp_R[3];  //��
uchar disp_G[3];  //��
uchar disp_B[3];  //��
uchar count;          //��ɫ��־λ��0:�� 1:�� 2:����
uint temp;
uchar dianji,yanse;
sbit s2=P0^3;        //TCS3200 S2 	 P0^4
sbit s3=P0^4;        //TCS3200 S3	 P0^3
                     //TCS3200 S0 ģ���ڲ�Ĭ������	5V
                     //TCS3200 S1 ģ���ڲ�Ĭ������	5V
                     //TCS3200 OE ģ���ڲ��ӵ�
					 //TCS3200 OUT ��P3^5������
void Color_recognition()
{
	uint temp_[3];
	uint num;
	TR0=0;              //�رն�ʱ
	TR1=0;              //�رռ���
	//   count+1ʵ���ȼ����ɫ,�ټ����ɫ,Ȼ�����ɫ,ѭ�����       
	if(count==0)
	{
		count++;    
		s2=1;s3=1;             //ѡ���˲���Ϊ��ɫ     
		
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
//		temp/=rp;			
		conversion(temp);
		 temp_[0] = temp;
		disp_G[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_G[1]=shi;
		disp_G[0]=bai;
		
	}	
	else if(count==1)
	{            
		count++;
		s2=1;s3=0;            //ѡ���˲���Ϊ��ɫ
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
//		temp/=gp;			
		conversion(temp);
		temp_[1] = temp;
		disp_B[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_B[1]=shi;
		disp_B[0]=bai;
	}	
	else if(count==2)
	{            
		count=0;
		s2=0;s3=0;            //ѡ���˲���Ϊ��ɫ
		
		temp=(8<<TH1)+TL1;    //�������ʱ���� TCS230 �����������	
//		temp/=bp;		
		conversion(temp);
		temp_[2] = temp;
		disp_R[2]=ge;         //��Ϊ��ε��жϣ����ϴ�ѡ���˲�������ֵ
		disp_R[1]=shi;
		disp_R[0]=bai;
	
	}
	num++;
	if(num==150)
	{		
	
		compare(temp_[0],temp_[1],temp_[2]);//������ȥ	
		dianji =1;					//�򿪵��
	 	yanse =0;					//�ر���ɫʶ��
		num=0;						//����ֵ����
		
		beep=~beep;					//ʶ��һ�η�����������
		delay(100);
		beep=~beep;
		delay(100);
		beep=~beep;
		delay(100);
		beep=~beep;
		delay(100);
	}
	//��ʱ���������ظ���ֵ
	TH0=0xE0;
	TL0=0x00; //11��0592M ����Ϊ10ms
	TL1=0x00;//����������
	TH1=0x00;//����������
	TR0=1;   //�򿪶�ʱ��
	TR1=1;   //�򿪼�����
}
void conversion(uint temp_data)  
{  	 

    bai=temp_data/100+0x30 ;
    temp_data=temp_data%100;   //ȡ������
    shi=temp_data/10+0x30 ;
    ge=temp_data%10+0x30;      //ȡ������
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
	s2=0;           //��ʼ�趨S2����
	s3=0;           //��ʼ�趨S3����
}

