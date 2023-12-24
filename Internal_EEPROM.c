/*
 * Internal_EEPROM.c
 *
 *  Created on: Dec 4, 2023
 *      Author: orabi
 */
#include "Internal_EEPROM.h"


void eeprom_address(uint16 address){
	EEARL = 0x00 | address ;
	EEARH = (address>>8);
}


void eeprom_write(uint16 address , uint8 data){

	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;

	/* Start eeprom write by setting EEWE */
	SET_BIT(EECR,2);
	SET_BIT(EECR,1);
	/* Write logical one to EEMWE */
	//EECR |= (1<<EEMWE);

}


uint8 eeprom_read(uint16 address){
	//wait for the completion of the previous write operation
	while(EECR & (1<<1));

	//set up address register
	EEAR = address ;

	//start read operation by setting EERE bit in Control Register
	EECR |= (1<<0);

	//now return data from data register
	return EEDR ;

}

