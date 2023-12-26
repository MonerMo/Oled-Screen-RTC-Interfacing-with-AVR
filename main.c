/*
 * main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: orabi
 */

#include "Atmega32_Registers.h"
#define F_CPU 8000000
#include <avr/delay.h>
#include "DIO.h"
#include "I2C.h"
#include "ssd1306.h"
#include "Application_Header.h"
#include "Timer0.h"


int main(){
	I2C_Init();
	Initialize();
	button_init();
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN7,DIO_PIN_DIR_OUTPUT);




	uint8 setup_done_correctly = 0;
	if(boot_check() == 0xFF){
		//first time booting up
		name_menu();
		setup_done_correctly = time_menu();
	}else if(boot_check() == 0x01){
		while(1){
		main_menu();
		}
	}

	if(setup_done_correctly){
		system_set();
		while(1){
			main_menu();
		}
	}else{
		//not done correctly
	}




	while(1){



	}

}


