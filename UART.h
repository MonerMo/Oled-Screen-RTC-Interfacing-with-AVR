/*
 * UART.h
 *
 *  Created on: Aug 30, 2023
 *      Author: orabi
 */

#ifndef UART_H_
#define UART_H_


#include "DIO.h"
#include "Atmega32_Registers.h"
#include "Bit_Operation.h"

void UART_Init();
void UART_Tx(uint8 data);
void UART_Tx_String(uint8 *data);
uint8 UART_Rx(void);


#endif /* UART_H_ */
