#ifndef __1602_LCD_H
#define __1602_LCD_H
#include "sys.h"
void delay1(int y);
void IIC_start(void);
void IIC_writeByte(char temp);
void LCD_write_command(char comm);
void LCD_write_data(char data1);
void Init_Lcd(void);
void Write_LCD(int x, int y, char *str);
//void LCD_write_word(unsigned char *s) ;
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);




#endif /*__1602_LCD_H*/

