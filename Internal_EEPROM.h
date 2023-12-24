/*
 * Internal_EEPROM.h
 *
 *  Created on: Dec 4, 2023
 *      Author: orabi
 */

#ifndef INTERNAL_EEPROM_H_
#define INTERNAL_EEPROM_H_

#include "STD.h"
#include "Atmega32_Registers.h"
#include "Bit_Operation.h"
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <util/delay.h>

void eeprom_write(uint16 address , uint8 data);
uint8 eeprom_read(uint16 address);
void eeprom_address(uint16 address);

#endif /* INTERNAL_EEPROM_H_ */
