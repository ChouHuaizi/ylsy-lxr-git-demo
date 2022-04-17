#include "IIC.h"

#define adress_1602 0x4e  


unsigned char LCD_data=0x08;


//bit ack;
			 
sbit SCL = P0^0;//�����������ݶ˿�
sbit SDA = P0^1;

/**************************************
����IIC������ʼ�ź�
**************************************/
void IIC_Start()
{
	SDA=1;
	Delay1us(4);
	SCL=1;
	Delay1us(4);
	SDA=0;
	Delay1us(4);
	SCL=0;
	Delay1us(4);
}
/**************************************
����IIC���߽����ź�
**************************************/
void IIC_Stop()
{
	SCL=0;
	Delay1us(4);
	SDA=0;
	Delay1us(4);
	SCL=1;
	Delay1us(4);
	SDA=1;
	Delay1us(4);
}
/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay1us(5);                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay1us(5);                  //��ʱ
}
/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void IIC_SendByte(unsigned char c)
{
	unsigned char BitCnt;
	for(BitCnt=0;BitCnt<8;BitCnt++)  //Ҫ���͵����ݳ���Ϊ8λ
	{
		if((c<<BitCnt)&0x80)  SDA=1;   //�жϷ���λ
		else  SDA=0;                
		_nop_();
		SCL=1;               //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
		Delay1us(4);; 
		_nop_();       
		SCL=0; 
	}  
	_nop_();
	_nop_();
	SDA=1;               //8λ��������ͷ������ߣ�׼������Ӧ��λ
	_nop_();
	_nop_();  
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	if(SDA==1)ack=0;     
	else ack=1;        //�ж��Ƿ���յ�Ӧ���ź�                    
	SCL=0;
	_nop_();
	_nop_();
}
/**************************************
��IIC���߷���һ�������ַ����
**************************************/
int Write_Random_Address_Byte(unsigned char add,unsigned char dat)
{
	IIC_Start();    //��������
	IIC_SendByte(add); //����������ַ
	if(ack==0)return(0);
	IIC_SendByte(dat);   //��������
	if(ack==0)return(0);
	IIC_Stop(); //��������
	return(1);
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
int  IIC_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay1us(5);             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay1us(5);             //��ʱ
    }
    return dat;
}
//********************Һ����ʹ��*********************
void Enable_LCD_write()
{
	LCD_data|=(1<<(3-1));//E=1;
	Write_Random_Address_Byte(adress_1602,LCD_data);  //
	Delay1us(2);
	LCD_data&=~(1<<(3-1));//E=0;
	Write_Random_Address_Byte(adress_1602,LCD_data);
}
/*------------------------------------------------
              д�������
------------------------------------------------*/
void LCD_write_command(unsigned char command) 
{ 
	Delay1us(16);
	LCD_data&=~(1<<(1-1));//RS=0;
	LCD_data&=~(1<<(2-1));//RW=0;
	//LCD_data&=~(1<<(4-1));
	Write_Random_Address_Byte(adress_1602,LCD_data);
	
	LCD_data&=0X0f; //�����λ
	LCD_data|=command & 0xf0; //д����λ
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
	
	command=command<<4; //����λ�Ƶ�����λ
	LCD_data&=0x0f; //�����λ
	LCD_data|=command&0xf0; //д����λ
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
}
/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
void LCD_write_dat(unsigned char value) 
{ 
	Delay1us(16);
	LCD_data|=(1<<(1-1));//RS=1;
	LCD_data&=~(1<<(2-1));//RW=0;
	Write_Random_Address_Byte(adress_1602,LCD_data);
	
	LCD_data&=0X0f; //�����λ
	LCD_data|=value&0xf0; //д����λ
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();         
	
	value=value<<4; //����λ�Ƶ�����λ
	LCD_data&=0x0f; //�����λ
	LCD_data|=value&0xf0; //д����λ
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
}

/*------------------------------------------------
                ��������
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	LCD_write_command(0x01); 
	Delay1ms(2);
}

/*------------------------------------------------
                ������ʾλ��
------------------------------------------------*/
void LCD_set_xy( unsigned char x, unsigned char y )
{
	unsigned char address;
	if (y == 1) 
	address = 0x80 + x;
	else 
	address =0xc0+ x;
	LCD_write_command(address); 
}

/*------------------------------------------------
                ��ʾһ���ַ�
------------------------------------------------*/
void LCD_dsp_char( unsigned x,unsigned char y,unsigned char dat)
{
	LCD_set_xy( x, y ); 
	LCD_write_dat(dat);
}

/*------------------------------------------------
                ��ʾ�ַ�������
------------------------------------------------*/
void LCD_dsp_string(unsigned char X,unsigned char Y,unsigned char *s)
{
	LCD_set_xy( X, Y ); 
	while (*s) 
	{
		LCD_write_dat(*s);   
		s ++;
	}
}
/*------------------------------------------------
              �������ַ�����д���Դ�
------------------------------------------------*/
//void WriteCGRAM()
//{
//	unsigned char i,j,k,tmp;
//	tmp=0x40;//����CGRAM��ַ�ĸ�ʽ��
//	k=0;
//	
//	for(j=0;j<8;j++)
//	{
//		for(i=0;i<8;i++)
//		{
//			LCD_write_command(tmp+i); // �����Զ����ַ��� CGRAM ��ַ 
//			Delay1us(50);
//			LCD_write_dat(table0[k]); // ��CGRAMд���Զ����ַ��������
//			k++;
//			Delay1us(50);
//		}
//		tmp=tmp+8;
//	}
//}
/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
{
	LCD_write_command(0x02);
	Delay1us(40);
	LCD_write_command(0x28); //4λ��ʾ������������������������������������
	LCD_write_command(0x0c); //��ʾ��
	LCD_write_command(0x01); //����
	Delay1ms(10);
}