//IIC.h
#ifndef __IIC_H
#define __IIC_H 
#define adress_1602 0x4e  //0x7e(PCF8574AT)   0x4e(PCF8574T)
#include "reg52.h"
#include "intrins.h"
void IIC_Start();
void IIC_Stop();
void IIC_SendACK(bit ack);
void IIC_SendByte(unsigned char c);
int Write_Random_Address_Byte(unsigned char add,unsigned char dat);
int IIC_RecvByte();
void Enable_LCD_write();
void LCD_write_command(unsigned char command);
void LCD_write_dat(unsigned char value);
void LCD_Clear(void);
void LCD_set_xy( unsigned char x, unsigned char y );
void LCD_dsp_char( unsigned x,unsigned char y,unsigned char dat);
void LCD_dsp_string(unsigned char X,unsigned char Y,unsigned char *s);
void LCD_Init(void);

#endif 