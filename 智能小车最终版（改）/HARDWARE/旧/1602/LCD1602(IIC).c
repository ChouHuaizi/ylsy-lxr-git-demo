#include "IIC.h"

#define adress_1602 0x4e  


unsigned char LCD_data=0x08;


//bit ack;
			 
sbit SCL = P0^0;//定义两个数据端口
sbit SDA = P0^1;

/**************************************
发送IIC总线起始信号
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
发送IIC总线结束信号
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
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void IIC_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay1us(5);                 //延时
    SCL = 0;                    //拉低时钟线
    Delay1us(5);                  //延时
}
/**************************************
从IIC总线发送一个字节数据
**************************************/
void IIC_SendByte(unsigned char c)
{
	unsigned char BitCnt;
	for(BitCnt=0;BitCnt<8;BitCnt++)  //要传送的数据长度为8位
	{
		if((c<<BitCnt)&0x80)  SDA=1;   //判断发送位
		else  SDA=0;                
		_nop_();
		SCL=1;               //置时钟线为高，通知被控器开始接收数据位
		Delay1us(4);; 
		_nop_();       
		SCL=0; 
	}  
	_nop_();
	_nop_();
	SDA=1;               //8位发送完后释放数据线，准备接收应答位
	_nop_();
	_nop_();  
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	if(SDA==1)ack=0;     
	else ack=1;        //判断是否接收到应答信号                    
	SCL=0;
	_nop_();
	_nop_();
}
/**************************************
从IIC总线发送一个随机地址数据
**************************************/
int Write_Random_Address_Byte(unsigned char add,unsigned char dat)
{
	IIC_Start();    //启动总线
	IIC_SendByte(add); //发送器件地址
	if(ack==0)return(0);
	IIC_SendByte(dat);   //发送数据
	if(ack==0)return(0);
	IIC_Stop(); //结束总线
	return(1);
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
int  IIC_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay1us(5);             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay1us(5);             //延时
    }
    return dat;
}
//********************液晶屏使能*********************
void Enable_LCD_write()
{
	LCD_data|=(1<<(3-1));//E=1;
	Write_Random_Address_Byte(adress_1602,LCD_data);  //
	Delay1us(2);
	LCD_data&=~(1<<(3-1));//E=0;
	Write_Random_Address_Byte(adress_1602,LCD_data);
}
/*------------------------------------------------
              写入命令函数
------------------------------------------------*/
void LCD_write_command(unsigned char command) 
{ 
	Delay1us(16);
	LCD_data&=~(1<<(1-1));//RS=0;
	LCD_data&=~(1<<(2-1));//RW=0;
	//LCD_data&=~(1<<(4-1));
	Write_Random_Address_Byte(adress_1602,LCD_data);
	
	LCD_data&=0X0f; //清高四位
	LCD_data|=command & 0xf0; //写高四位
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
	
	command=command<<4; //低四位移到高四位
	LCD_data&=0x0f; //清高四位
	LCD_data|=command&0xf0; //写低四位
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
}
/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
void LCD_write_dat(unsigned char value) 
{ 
	Delay1us(16);
	LCD_data|=(1<<(1-1));//RS=1;
	LCD_data&=~(1<<(2-1));//RW=0;
	Write_Random_Address_Byte(adress_1602,LCD_data);
	
	LCD_data&=0X0f; //清高四位
	LCD_data|=value&0xf0; //写高四位
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();         
	
	value=value<<4; //低四位移到高四位
	LCD_data&=0x0f; //清高四位
	LCD_data|=value&0xf0; //写低四位
	Write_Random_Address_Byte(adress_1602,LCD_data);
	Enable_LCD_write();
}

/*------------------------------------------------
                清屏函数
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	LCD_write_command(0x01); 
	Delay1ms(2);
}

/*------------------------------------------------
                设置显示位置
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
                显示一个字符
------------------------------------------------*/
void LCD_dsp_char( unsigned x,unsigned char y,unsigned char dat)
{
	LCD_set_xy( x, y ); 
	LCD_write_dat(dat);
}

/*------------------------------------------------
                显示字符串函数
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
              把特殊字符数据写入显存
------------------------------------------------*/
//void WriteCGRAM()
//{
//	unsigned char i,j,k,tmp;
//	tmp=0x40;//设置CGRAM地址的格式字
//	k=0;
//	
//	for(j=0;j<8;j++)
//	{
//		for(i=0;i<8;i++)
//		{
//			LCD_write_command(tmp+i); // 设置自定义字符的 CGRAM 地址 
//			Delay1us(50);
//			LCD_write_dat(table0[k]); // 向CGRAM写入自定义字符表的数据
//			k++;
//			Delay1us(50);
//		}
//		tmp=tmp+8;
//	}
//}
/*------------------------------------------------
              初始化函数
------------------------------------------------*/
void LCD_Init(void) 
{
	LCD_write_command(0x02);
	Delay1us(40);
	LCD_write_command(0x28); //4位显示！！！！！！！！！！！！！！！！！！
	LCD_write_command(0x0c); //显示开
	LCD_write_command(0x01); //清屏
	Delay1ms(10);
}