/*
 * I2C.c
 *
 *  Created on: Sep 5, 2023
 *      Author: orabi
 */

#include "I2C.h"

void I2C_Init(void){
	//for 100 KHz communication speed
	TWBR = 32 ;
	//TWBR = 72 ;
}

uint8 I2C_Start(uint8 Slave_Address_W){
	uint8 status = 0x00 ;

	//0b10100100 -- Make TWINT bit = 0 , Generate Start bit , I2C Enable
	TWCR = 0b10100100 ;

	//wait until TWI finished generating start bit by checking TWI interrupt bit
	while(GET_BIT(TWCR,7) == 0);

	//get value inside status ( DON'T forget to mask Prescalar bits ) ( you need 5 MSB bits only )
	status = TWSR & 0xF8 ;

	if(status != 0x08)
		return 0 ; //signal tells us that START bit failed

	//load Slave_Address to write to in TWDR - Data register
	TWDR = Slave_Address_W ;

	//Make TWINT bit = 0 , I2C Enable
	TWCR = 0b10000100 ;

	//wait until making sure address has been sent
	while(GET_BIT(TWCR,7) == 0);

	status = TWSR & 0xF8 ;

	if(status == 0x18)
		return 1 ; //slave address + Write bit has been transmitted + ACK

	if(status == 0x20)
		return 2 ; //slave address + Write bit has been transmitted + NACK
	else
		return 3 ; //slave address + Write bit failed



}

uint8 I2C_Repeated_Start(uint8 Slave_Address_R){
	uint8 status = 0x00 ;

	//0b10100100 -- Make TWINT bit = 0 , Generate Start bit , I2C Enable
	TWCR = 0b10100100 ;

	//wait until TWI finished generating start bit by checking TWI interrupt bit
	while(GET_BIT(TWCR,7) == 0);

	//get value inside status ( DON'T forget to mask prescaler bits ) ( you need 5 MSB bits only )
	status = TWSR & 0xF8 ;

	//repeated start not transmitted
	if(status != 0x10)
		return 0 ;

	//load Slave_Address to write to in TWDR - Data register
	TWDR = Slave_Address_R ;

	//Make TWINT bit = 0 , I2C Enable
	TWCR = 0b10000100 ;

	//wait until making sure address has been sent
	while(GET_BIT(TWCR,7) == 0);

	status = TWSR & 0xF8 ;

	if(status == 0x40)
		return 1 ; //SLA+R transmitted and ACK received
	if(status == 0x48)
		return 2 ; //SLA+R transmitted and NACK received
	else
		return 3 ; //SLA+R transmission failed


}

uint8 I2C_Write(uint16 Data){
	uint8 status = 0x00 ;

	//Load data or address in TWDR
	TWDR = Data ;

	//Make TWINT bit = 0 , I2C Enable
	TWCR = 0b10000100 ;

	//wait until making sure data or address has been sent
	while(GET_BIT(TWCR,7) == 0);

	status = TWSR & 0xF8 ;

	if(status == 0x28)
		return 0 ; // data has been sent and ACK received
	if(status == 0x30)
		return 1 ; // data has been sent and NACK received
	else
		return 2 ; // data transmission failed

}

uint8 I2C_Read_ACK(void){

	//Send Acknowledgment , Set TWINT bit to zero , enable I2C
	TWCR = 0b11000100 ;

	while(GET_BIT(TWCR,7) == 0);

	return TWDR ;
}

uint8 I2C_Read_NACK(void){
	//Send NOT Acknowledgment , Set TWINT bit to zero , enable I2C
	TWCR = 0b10000100 ;

	while(GET_BIT(TWCR,7) == 0);

	return TWDR ;
}

void  I2C_Stop(void){
	TWCR = 0b10010100 ;

	while(GET_BIT(TWCR,4) == 1);
}

