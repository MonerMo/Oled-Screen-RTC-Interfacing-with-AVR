/*
 * Timers.h
 *
 *  Created on: Aug 27, 2023
 *      Author: orabi
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "Atmega32_Registers.h"
#include "DIO.h"
#include "Bit_Operation.h"

#define Timer0_MODE  Timer0_NORMAL_MODE

#define Timer0_NORMAL_MODE 		0
#define Timer0_CTC_MODE    		1
#define Timer0_FAST_PWM_MODE    2


void Timer0_Init(void);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_delay_ms(uint32 delay_ms);
void Fast_PWM_Motor(uint8 OCR);


//for study table project
void minute_delay(void);






#endif /* TIMERS_H_ */
