/*
 * Timer1.h
 *
 *  Created on: Aug 29, 2023
 *      Author: orabi
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "Atmega32_Registers.h"
#include "DIO.h"
#include "Bit_Operation.h"



void Timer1_Init(void);
void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_Generate(uint16 Duty , uint16 Top);

#endif /* TIMER1_H_ */
