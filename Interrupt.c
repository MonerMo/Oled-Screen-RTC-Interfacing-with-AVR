/*
 * Interrupt.c
 *
 *  Created on: Aug 23, 2023
 *      Author: orabi
 */


#include "Interrupt.h"


void Interrupt_Init(void){

#if   GLOBAL_INTERRUPT_STATUS == GENERAL_INTERRUPT_ENABLE
	SET_BIT(SREG,7);
#elif GLOBAL_INTERRUPT_STATUS == GENERAL_INTERRUPT_DISABLE
	CLR_BIT(SREG,7);
#endif

}

void Interrupt0_Init(void){
	Interrupt_Init();

	//Enabling External Interrupt Request 0
	SET_BIT(GICR,6);

#if INTERRUPT0_TRIGGER == INTERRUPT_TRIGGER_LOW_LEVEL
	CLR_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
#elif INTERRUPT0_TRIGGER == INTERRUPT_TRIGGER_ANY_LOGICAL_CHANGE
	SET_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
#elif INTERRUPT0_TRIGGER == INTERRUPT_TRIGGER_RISING_EDGE
	SET_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#elif INTERRUPT0_TRIGGER == INTERRUPT_TRIGGER_FALLING_EDGE
	CLR_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#endif

}

void Interrupt1_Init(void){

	Interrupt_Init();

	//Enabling External Interrupt Request 1
	SET_BIT(GICR,7);

#if INTERRUPT1_TRIGGER == INTERRUPT_TRIGGER_LOW_LEVEL
	CLR_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);
#elif INTERRUPT1_TRIGGER == INTERRUPT_TRIGGER_ANY_LOGICAL_CHANGE
	SET_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);
#elif INTERRUPT1_TRIGGER == INTERRUPT_TRIGGER_RISING_EDGE
	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
#elif INTERRUPT1_TRIGGER == INTERRUPT_TRIGGER_FALLING_EDGE
	CLR_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
#endif

}

void Interrupt2_Init(void){

	Interrupt_Init();

	//Enabling External Interrupt Request 2
	SET_BIT(GICR,5);


//IF BIT.6 IN MCUCSR REGISTER IS LOW(0-BIT CLEARED) THEN INT2 ARE TRIGGERED IN FALLING EDGE MODE
//IF BIT.6 IN MCUCSR REGISTER IS HIGH(1-BIT SET) THEN INT2 ARE TRIGGERED IN RISING EDGE MODE
//PAGE.65 in DATASHEET
#if INTERRUPT2_TRIGGER == INTERRUPT_TRIGGER_FALLING_EDGE
	CLR_BIT(MCUCSR,6);
#elif INTERRUPT2_TRIGGER == INTERRUPT_TRIGGER_RISING_EDGE
	SET_BIT(MCUCSR,6);

#endif

}
