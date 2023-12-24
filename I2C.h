/*
 * I2C.h
 *
 *  Created on: Sep 5, 2023
 *      Author: orabi
 */

#ifndef I2C_H_
#define I2C_H_

#include "Atmega32_Registers.h"
#include "Bit_Operation.h"
#include "STD.h"

//This functions are dedicated to interface EEPROM
void I2C_Init(void);
uint8 I2C_Start(uint8 Slave_Address_W);
uint8 I2C_Repeated_Start(uint8 Slave_Address_R);
uint8 I2C_Write(uint16 Data);
uint8 I2C_Read_ACK(void);
uint8 I2C_Read_NACK(void);
void  I2C_Stop(void);



#endif /* I2C_H_ */
