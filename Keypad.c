/*
 * Keypad.c
 *
 *  Created on: Aug 26, 2023
 *      Author: orabi
 */
#include "Keypad.h"


uint8 KEYPAD_ARR[4][4] = {
		{7,8,9,0},
		{4,5,6,0},
		{1,2,3,0},
		{0,0,0,0}
};

void Keypad_Init(void){

	//Make ROW Pins as an input
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN0,DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN1,DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN2,DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN3,DIO_PIN_DIR_INPUT);

	//Activate Pull Up Resistors on the input pins
	DIO_SetPullUpRes(KEYPAD_PORT, DIO_PIN0);
	DIO_SetPullUpRes(KEYPAD_PORT, DIO_PIN1);
	DIO_SetPullUpRes(KEYPAD_PORT, DIO_PIN2);
	DIO_SetPullUpRes(KEYPAD_PORT, DIO_PIN3);

	//Make COL Pins as an output
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN4,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN5,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN6,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT,DIO_PIN7,DIO_PIN_DIR_OUTPUT);

	//Make COL Pins output high value
	DIO_SetPinValue(KEYPAD_PORT, DIO_PIN4, DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, DIO_PIN5, DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, DIO_PIN6, DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, DIO_PIN7, DIO_PIN_VAL_HIGH);


}



uint8 Keypad_Val(void){
	//Here in this function we want to loop through the columns pins first
	uint8 COL_PIN = 0 ;
	uint8 ROW_PIN = 0 ;

	uint8 BUTTON = 1 ;
	static uint8 VAL = 0 ;

	for(COL_PIN = COL_INIT_PIN ;COL_PIN <= COL_FINAL_PIN; COL_PIN++){

		DIO_SetPinValue(KEYPAD_PORT,COL_PIN,DIO_PIN_VAL_LOW);

		for(ROW_PIN = ROW_INIT_PIN ;ROW_PIN <= ROW_FINAL_PIN; ROW_PIN++){

			DIO_GetPinValue(KEYPAD_PORT, ROW_PIN, &BUTTON);

			if(BUTTON == BUTTON_PRESSED){
				VAL = KEYPAD_ARR[ROW_PIN][COL_PIN-COL_INIT_PIN];

				while(BUTTON == BUTTON_PRESSED)
					DIO_GetPinValue(KEYPAD_PORT, ROW_PIN, &BUTTON);

			}else if(BUTTON == BUTTON_NOT_PRESSED){
				VAL = 99 ;
			}
		}

		DIO_SetPinValue(KEYPAD_PORT,COL_PIN,DIO_PIN_VAL_HIGH);
	}

	return VAL ;
}
