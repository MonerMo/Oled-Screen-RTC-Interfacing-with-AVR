/*
 * Watchdog.h
 *
 *  Created on: Aug 29, 2023
 *      Author: orabi
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_


#include "Bit_Operation.h"
#include "Atmega32_Registers.h"

void WDT_On(void){
	SET_BIT(WDTCR,3);

	SET_BIT(WDTCR,0);
	SET_BIT(WDTCR,1);
	SET_BIT(WDTCR,2);
}

void WDT_Off(void){
	SET_BIT(WDTCR,4);
	SET_BIT(WDTCR,3);

	CLR_BIT(WDTCR,3);
}

#endif /* WATCHDOG_H_ */
