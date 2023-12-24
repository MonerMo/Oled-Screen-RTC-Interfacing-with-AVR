/*
 * DIO.h
 *
 *  Created on: Aug 20, 2023
 *      Author: orabi
 */

#ifndef DIO_H_
#define DIO_H_

#include "STD.h"
#include "Atmega32_Registers.h"
#include "Bit_Operation.h"

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN0  0
#define DIO_PIN1  1
#define DIO_PIN2  2
#define DIO_PIN3  3
#define DIO_PIN4  4
#define DIO_PIN5  5
#define DIO_PIN6  6
#define DIO_PIN7  7

#define DIO_PIN_DIR_INPUT   0
#define DIO_PIN_DIR_OUTPUT  1

#define DIO_PIN_VAL_LOW     0
#define DIO_PIN_VAL_HIGH    1

#define DIO_PORT_DIR_INPUT  0x00
#define DIO_PORT_DIR_OUTPUT 0xFF

#define DIO_PORT_VAL_LOW    0x00
#define DIO_PORT_VAL_HIGH   0xFF

//we want to make for each of the pin and port
//1.setting direction function ( for pin and port )
//2.setting value function ( for pin and port )
//3.getting the value ( for pin and port )
//4.toggling ( for pin )
//1.1 setting direction for port will take the port and the direction type
//1.2 setting direction for pin will take the port , pin and direction type
//2.1 setting value for the whole port will take the port and the value
//2.2 setting value for a specific pin will take the port , pin and the value
//3.1 getting value inside the whole port by sending a reference to variable the argument will be a pointer to char
//3.2 getting value inside a specific pin using same technique as port
//4.1 toggling value inside a pin
//5.1 Set Pullup Resistor

void DIO_SetPortDirection(uint8 Port, uint8 Direction);
void DIO_SetPinDirection(uint8 Port, uint8 Pin, uint8 Direction);
void DIO_SetPortValue(uint8 Port, uint8 Value);
void DIO_SetPinValue(uint8 Port, uint8 Pin, uint8 Value);

void DIO_GetPortValue(uint8 Port, uint8 *Value);
void DIO_GetPinValue(uint8 Port, uint8 Pin, uint8 *Value);
void DIO_TogglePin(uint8 Port, uint8 Pin);
void DIO_SetPullUpRes(uint8 Port, uint8 Pin);


#endif /* DIO_H_ */
