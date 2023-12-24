/*
 * ADC.c
 *
 *  Created on: Aug 24, 2023
 *      Author: orabi
 */


#include "ADC.h"

void ADC_Init(uint8 ADC_NUM){

	switch(ADC_NUM){
		case ADC_0:
		CLR_BIT(ADMUX,0);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,2);
		break;

		case ADC_1:
		SET_BIT(ADMUX,0);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,2);
		break;

		case ADC_2:
		CLR_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,2);
		break;

		case ADC_3:
		SET_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,2);
		break;

		case ADC_4:
		CLR_BIT(ADMUX,0);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,2);
		break;

		case ADC_5:
		SET_BIT(ADMUX,0);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,2);
		break;

		case ADC_6:
		CLR_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,2);
		break;

		case ADC_7:
		SET_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,2);
		break;
	}

	switch(ADC_REF_VOLTAGE){
	case AREF_PIN:
		CLR_BIT(ADMUX,6);
		CLR_BIT(ADMUX,7);
		break;
	case AVCC_PIN:
		SET_BIT(ADMUX,6);
		CLR_BIT(ADMUX,7);
		break;
	case V_REF_2_56V :
		SET_BIT(ADMUX,6);
		SET_BIT(ADMUX,7);
		break;
	}

	switch(ADC_PRESCALAR){

	case DIVIDE_BY_2 :
			SET_BIT(ADCSRA,0);
			CLR_BIT(ADCSRA,1);
			CLR_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_4 :
			CLR_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			CLR_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_8 :
			SET_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			CLR_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_16 :
			CLR_BIT(ADCSRA,0);
			CLR_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_32 :
			SET_BIT(ADCSRA,0);
			CLR_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_64 :
			CLR_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;

	case DIVIDE_BY_128 :
			SET_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;

			default:
			break;
	}

	switch(ADC_TRIGGER_MODE){
	case MANUAL_TRIGGER:
		//In this mode you need to enable conversion each time
		break;

	case AUTO_TRIGGER:
		//you enable it once
		SET_BIT(ADCSRA,5);
		break;

	case EXTERNAL_INTERRUPT_TRIGGER:
		CLR_BIT(SFIOR,5);
		SET_BIT(SFIOR,6);
		CLR_BIT(SFIOR,7);
		break;
	}


	switch(ADC_ADJUST_MODE){
	case ADC_RIGHT_ADJUST:
		CLR_BIT(ADMUX,5);
		break;
	case ADC_LEFT_ADJUST:
		SET_BIT(ADMUX,5);
		break;
	}

	//Enable ADC
	SET_BIT(ADCSRA,7);

}








uint16 ADC_Read(void){
//first start conversion and wait until ADC finishes conversion
	//1.Start conversion
	SET_BIT(ADCSRA, 6);
	//2.wait until Data Registers are updated
	while( GET_BIT(ADCSRA,4) == 0);


	uint16 value = ADC_D_VAL ;


	return value ;

}
