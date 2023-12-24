/*
 * SPI.h
 *
 *  Created on: Aug 31, 2023
 *      Author: orabi
 */

#ifndef SPI_H_
#define SPI_H_

#include "Bit_Operation.h"
#include "Atmega32_Registers.h"
#include "DIO.h"


void  SPI_Master_Init(void);
void  SPI_Slave_Init(void);
void  SPI_Transmit_Start(void);
void  SPI_Transmit_Term(void);
uint8 SPI_Data_Transmit(uint8 data);


#endif /* SPI_H_ */
