/*
 * Interrupt.h
 *
 *  Created on: Aug 23, 2023
 *      Author: orabi
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "Interrupt_Config.h"
#include "Atmega32_Registers.h"
#include "Bit_Operation.h"


#define GENERAL_INTERRUPT_ENABLE  1
#define GENERAL_INTERRUPT_DISABLE 0


#define INTERRUPT_TRIGGER_LOW_LEVEL 			0
#define INTERRUPT_TRIGGER_ANY_LOGICAL_CHANGE    1
#define INTERRUPT_TRIGGER_RISING_EDGE			2
#define INTERRUPT_TRIGGER_FALLING_EDGE          3


void Interrupt_Init(void);
void Interrupt0_Init(void);
void Interrupt1_Init(void);
void Interrupt2_Init(void);



#endif /* INTERRUPT_H_ */
