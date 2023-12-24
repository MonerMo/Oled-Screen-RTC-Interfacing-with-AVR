/*
 * Keypad.h
 *
 *  Created on: Aug 26, 2023
 *      Author: orabi
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Keypad_Config.h"
#include "Atmega32_Registers.h"
#include "STD.h"
#include "DIO.h"
#define F_CPU 16000000
#include <avr/delay.h>


#define ROW_INIT_PIN  		0
#define ROW_FINAL_PIN 		3

#define COL_INIT_PIN  		4
#define COL_FINAL_PIN 		7

#define BUTTON_PRESSED 		0
#define BUTTON_NOT_PRESSED 	1



//Functions
//In this functions we want to make ROW pins to be input and pullup res
//is activated on the pins , After that we want to make the columns pins
//work as an output pins that outputs high and when the column index is called
//output low so when the button is pressed the row pins gets low and we can
//know that the button is pressed
void  Keypad_Init(void);
uint8 Keypad_Val(void);


#endif /* KEYPAD_H_ */
