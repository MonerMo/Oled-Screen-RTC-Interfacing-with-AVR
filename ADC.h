/*
 * ADC.h
 *
 *  Created on: Aug 24, 2023
 *      Author: orabi
 */

#ifndef ADC_H_
#define ADC_H_
#include "ADC_Config.h"
#include "Bit_Operation.h"
#include "Atmega32_Registers.h"



//ADC Pin Number
#define ADC_0 0
#define ADC_1 1
#define ADC_2 2
#define ADC_3 3
#define ADC_4 4
#define ADC_5 5
#define ADC_6 6
#define ADC_7 7

//ADC Reference Voltages
#define AREF_PIN 	0
#define AVCC_PIN 	1
#define V_REF_2_56V	2

//ADC Prescaler
#define DIVIDE_BY_2   0
#define DIVIDE_BY_4   1
#define DIVIDE_BY_8   2
#define DIVIDE_BY_16  3
#define DIVIDE_BY_32  4
#define DIVIDE_BY_64  5
#define DIVIDE_BY_128 6

//ADC Conversion Type
#define MANUAL_TRIGGER 				0
#define AUTO_TRIGGER   				1
#define EXTERNAL_INTERRUPT_TRIGGER  2


//ADC Adjust
#define ADC_RIGHT_ADJUST 0
#define ADC_LEFT_ADJUST  1



//ADC Functions
//ADC_Init(); -Initialize ADC enviroment & Enable ADC
//Doesn't Return anything and just takes the specified ADC pin input
void ADC_Init(uint8 ADC_NUM);

//ADC_Read();
//Start Conversion and returns the converted analog value
uint16 ADC_Read(void);

#endif /* ADC_H_ */
