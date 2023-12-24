/*
 * HomemadeRTOS.c
 *
 *  Created on: Sep 6, 2023
 *      Author: orabi
 */

#include "HomemadeRTOS.h"

Task arr[NUM_TASKS] = {} ;


void TASK_CREATE(uint8 priority, uint8 period, void(*Func_ptr)(void)){
	arr[priority].Period = period ;
	arr[priority].Func_ptr = Func_ptr ;
}

void RED_BLINK(void){
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_DIR_OUTPUT);
	DIO_TogglePin(DIO_PORTD, DIO_PIN0);
}

void YEL_BLINK(void){
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN1, DIO_PIN_DIR_OUTPUT);
	DIO_TogglePin(DIO_PORTD, DIO_PIN1);
}

void GRE_BLINK(void){
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_DIR_OUTPUT);
	DIO_TogglePin(DIO_PORTD, DIO_PIN2);
}

void MOTOR(void){
	static sint8 flip = 1 ;

	DIO_SetPinDirection(DIO_PORTD, DIO_PIN3, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN4, DIO_PIN_DIR_OUTPUT);

	if(flip == 1){
		DIO_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_VAL_HIGH);
		DIO_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_VAL_LOW);
		flip *= -1 ;
	}else if(flip == -1){
		DIO_SetPinValue(DIO_PORTD,DIO_PIN3,DIO_PIN_VAL_LOW);
		DIO_SetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_VAL_HIGH);
		flip *= -1;
	}
}

void LCD(void){
	LCD_Init();

	static uint8 index = 0 ;
	static sint8 dir = 1 ;

	char *name = "Ahmed" ;
	if(index == 11 && dir == 1){
		dir *= -1 ;
		index += dir ;
		LCD_GoTo(0,index);
		LCD_WriteString(name);
	}else if(index == 0 && dir == -1){
		dir *= -1 ;
		index += dir ;
		LCD_GoTo(0,index);
		LCD_WriteString(name);
	}else if(index >= 0 && index < 11){
		LCD_GoTo(0,index);
		index += dir ;
		LCD_WriteString(name);
	}

}

void Scheduler(uint8 ticks){
	for(int i = 0 ; i < NUM_TASKS ; i++){
		if(ticks % arr[i].Period == 0){
			arr[i].Func_ptr();
		}
	}
}

