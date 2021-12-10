#ifndef __AVR_ATmega328__
#define __AVR_ATmega328__
#endif

#include <avr/io.h>
#include <util/delay.h>

void LCD_SendLowerNibble(unsigned char data) {
    LCD_Port = (LCD_Port & 0x0F) | (data << 4) | (1 << LCD_EN);
    _delay_us(1);
    LCD_Port &= ~(1 << LCD_EN);
    _delay_ms(2);
}

void LCD_SendByte(unsigned char data) {
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0) | (1 << LCD_RS) | (1 << LCD_EN);
    _delay_us(1);
    LCD_Port &= ~(1 << LCD_EN);
    _delay_us(200);
    LCD_SendLowerNibble(data);
}

void LCD_SendCmd(unsigned char data) {
    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0) | (1 << LCD_EN);
    LCD_Port &= ~(1 << LCD_RS);
    _delay_us(1);
    LCD_Port &= ~(1 << LCD_EN);

    _delay_us(200);
    LCD_SendLowerNibble(data);
}

void LCD_Init(void) {
    LCD_Dir = 0xFF;         // Make LCD port direction as o/p
    _delay_ms(20);          // Power ON time

    LCD_SendCmd(0x02);      // Send bits to init LCD
    LCD_SendCmd(0x02);      // Send bits to init LCD
    LCD_SendCmd(0x28);      // 2 line, 5*7 matrix in 4-bit mode
    LCD_SendCmd(0x0c);      // Display on cursor off
    LCD_SendCmd(0x06);      // Shift cursor to right
    LCD_SendCmd(0x01);      // Clear display screen
    _delay_ms(2);
}

void LCD_String(char *str) {
    short int i;
    for (i = 0; str[i] != 0; i++) {
        LCD_SendByte(str[i]);
    }
}

void LCD_String_xy(char row, char pos, char *str) {
    if (row == 0 && pos < 16)       LCD_SendCmd((pos & 0x0F) | 0x80);
    else if (row == 1 && pos < 16)  LCD_SendCmd((pos & 0x0F) | 0xC0);
    LCD_String(str);
}

void LCD_Clear() {
    LCD_SendCmd(0x01);
    _delay_ms(2);
    LCD_SendCmd(0x80);
}

void LCD_GoTo2ndLine()
{
    LCD_SendCmd(0xC0);
}

void LCD_GoTo1stLine()
{
    LCD_SendCmd(0x80);
}
