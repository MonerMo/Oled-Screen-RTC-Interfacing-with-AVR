/*
 * Timers.c
 *
 *  Created on: Aug 27, 2023
 *      Author: orabi
 */


#include "Timer0.h"

uint32 NUM_OVF = 0 ;
uint32 INIT_VAL = 0 ;


void Timer0_Init(void){
#if Timer0_MODE == Timer0_NORMAL_MODE

	//Choosing normal mode
	CLR_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);

	//Enable Global Interrupt
	//SET_BIT(SREG,7);

	//Enable overflow Interrupt
	//Timer/Counter0 Overflow Interrupt Enable
	SET_BIT(TIMSK,0);
	CLR_BIT(TIMSK,1);

#elif Timer0_MODE == Timer0_CTC_MODE

	//Choosing Compare mode
	SET_BIT(TCCR0,3);
	CLR_BIT(TCCR0,6);


	//Enable Global Interrupt
	SET_BIT(SREG,7);

	//Enable Compare Interrupt
	SET_BIT(TIMSK,1);
	CLR_BIT(TIMSK,0);

	//Prescalling to Osc/1024
	SET_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	SET_BIT(TCCR0,2);

	//for 32 ms
	OCR0 = 255 ;

#elif Timer0_MODE == Timer0_FAST_PWM_MODE

	//Set OC0 pin direction to output
	SET_BIT(DDRB,3);


	//For fast PWM
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);

	//Enable Global Interrupt
	SET_BIT(SREG,7);

	//Non-Inverted Fast PWM
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);

#elif Timer0_MODE == Timer0_Servo_Control
	//Set OC0 pin direction to output
	//SET_BIT(DDRB,3);

	//For fast pwm
	SET_BIT(TCCR0,3);
	SET_BIT(TCCR0,6);

	//Enable Global Interrupt
	SET_BIT(SREG,7);

	//Non-Inverted Fast PWM
	CLR_BIT(TCCR0,4);
	SET_BIT(TCCR0,5);



#endif
}

void Timer0_Start(void){

	SET_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	SET_BIT(TCCR0,2);
}

void Timer0_Stop(void){
	CLR_BIT(TCCR0,0);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,2);
}

void Timer0_delay_ms(uint32 delay_ms){
	uint8 Tick_Time = 1024/8 ; //this time is in micro seconds
	uint32 Total_Ticks = (delay_ms*1000) / Tick_Time ;
	NUM_OVF = Total_Ticks / 256 ;

#if Timer0_MODE == Timer0_NORMAL_MODE

	INIT_VAL = 256 - (Total_Ticks % 256) ;
	TCNT0 = INIT_VAL ;

#elif Timer0_MODE == Timer0_CTC_MODE

	INIT_VAL = Total_Ticks % 256 ;
	OCR0 = INIT_VAL ;
#endif
}


void minute_delay(void){
	Timer0_Init();
	Timer0_Start();


	//we will set number of overflows
	sint16 ovf_for_min = 1830 ;
	while(ovf_for_min > 0){
		if(GET_BIT(TIFR,0) == 1){
			ovf_for_min-- ;
			SET_BIT(TIFR,0) ;
		}
	}

	Timer0_Stop();
}



void Fast_PWM_Motor(uint8 OCR){
	OCR0 = OCR ;
}
