/*
 * LCD.c
 *
 *  Created on: Aug 26, 2023
 *      Author: orabi
 */
#include "LCD.h"

void LCD_Init(void){
#if LCD_MODE == 8
	//Make Data port OUTPUT
	DIO_SetPortDirection(LCD_8BIT_DATA_PORT,DIO_PORT_DIR_OUTPUT);

	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_DIR_OUTPUT);

	LCD_WriteCommand(0x38); //if you sent this to command reg (8bit lcd)
	LCD_WriteCommand(0x0C); //Display ON , Cursor OFF
	LCD_WriteCommand(0x01); //Clear LCD screen
	LCD_WriteCommand(0x02); //Return Cursor to HOME

#elif LCD_MODE == 4
	DIO_SetPinDirection(LCD_8BIT_DATA_PORT,LCD_D4_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_DATA_PORT,LCD_D5_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_DATA_PORT,LCD_D6_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_DATA_PORT,LCD_D7_PIN,DIO_PIN_DIR_OUTPUT);

	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_DIR_OUTPUT);

	LCD_WriteCommand(0x33); //For 4bit mode
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);

	LCD_WriteCommand(0x0C); //Display ON , Cursor OFF
	LCD_WriteCommand(0x01); //Clear LCD screen
	LCD_WriteCommand(0x02); //Return Cursor to HOME

#endif
}


void LCD_WriteCommand(uint8 cmd){

#if LCD_MODE == 8

	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);

	//Put Command on Data/command port
	DIO_SetPortValue(LCD_8BIT_DATA_PORT,cmd);

	//Latch
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);


#elif LCD_MODE == 4
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);

	//Send Highest nibble first
	LCD_4BIT_DATA_PORT = (LCD_4BIT_DATA_PORT & 0x0f)|(cmd & 0xf0) ;
	//Latch the highest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	//Stop Latch to send lowest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);

	//Send Highest nibble first
	LCD_4BIT_DATA_PORT = (LCD_4BIT_DATA_PORT & 0x0f)|(cmd<<4) ;
	//Latch the highest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	//Stop Latch to send lowest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);

#endif

}


void LCD_WriteChar(uint8 ch){
#if LCD_MODE == 8

	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);

	//Put Command on Data/command port
	DIO_SetPortValue(LCD_8BIT_DATA_PORT,ch);

	//Latch
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);

#elif LCD_MODE == 4

	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RS_PIN,DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_RW_PIN,DIO_PIN_VAL_LOW);
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);

	//Send Highest nibble first
	LCD_4BIT_DATA_PORT = (LCD_4BIT_DATA_PORT & 0x0f)|(ch & 0xf0) ;
	//Latch the highest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	//Stop Latch to send lowest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);

	//Send Highest nibble first
	LCD_4BIT_DATA_PORT = (LCD_4BIT_DATA_PORT & 0x0f)|(ch<<4) ;
	//Latch the highest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_HIGH);
	_delay_ms(1);
	//Stop Latch to send lowest nibble
	DIO_SetPinValue(LCD_8BIT_CONTROL_PORT,LCD_E_PIN,DIO_PIN_VAL_LOW);
	_delay_ms(1);

#endif

}

void LCD_WriteString(uint8 *str){
	while(*str != '\0'){
		LCD_WriteChar(*str);
		str++ ;
	}
}


void LCD_GoTo(uint8 row,uint8 col){
	if(row == 0){
		uint8 cmd = 0x80 + col ;
		LCD_WriteCommand(cmd);
	}else if(row == 1){
		uint8 cmd = 0xC0 + col ;
		LCD_WriteCommand(cmd);
	}
}


void LCD_WriteInteger(sint32 num){
	uint32 reversed = 0 ;
	uint8 num_length = 0 ;

	if(num == 0){
		LCD_WriteChar('0');
	}

	if(num < 0){
		num *= -1 ;
		LCD_WriteChar('-');
	}

	while(num != 0){
		reversed = reversed + num%10;
		num_length++ ;

		num = num / 10 ;
		if(num != 0)
			reversed = reversed * 10 ;
	}



	while(reversed != 0){
		uint8 digit = reversed %10 ;
		LCD_WriteChar(digit + '0');
		reversed = reversed / 10 ;
		num_length--;
	}

	while(num_length !=0){
		LCD_WriteChar('0');
		num_length--;
	}

}


void LCD_Clear(void){
	LCD_WriteCommand(0x01);
}
