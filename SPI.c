/*
 * SPI.c
 *
 *  Created on: Aug 31, 2023
 *      Author: orabi
 */


#include "SPI.h"

void  SPI_Master_Init(void){
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_DIR_OUTPUT);

	//SPI Enable
	//SET_BIT(SPCR,6);

	//LSB send first
	//SET_BIT(SPCR,5);

	//Master Select
	//SET_BIT(SPCR,4);

	//CPOL = 0 --> Rising then Falling , CPHA = 0 -->Sample then Setup .
	//CLR_BIT(SPCR,3);
	//CLR_BIT(SPCR,2);

	//CLK/128
	//SET_BIT(SPCR,0);
	//SET_BIT(SPCR,1);

	SPCR =  0x53;

}
void  SPI_Slave_Init(void){
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN4, DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN5, DIO_PIN_DIR_INPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN6, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_DIR_INPUT);

	//SPI Enable
	//SET_BIT(SPCR,6);

	//LSB send first
	//SET_BIT(SPCR,5);

	//Slave Select
	//CLR_BIT(SPCR,4);

	SPCR = 0x40 ;


}

void  SPI_Transmit_Start(void){
	DIO_SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_VAL_LOW);
}

void  SPI_Transmit_Term(void){
	DIO_SetPinValue(DIO_PORTB,DIO_PIN4,DIO_PIN_VAL_HIGH);
}

uint8 SPI_Data_Transmit(uint8 data){
	SPDR = data ;

	while(GET_BIT(SPSR,7) == 0);

	uint8 received_data = 0 ;
	received_data = SPDR ;

	return received_data ;

}
