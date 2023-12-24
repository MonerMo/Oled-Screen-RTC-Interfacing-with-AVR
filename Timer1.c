/*
 * Timer1.c
 *
 *  Created on: Aug 29, 2023
 *      Author: orabi
 */

#include "Timer1.h"

void Timer1_Init(void){

	//make pin5 on portd output
	SET_BIT(DDRD,5);

	//fast pwm , TOP -->ICR1 , COMPARE-->OCR1A
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);

	//Non inverted fast pwm
	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);

}


void Timer1_Start(void){
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
}
void Timer1_Stop(void){
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}


void Timer1_Generate(uint16 Duty , uint16 Top){
	OCR1A = Duty ;
	ICR1 = Top ;
}
