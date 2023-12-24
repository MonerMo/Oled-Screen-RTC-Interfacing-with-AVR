/*
 * Application_Header.h
 *
 *  Created on: Dec 6, 2023
 *      Author: orabi
 */

#ifndef APPLICATION_HEADER_H_
#define APPLICATION_HEADER_H_




/************************INCLUDES******************/
#include "STD.h"


//I2C
#include "I2C.h"
#define Slave_Address_W 0b10101000
#define Slave_Address_R 0b10101001

//oled
#include "ssd1306.h"

//For DIO & Buttons.
#include "DIO.h"

//For RTC
#include "ds3231.h"

//For eeprom
#include <avr/eeprom.h>

//For delay
#include "Timer0.h"
#define F_CPU 8000000
#include <avr/delay.h>


/************************************************/


//Checking for first time booting the system
/*
 	 This function should follow the following sequence
 	 1.Check for a specific bit 0x01F8 (if zero---->0 : login in times , if one----> already logged in)
 	 2.In this function we care about the first time booting
 	 3.now we need to take the name of the user and store it
 	 4.print "enter name" on the top of the frame
 	 5.print a bar under the first letter
 	 6.print letter a
 	 7.wait for UP , DOWN or OK buttons to be pressed.
 */


//Interfaces Functions
//Clear a block
//Write a block of letter
//Write a block of numbers

void number_write(uint8 page_num , uint8 col_num , uint8 number_index);
void letter_write(uint8 page_num , uint8 col_num , uint8 letter_index);
void black_entire_screen(void);
uint8 boot_check(void);
void system_reset(void);
void system_set(void);
uint8 name_menu(void);

void button_init(void);
uint8 button_check(void);

uint8 time_menu(void);
void double_digit_write(uint8 page_num , uint8 col_num , uint8 number);
void triple_digit_write(uint8 page_num , uint8 col_num , uint16 number);
uint8 is_it_leap_year(uint16 year);
void day_name_print(uint8 day_name_track , uint8 ptr[][3]);
uint8 dec_to_bcd(uint8 dec);

//now for the main menu function.
uint8 main_menu(void);
void printing_menu_with_choice(void);
void color_choice_black(uint8 number_of_choice);
void color_choice_white(uint8 number_of_choice);

//study_timer function
uint8 study_timer(void);

//live_clock function
uint8 live_clock(void);
uint8 bcd_to_dec(uint8 bcd);

//lamp switch functions
void lamp_on_off(void);

#endif /* APPLICATION_HEADER_H_ */
