/*
 * Atmega32_Registers.h
 *
 *  Created on: Aug 20, 2023
 *      Author: orabi
 */

#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_

#include "STD.h"

//***************************************************
//DIO Registers
#define PORTA (*(volatile uint8*)(0x3B))
#define DDRA  (*(volatile uint8*)(0x3A))
#define PINA  (*(volatile uint8*)(0x39))

#define PORTB (*(volatile uint8*)(0x38))
#define DDRB  (*(volatile uint8*)(0x37))
#define PINB  (*(volatile uint8*)(0x36))

#define PORTC (*(volatile uint8*)(0x35))
#define DDRC  (*(volatile uint8*)(0x34))
#define PINC  (*(volatile uint8*)(0x33))

#define PORTD (*(volatile uint8*)(0x32))
#define DDRD  (*(volatile uint8*)(0x31))
#define PIND  (*(volatile uint8*)(0x30))

//***************************************************
//External Interrupts Registers

//Status Register - Responsible for global interrupt enable
//Bit no.7 enable global interrupt (Bit no.7 initially equal 0)
#define SREG  	(*(volatile uint8*)(0x5F))

//General Interrupt Control Register - Responsible for enabling external interrupt request
//(INT1 , INT0 , INT2) -- (bit no. 7,6,5)
#define GICR  	(*(volatile uint8*)(0x5B))

//MCU Control Register - Responsible for trigger type
//For interrupt0  ( 1 , 0 )
//For interrupt1  ( 3 , 2 )
#define MCUCR 	(*(volatile uint8*)(0x55))

//MCU Control and Status Register - Responsible for trigger type
//For interrupt2
#define MCUCSR 	(*(volatile uint8*)(0x54))


//General Interrupt Flag Register
//(INT1 ,INT0 , INT2) -- (bit no. 7,6,5)
#define GIFR 	(*(volatile uint8*)(0x5A))
//***************************************************
//ADC Registers

#define ADMUX 		(*(volatile uint8*)(0x27))
#define ADCSRA 		(*(volatile uint8*)(0x26))
#define SFIOR       (*(volatile uint8*)(0x50))
#define ADC_D_VAL 	(*(volatile uint16*)(0x24))

//***************************************************
//Timer0 Registers

#define TCCR0 		(*(volatile uint8*)(0x53))
#define TIMSK 		(*(volatile uint8*)(0x59))
#define TCNT0 		(*(volatile uint8*)(0x52))
#define OCR0 		(*(volatile uint8*)(0x5C))
#define TIFR        (*(volatile uint8*)(0x58))

//***************************************************
//Timer1 Registers
#define TCCR1A 		(*(volatile uint8*)(0x4F))
#define TCCR1B 		(*(volatile uint8*)(0x4E))

#define OCR1A 		(*(volatile uint16*)(0x4A))

#define ICR1L 		(*(volatile uint8*)(0x46))
#define ICR1H		(*(volatile uint8*)(0x47))

#define ICR1 		(*(volatile uint16*)(0x46))

#define ACSR 		(*(volatile uint8*)(0x28))

//**************************************************
//WatchDog Register
#define WDTCR  		(*(volatile uint8*)(0x41))

//****************************************************
//UART

#define UBRRH   (*(volatile uint8*)(0x40))
#define UBRRL   (*(volatile uint8*)(0x29)) //baudrate register
#define UCSRA   (*(volatile uint8*)(0x2B))
#define UCSRB   (*(volatile uint8*)(0x2A)) //enable transmitter and receiver
#define UCSRC   (*(volatile uint8*)(0x40))
#define UDR     (*(volatile uint8*)(0x2C))


//****************************************************
//SPI

//SPCR - Used for controlling
//LSB or MSB Transfer bit
//CLK Polarity , CLK Phase , Master CLK Generate , Master Enable
#define SPCR       (*(volatile uint8*)(0x2D))

//SPSR - Used for checking transmission complete flag
#define SPSR       (*(volatile uint8*)(0x2E))

//SPDR - SPI Data Register
#define SPDR       (*(volatile uint8*)(0x2F))

//***********************************************************
//I2C
#define TWCR (*(volatile uint8*)(0x56)) //Two wire interface Control register
#define TWDR (*(volatile uint8*)(0x23)) //Two wire interface Data register
#define TWAR (*(volatile uint8*)(0x22)) //Two wire interface Slave Address register
#define TWSR (*(volatile uint8*)(0x21)) //Two wire interface Status register
#define TWBR (*(volatile uint8*)(0x20)) //Two wire interface Bit rate register
//*************************************************************
//Internal EEPROM
#define EEARL (*(volatile uint8*)(0x3E))  //Lowest Nibble of the Address Regsiter
#define EEARH (*(volatile uint8*)(0x3F))  //Highest Nibble of the Address Register
#define EEAR  (*(volatile uint16*)(0x3E)) //Address Register
#define EEDR  (*(volatile uint8*)(0x3D))  //Data Register
#define EECR  (*(volatile uint8*)(0x3C))  //Control Register
#define SPCMR (*(volatile uint8*)(0x57))
//*************************************************************


#endif /* ATMEGA32_REGISTERS_H_ */
