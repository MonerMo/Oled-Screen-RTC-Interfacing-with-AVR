/*
 * HomemadeRTOS.h
 *
 *  Created on: Sep 6, 2023
 *      Author: orabi
 */

#ifndef HOMEMADERTOS_H_
#define HOMEMADERTOS_H_

#include "Atmega32_Registers.h"
#include "DIO.h"
#include "Bit_Operation.h"
#include "LCD.h"

#define NUM_TASKS 5


typedef struct{
	uint8 Period ;
	void (*Func_ptr)(void) ;
}Task;


void TASK_CREATE(uint8 priority, uint8 period, void(*Func_ptr)(void)) ;

void RED_BLINK(void);
void YEL_BLINK(void);
void GRE_BLINK(void);
void MOTOR(void);
void LCD(void);

void Scheduler(uint8 ticks);



#endif /* HOMEMADERTOS_H_ */
