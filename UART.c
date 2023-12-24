/*
 * UART.c
 *
 *  Created on: Aug 30, 2023
 *      Author: orabi
 */


#include "UART.h"

#define Freq 				80000
#define Desired_Baud_Rate   96


void UART_Init(){

	//Set Tx pin output direction
	DIO_SetPinDirection(DIO_PORTD,DIO_PIN1,DIO_PIN_DIR_OUTPUT);
	//Set Rx pin input direction
	DIO_SetPinDirection(DIO_PORTD, DIO_PIN0, DIO_PIN_DIR_INPUT);

	//BaudRate calculation --> value to be input to down counter prescalar
	UBRRL = ((Freq)/(16*Desired_Baud_Rate)) - 1;

	//Enable Transmitter and Receiver
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);

	//Asynchronous Operation
	//Stop Bits -->1 bit
	//Disable Parity
	//8 data bits
	UCSRC = 0x86 ; //0b1000 0110

}


void UART_Tx(uint8 data){
	//put data we want to send in UDR register after that it will be shifted to output
	UDR = data;

	//keep looping until data buffer register is empty
	while(GET_BIT(UCSRA,5) != 1);
}

void UART_Tx_String(uint8 *data){
	uint8 counter = 0 ;

	while(data[counter] != '\0'){
		UART_Tx(data[counter]);
		counter++ ;
	}
}

uint8 UART_Rx(void){
	while(GET_BIT(UCSRA,7) != 1) ;

	return UDR ;
}
