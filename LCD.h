/*
 * LCD.h
 *
 *  Created on: Aug 26, 2023
 *      Author: orabi
 */

#ifndef LCD_H_
#define LCD_H_
#include "DIO.h"

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/delay.h>

#define LCD_MODE 4

#define LCD_8BIT_DATA_PORT 		DIO_PORTA
#define LCD_8BIT_CONTROL_PORT   DIO_PORTD

#define LCD_RS_PIN				DIO_PIN1
#define LCD_RW_PIN				DIO_PIN2
#define LCD_E_PIN				DIO_PIN3

#define LCD_D4_PIN				DIO_PIN4
#define LCD_D5_PIN				DIO_PIN5
#define LCD_D6_PIN 				DIO_PIN6
#define LCD_D7_PIN				DIO_PIN7


#define LCD_4BIT_DATA_PORT  	(*(volatile uint8*)(0x3B))
#define LCD_4BIT_CONTROL_PORT	(*(volatile uint8*)(0x38))

void LCD_Init(void);
void LCD_WriteCommand(uint8 cmd);
void LCD_WriteChar(uint8 ch);
void LCD_WriteString(uint8 *str);
void LCD_GoTo(uint8 row,uint8 col);
void LCD_WriteInteger(sint32 num);
void LCD_Clear(void);


#endif /* LCD_H_ */
