/*
 * Application_Header.c
 *
 *  Created on: Dec 6, 2023
 *      Author: orabi
 */



#include "Application_Header.h"



//array of days letters SAT,SUN,MON,TUE,WED,THU,FRI
uint8 days[7][3] = {
	{18,0,19},//SAT ----> 1
	{18,20,13},//SUN ----> 2
	{12,14,13},//MON ----> 3
	{19,20,4},//TUE ----> 4
	{22,4,3},//WED ----> 5
	{19,7,20},//THU ----> 6
	{5,17,8}//FRI ----> 7
};

//array to hold the input from the user in name_menu function .
//also used in main_menu function to read the name coming from the external eeprom.
uint8 username[5] = {0} ;

//array for ":" & "-" used in *live_clock* function & used in *time_menu* function
//bitmap array for :
uint8 double_dot_bitmap[14] = {0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00};
//bitmap array for -
uint8 dash_bitmap[14] = {0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


/********************************************************************************/
void number_write(uint8 page_num , uint8 col_num , uint8 number_index){
	I2C_Init();
	/*storing bytes array*/
	uint8 bitmap_holder[14] = {0};


	//first we want to send that we want to write and write the start reading address.
	I2C_Start(Slave_Address_W);

	/*calculate the starting reading address depend on the number_index)*/
	uint8 address = ( number_index * 14 );
	I2C_Write(address);

	/*now initiate the communication again but this time in read mode*/
	I2C_Repeated_Start(Slave_Address_R);

	/*now reading from the eeprom and storing in "bitmap_holder" array*/
	for(uint8 byte_address = 0 ; byte_address < 13 ; byte_address++){
		bitmap_holder[byte_address] = I2C_Read_ACK();
	}
	bitmap_holder[13] = I2C_Read_NACK();
	I2C_Stop();

	/*now after getting the data from the eeprom we want to send it to the oled screen*/
	setColumnAddress(col_num,col_num+7);
	setPageAddress(page_num,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);

	for(uint8 byte_address = 0 ; byte_address < 7 ; byte_address++){
		I2C_Write(bitmap_holder[byte_address]);
	}

	I2C_Stop();
	setColumnAddress(col_num,col_num+7);
	setPageAddress(page_num-1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);

	for(uint8 byte_address = 7 ; byte_address < 14 ; byte_address++){
		I2C_Write(bitmap_holder[byte_address]);
	}

	I2C_Stop();

}

/********************************************************************************/
void letter_write(uint8 page_num , uint8 col_num , uint8 letter_index){
	I2C_Init();
	/*storing bytes array*/
	uint8 bitmap_holder[14] = {0};


	//first we want to send that we want to write and write the start reading address.
	//but take care that the first 8 letters(index ----> 0 to 7) are stored in BLOCK 1 in eeprom.
	//and the latter 18 letters (index ----> 8 to 17) are stored in BLOCK 2 in eeprom.
	if(letter_index >= 0 && letter_index <= 7){

		I2C_Start(Slave_Address_W);
		/*calculate the starting reading address depend on the number_index)*/
		uint8 address = ( ( letter_index * 14 ) + 140 );
		I2C_Write(address);
		/*now initiate the communication again but this time in read mode*/
		I2C_Repeated_Start(Slave_Address_R);

		/*now reading from the eeprom and storing in "bitmap_holder" array*/
		for(uint8 byte_address = 0 ; byte_address < 13 ; byte_address++){
			bitmap_holder[byte_address] = I2C_Read_ACK();
		}
		bitmap_holder[13] = I2C_Read_NACK();
		I2C_Stop();

	}else if(letter_index == 8){

		I2C_Start(Slave_Address_W);
		/*calculate the starting reading address depend on the number_index)*/
		uint8 address = ( ( letter_index * 14 ) + 140 );
		I2C_Write(address);
		/*now initiate the communication again but this time in read mode*/
		I2C_Repeated_Start(Slave_Address_R);

		for(uint8 byte_address = 0 ; byte_address < 3 ; byte_address++){
			bitmap_holder[byte_address] = I2C_Read_ACK();
		}
		bitmap_holder[3] = I2C_Read_NACK();
		I2C_Stop();

		I2C_Start(0b10101010);
		I2C_Write(0x00);
		I2C_Repeated_Start(0b10101011);
		for(uint8 byte_address = 4 ; byte_address < 13 ; byte_address++){
			bitmap_holder[byte_address] = I2C_Read_ACK();
		}
		bitmap_holder[13] = I2C_Read_NACK();
		I2C_Stop();

	}else if(letter_index > 8 && letter_index <= 25){

		I2C_Start(0b10101010);//to start reading from block 0
		/*calculate the starting reading address depend on the number_index)*/
		uint8 address = (( (letter_index-9) * 14 ) + 10);
		I2C_Write(address);
		/*now initiate the communication again but this time in read mode*/
		I2C_Repeated_Start(0b10101011);

		/*now reading from the eeprom and storing in "bitmap_holder" array*/
		for(uint8 byte_address = 0 ; byte_address < 13 ; byte_address++){
			bitmap_holder[byte_address] = I2C_Read_ACK();
		}
		bitmap_holder[13] = I2C_Read_NACK();
		I2C_Stop();

	}

	/*now after getting the data from the eeprom we want to send it to the oled screen*/
	setColumnAddress(col_num,col_num+7);
	setPageAddress(page_num,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);

	for(uint8 byte_address = 0 ; byte_address < 7 ; byte_address++){
		I2C_Write(bitmap_holder[byte_address]);
	}

	I2C_Stop();
	setColumnAddress(col_num,col_num+7);
	setPageAddress(page_num-1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);

	for(uint8 byte_address = 7 ; byte_address < 14 ; byte_address++){
		I2C_Write(bitmap_holder[byte_address]);
	}

	I2C_Stop();
}
/*******************************************************************/
uint8 boot_check(void){
	/*Initiate the communication to eeprom*/
	I2C_Init();
	I2C_Start(0b10101010);
	/*For the address of the boot check byte = 0x1F8*/
	I2C_Write(0xF8);
	/*now we want to re-initiate the communication again to read mode*/
	I2C_Repeated_Start(0b10101011);
	/*read the boot_byte mode if 0xFF---->first time booting if 0x01---->already booted up before.*/
	uint8 boot_byte = I2C_Read_NACK();
	I2C_Stop();
	return boot_byte ;
}

/****************************************************************************/
void system_reset(void){
	I2C_Init();
	I2C_Start(0b10101010);
	//For the address of the boot check byte = 0x1F8
	I2C_Write(0xF8);
	I2C_Write(0xFF);
	I2C_Stop();
}
/****************************************************************************/
void system_set(void){
	I2C_Init();
	I2C_Start(0b10101010);
	//For the address of the boot check byte = 0x1F8
	I2C_Write(0xF8);
	I2C_Write(0x01);
	I2C_Stop();
}
/****************************************************************************/
void button_init(void){
	//For Pin2 PortC
	DIO_SetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_DIR_INPUT);
	DIO_SetPullUpRes(DIO_PORTC, DIO_PIN2);


	//For the 3 buttons
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN3, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN4, DIO_PIN_DIR_OUTPUT);
	DIO_SetPinDirection(DIO_PORTC, DIO_PIN5, DIO_PIN_DIR_OUTPUT);

	//Set the values to HIGH
	DIO_SetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_VAL_HIGH);
	DIO_SetPinValue(DIO_PORTC,DIO_PIN5,DIO_PIN_VAL_HIGH);
}

/****************************************************************************/
uint8 button_check(void){

	uint8 which_button = 0 ;

	//now we want to loop over the pins 3,4,5 and set each one to low and check if pin2 get LOW value.
	for(uint8 COL_PIN = 3 ; COL_PIN <= 5 ; COL_PIN++){
		uint8 button_pressed = 1 ;

		DIO_SetPinValue(DIO_PORTC,COL_PIN,DIO_PIN_VAL_LOW);
		DIO_GetPinValue(DIO_PORTC,DIO_PIN2, &button_pressed);

		//0 means button is pressed
		if(button_pressed == 0){
			which_button = COL_PIN ;

			while(button_pressed == 0){
				DIO_GetPinValue(DIO_PORTC, DIO_PIN2, &button_pressed);
			}
		}

		DIO_SetPinValue(DIO_PORTC,COL_PIN,DIO_PIN_VAL_HIGH);
		if(which_button != 0)
			return which_button ;
	}
	return which_button ;
}
/*****************************************************************************/
uint8 name_menu(void){

	//First we will print "enter your name" on the top of the screen.
	/*enter_name_arr is an array that hold the indexes of the letters in "enter your name" sentence.*/

	black_entire_screen();

	uint8 enter_name_arr[13] = {4,13,19,4,17,24,14,20,17,13,0,12,4};
	/*now we will print them on the screen*/
	uint8 starting_col = 0 ;
	for(uint8 letter_index = 0 ; letter_index < 13 ; letter_index++){


		if(letter_index == 5 || letter_index == 9){
			starting_col += 14;
		}else{
			starting_col += 7;
		}

		letter_write(7,starting_col,enter_name_arr[letter_index]);

	}

	/*now after printing "enter your name" sentence.
	 * we want to print the first letter on the beginning of PAGE 3 on OLED
	 * and dash underline it do it for 5 iterations
	 */


	//also we want an array of 5 bytes to store the name of the user.
	//uint8 username[5] = {0} ;

	for(uint8 letter_in = 0 ; letter_in < 5 ; letter_in++){
		//we want to have a variable to keep track of what letter to show on screen.
		uint8 letter_count = 0 ;

		//now we print letter 'a' and underline it.
		letter_write(3,(letter_in * 7),0);

		//for the underline
		setColumnAddress((letter_in * 7),8);
		setPageAddress(1,7);
		I2C_Start(oled_write_address);
		I2C_Write(CONTROL_DATA);
		for(uint8 i = 0 ; i < 7 ; i++){
			I2C_Write(0x03);
		}
		I2C_Stop();


		//now we want to enter a do while loop in order to check for the buttons.
		//design a function that returns with the value of the button pressed.
		uint8 which_button = 0 ;
		do{
			which_button = 0 ;
			which_button = button_check();

			if(which_button == 3){
				//this means that we pressed left
				//check if we stopping at letter a
				if(letter_count == 0){
					letter_count = 25 ;
					letter_write(3,(letter_in * 7),letter_count);
				}else{
					letter_count-- ;
					letter_write(3,(letter_in * 7),letter_count);
				}

			}else if(which_button == 4){
				//this means that we pressed right
				//check if we stopping at letter z
				if(letter_count == 25){
					letter_count = 0 ;
					letter_write(3,(letter_in * 7),letter_count);
				}else{
					letter_count++ ;
					letter_write(3,(letter_in * 7),letter_count);
				}
			}


		}while(which_button != 5);

		//now we need to store the letter the user have chosen.
		username[letter_in] = letter_count ;

		//now we need to clear the underline
		setColumnAddress((letter_in * 7),8);
		setPageAddress(1,7);
		I2C_Start(oled_write_address);
		I2C_Write(CONTROL_DATA);
		for(uint8 i = 0 ; i < 7 ; i++){
			I2C_Write(0x00);
		}
		I2C_Stop();

	}
	//now save the name inside eeprom starting from 0x1F9
	I2C_Start(0b10101010);
	//For the address of the boot check byte = 0x1F8
	I2C_Write(0xF9);
	for(uint8 i = 0 ; i < 5 ; i++){
		I2C_Write(username[i]);
	}
	I2C_Stop();

	return 1 ; //adding name to eeprom done successfully.
}
/**********************************************************************/
void double_digit_write(uint8 page_num , uint8 col_num , uint8 number){
	uint8 digit = number % 10 ;
	number_write(page_num,col_num+7,digit);
	number /= 10 ;
	number_write(page_num,col_num,number);
}
/*********************************************************************/
void triple_digit_write(uint8 page_num , uint8 col_num , uint16 number){
	uint8 digit = number % 10 ;
	number_write(page_num,(col_num+14),digit);
	number /= 10 ;
	digit = number % 10 ;
	number_write(page_num,col_num+7,digit);
	number /= 10 ;
	digit = number % 10 ;
	number_write(page_num,col_num,digit);
}
/*********************************************************************/
uint8 is_it_leap_year(uint16 year){
	uint8 holder = year % 10 ;
	year /= 10 ;
	holder = ((year % 10) * 10 ) + holder ;
	if(holder % 4 == 0){
		return 1 ; //it is leap year.
	}else{
		return 0 ; //it is not a leap year.
	}
}
/*********************************************************************/
void day_name_print(uint8 day_name_track , uint8 ptr[][3]){
	for(uint8 letter_index = 0 ; letter_index < 3 ; letter_index++){
		letter_write(2,((letter_index*7)+97),ptr[day_name_track][letter_index]) ;
	}
}
/*********************************************************************/
uint8 dec_to_bcd(uint8 dec){
	uint8 digit = dec % 10 ;
	dec /= 10 ;
	digit = ( dec << 4 ) | digit ;
	return digit ;
}
/*********************************************************************/

void printing_menu_with_choice(void){


	for(sint8 i = 7; i >= 0 ; i--){
			setColumnAddress(0,127);
			setPageAddress(i,7);
			I2C_Init();
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);

			//start byte to write
			uint32 start_byte_index = (7-i) * 128 ;
			//end byte to write
			uint32 end_byte_index = start_byte_index + 127 ;
			if(i == 5 || i == 4){
				for(;start_byte_index < end_byte_index ; start_byte_index++){
					I2C_Write(~(eeprom_read_byte(start_byte_index)));
				}
			}else{
				for(;start_byte_index < end_byte_index ; start_byte_index++){
					I2C_Write(eeprom_read_byte(start_byte_index));
				}
			}
			I2C_Stop();
	}


	I2C_Start(0b10101010); //Starting communication with the external eeprom.
	I2C_Write(0xF9); //Writing the starting address to read from the eeprom.
	I2C_Repeated_Start(0b10101011);//Rs & telling the eeprom that we will read from it.
	for(uint8 i = 0 ; i < 4 ; i++){
		username[i] = I2C_Read_ACK();
	}
	username[4] = I2C_Read_NACK();
	I2C_Stop();

	//now print the name on the OLED
	for(uint8 i = 0 ; i < 5 ; i++){
		letter_write(7,(56+(7*i)),username[i]);
	}



}
/*********************************************************************/
void black_entire_screen(void){
	//WE WANT TO BLACK OUT THE ENTIRE SCREEN

	for(int i = 0 ; i <= 7 ; i++){
		setColumnAddress(0,128);
		setPageAddress(i,7);
		I2C_Start(oled_write_address);
		I2C_Write(CONTROL_DATA);
		for(int i = 0 ; i < 128 ; i++){
			I2C_Write(0x00);
		}
		I2C_Stop();
	}
}
/*********************************************************************/
uint8 choice_page_index[4] = {0 , 5 , 3 , 1};
void color_choice_black(uint8 number_of_choice){
	//color either 0----> black , 1---->white
	//we have 3 choices , 1---->study timer , 2---->clock , 3---->lamp on/off

	sint8 starting_page = choice_page_index[number_of_choice];
	uint8 ending_page = starting_page-1;



	for(; starting_page >= ending_page ;starting_page--){
		setColumnAddress(0,127);
		setPageAddress(starting_page,7);
		I2C_Init();
		I2C_Start(oled_write_address);
		I2C_Write(CONTROL_DATA);

		//start byte to write
		uint32 start_byte_index = (7-starting_page) * 128 ;
		//end byte to write
		uint32 end_byte_index = start_byte_index + 127 ;


		//this means black the choice
		for(;start_byte_index < end_byte_index ; start_byte_index++){
			I2C_Write(eeprom_read_byte(start_byte_index));
		}
		I2C_Stop();
	}
}
/*********************************************************************/
void color_choice_white(uint8 number_of_choice){
	//color either 0----> black , 1---->white
	//we have 3 choices , 1---->study timer , 2---->clock , 3---->lamp on/off

	sint8 starting_page = choice_page_index[number_of_choice];
	uint8 ending_page = starting_page-1;



	for(; starting_page >= ending_page ;starting_page--){
		setColumnAddress(0,127);
		setPageAddress(starting_page,7);
		I2C_Init();
		I2C_Start(oled_write_address);
		I2C_Write(CONTROL_DATA);

		//start byte to write
		uint32 start_byte_index = (7-starting_page) * 128 ;
		//end byte to write
		uint32 end_byte_index = start_byte_index + 127 ;


		//this means black the choice
		for(;start_byte_index < end_byte_index ; start_byte_index++){
			I2C_Write(~(eeprom_read_byte(start_byte_index)));
		}
		I2C_Stop();
	}
}
/*******************************************************************/
uint8 time_menu(void){

	//WE WANT TO BLACK OUT THE ENTIRE SCREEN

	black_entire_screen();

	//"adjust time" prompt letters array.
	uint8 adjust_time_arr[10] = {0,3,9,20,18,19,19,8,12,4};

	uint8 starting_col = 20 ;
	for(uint8 letter_index = 0 ; letter_index < 10 ; letter_index++){


		if(letter_index == 6){
			starting_col += 14;
		}else{
			starting_col += 7;
		}

		letter_write(7,starting_col,adjust_time_arr[letter_index]);

	}

	/************************************************************/
	//Printing time 00:00 AM

	//Printing 00
	number_write(5,41,0);
	number_write(5,48,1);

	//Printing :
	setColumnAddress(55,128);
	setPageAddress(5,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(double_dot_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(55,128);
	setPageAddress(4,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(double_dot_bitmap[i]);
	}
	I2C_Stop();

	//Printing 00
	number_write(5,62,0);
	number_write(5,69,0);

	//Printing AM
	letter_write(5,76,0);
	letter_write(5,83,12);

	/************************************************************/
	//Printing 28-12-2023 SUN

	//Printing 28
	number_write(2,20,2);
	number_write(2,27,8);

	uint8 dash_bitmap[14] = {0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	//Printing -
	setColumnAddress(34,128);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(34,128);
	setPageAddress(1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	//Printing 12
	number_write(2,41,1);
	number_write(2,48,2);

	//Printing -
	setColumnAddress(55,128);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(55,128);
	setPageAddress(1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	//Printing 2023
	number_write(2,62,2);
	number_write(2,69,0);
	number_write(2,76,2);
	number_write(2,83,3);

	//Printing THU ----> 6
	letter_write(2,97,19);
	letter_write(2,104,7);
	letter_write(2,111,20);

	/*******************************Taking Inputs Master Loop***************************/
	//For storing runtime input
	CLOCK_DATA clock_input ;
	DATE_DATA date_input ;


	for(uint8 num_of_inputs = 0 ; num_of_inputs < 7 ; num_of_inputs++){
		if(num_of_inputs == 0){/********************************************************/
			//this means that we are taking hours as an input.

			//for the underline
			setColumnAddress(41,55);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();

			uint8 hours_tracker = 1 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//this means that we pressed left
					//check if we stopping at letter a
					if(hours_tracker == 1){
						hours_tracker = 12 ;
						double_digit_write(5,41,hours_tracker);
					}else{
						hours_tracker-- ;
						double_digit_write(5,41,hours_tracker);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if(hours_tracker == 12){
						hours_tracker = 1 ;
						double_digit_write(5,41,hours_tracker);
					}else{
						hours_tracker++ ;
						double_digit_write(5,41,hours_tracker);
					}
				}

			}while(which_button != 5);
			//Storing hours in our struct for later rtc modification.
			clock_input.hours = dec_to_bcd(hours_tracker);

			//for clearing underline
			setColumnAddress(41,55);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();

		}else if(num_of_inputs == 1){/********************************************************/
			//we are adjusting minutes.

			//for the underline
			setColumnAddress(62,76);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();

			uint8 minutes_tracker = 0 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//this means that we pressed left
					//check if we stopping at letter a
					if(minutes_tracker == 0){
						minutes_tracker = 59 ;
						double_digit_write(5,62,minutes_tracker);
					}else{
						minutes_tracker-- ;
						double_digit_write(5,62,minutes_tracker);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if(minutes_tracker == 59){
						minutes_tracker = 0 ;
						double_digit_write(5,62,minutes_tracker);
					}else{
						minutes_tracker++ ;
						double_digit_write(5,62,minutes_tracker);
					}
				}

			}while(which_button != 5);
			//Storing hours in our struct for later rtc modification.
			clock_input.minutes = dec_to_bcd(minutes_tracker);

			//for clearing underline
			setColumnAddress(62,76);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();


		}else if(num_of_inputs == 2){/********************************************************/
			//now we are choosing am or pm

			//for the underline
			setColumnAddress(76,90);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();


			//if am_pm_tracker == 0 ----> AM , if am_pm_tracker == 1 ----> PM
			uint8 am_pm_tracker = 0 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3 || which_button == 4){
					//this means that we pressed left
					if(am_pm_tracker == 0){
						am_pm_tracker = 1;
						letter_write(5,76,15);
					}else if(am_pm_tracker == 1){
						am_pm_tracker = 0 ;
						letter_write(5,76,0);
					}
				}

			}while(which_button != 5);


			clock_input.am_pm = am_pm_tracker  ;


			//for clearing underline
			setColumnAddress(76,90);
			setPageAddress(3,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();


		}else if(num_of_inputs == 3){/********************************************************/
			//now we are adjusting the year

			//for the underline
			setColumnAddress(62,90);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 28 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();


			uint16 year_tracker = 2023 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//this means that we pressed left
					//check if we stopping at letter a
					if(year_tracker == 2023){
						year_tracker = 2100 ;
						triple_digit_write(2,69,year_tracker);
					}else{
						year_tracker-- ;
						triple_digit_write(2,69,year_tracker);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if(year_tracker == 2100){
						year_tracker = 2023 ;
						triple_digit_write(2,69,year_tracker);
					}else{
						year_tracker++ ;
						triple_digit_write(2,69,year_tracker);
					}
				}

			}while(which_button != 5);
			uint8 last_two_digit = year_tracker % 10 ;
			year_tracker /= 10 ;
			last_two_digit = ((year_tracker % 10) * 10 ) + last_two_digit ;
			date_input.year = dec_to_bcd(last_two_digit) ;

			//for clearing/deleting the underline
			setColumnAddress(62,90);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 28 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();

		}else if(num_of_inputs == 4){/********************************************************/
			//this means that we are choosing the current month.

			//for the underline
			setColumnAddress(41,55);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();

			uint8 month_tracker = 12 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//this means that we pressed left
					//check if we stopping at letter a
					if(month_tracker == 1){
						month_tracker = 12 ;
						double_digit_write(2,41,month_tracker);
					}else{
						month_tracker-- ;
						double_digit_write(2,41,month_tracker);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if(month_tracker == 12){
						month_tracker = 1 ;
						double_digit_write(2,41,month_tracker);
					}else{
						month_tracker++ ;
						double_digit_write(2,41,month_tracker);
					}
				}

			}while(which_button != 5);
			date_input.month = dec_to_bcd(month_tracker) ;

			//for clearing the underline
			setColumnAddress(41,55);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();


		}else if(num_of_inputs == 5){/********************************************************/

			//now we are choosing the day
			//for the underline
			setColumnAddress(20,34);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();

			uint8 day_tracker = 28 ;
			uint8 which_button = 0 ;


			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//we have a the following cases:
					//1.we are 1,3,5,7,8,10,12 ----> 31 day
					//2.we are 4,6,9,11 ---->30 days
					//3.February 28 days if it is not leap year , 29 days if it is leap year.{
					if(day_tracker == 1){
						if( (date_input.month == 2) && (is_it_leap_year(date_input.year)) ){
							day_tracker = 29 ;
							double_digit_write(2,20,day_tracker);
						}else if( (date_input.month == 2) && !(is_it_leap_year(date_input.year)) ){
							day_tracker = 28 ;
							double_digit_write(2,20,day_tracker);
						}else if(date_input.month == 4||date_input.month == 6||date_input.month == 9||date_input.month == 11){
							day_tracker = 30 ;
							double_digit_write(2,20,day_tracker);
						}else{
							day_tracker = 31 ;
							double_digit_write(2,20,day_tracker);
						}
					}else{
						day_tracker-- ;
						double_digit_write(2,20,day_tracker);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if( (date_input.month == 2) && (is_it_leap_year(date_input.year)) ){
						if(day_tracker != 29){
							day_tracker++;
						}else{
							day_tracker = 1 ;
						}
						double_digit_write(2,20,day_tracker);

					}else if( (date_input.month == 2) && !(is_it_leap_year(date_input.year)) ){
						if(day_tracker != 28){
							day_tracker++;
						}else{
							day_tracker = 1 ;
						}
						double_digit_write(2,20,day_tracker);

					}else if(date_input.month == 4||date_input.month == 6||date_input.month == 9||date_input.month == 11){
						if(day_tracker != 30){
							day_tracker++;
						}else{
							day_tracker = 1 ;
						}
						double_digit_write(2,20,day_tracker);

					}else{
						if(day_tracker != 31){
							day_tracker++;
						}else{
							day_tracker = 1 ;
						}
						double_digit_write(2,20,day_tracker);
					}
				}

			}while(which_button != 5);
			date_input.date = dec_to_bcd(day_tracker) ;

			//for the underline
			setColumnAddress(20,34);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 14 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();
		}else if(num_of_inputs == 6){/********************************************************/
			//now we are choosing the day name.

			//for the underline
			setColumnAddress(97,118);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 21 ; i++){
				I2C_Write(0xC0);
			}
			I2C_Stop();



			//we will make the day_name_tracker have the range from 1---->7 because rtc holds value
			//starting from 1 to 7 , but in index form we will send "day_name_tracker - 1".
			uint8 day_name_tracker = 6 ;
			uint8 which_button = 0 ;
			do{
				which_button = 0 ;
				which_button = button_check();

				if(which_button == 3){
					//this means that we pressed left
					//check if we stopping at letter a
					if(day_name_tracker == 1){
						day_name_tracker = 7 ;
						day_name_print(day_name_tracker - 1 , days);
					}else{
						day_name_tracker-- ;
						day_name_print(day_name_tracker - 1 , days);
					}

				}else if(which_button == 4){
					//this means that we pressed right
					//check if we stopping at letter z
					if(day_name_tracker == 7){
						day_name_tracker = 1 ;
						day_name_print(day_name_tracker - 1 , days);
					}else{
						day_name_tracker++ ;
						day_name_print(day_name_tracker - 1 , days);
					}
				}
			}while(which_button != 5);
			date_input.day = day_name_tracker ;

			//for clearing underline
			setColumnAddress(97,118);
			setPageAddress(0,7);
			I2C_Start(oled_write_address);
			I2C_Write(CONTROL_DATA);
			for(uint8 i = 0 ; i < 21 ; i++){
				I2C_Write(0x00);
			}
			I2C_Stop();
			//after taking all inputs now we will set the time\date and send data to the rtc.
			RTC_CLOCK_Write(clock_input.hours,clock_input.minutes,clock_input.seconds,clock_input.am_pm);
			RTC_DATE_Write(date_input.day,date_input.date,date_input.month,date_input.year);
		}

	}
	return 1 ;
}
/*********************************************************************/
uint8 bcd_to_dec(uint8 bcd){
	uint8 tens = (bcd >> 4) * 10 ;
	tens = tens + (bcd & 0b00001111) ;
	return tens ;
}
/*********************************************************************/
uint8 live_clock(void){

	black_entire_screen();

	//making struct object to hold the data coming from the RTC
	CLOCK_DATA CLOCK_HOLDER_NEW , CLOCK_HOLDER_OLD;
	DATE_DATA DATE_HOLDER_NEW , DATE_HOLDER_OLD;

	//for storing data for the first comparison
	CLOCK_HOLDER_OLD = CLOCK_HOLDER_NEW;
	RTC_CLOCK_Read(0x00,&CLOCK_HOLDER_NEW);
	RTC_DATE_Read(0x03,&DATE_HOLDER_NEW);

	//to mask the clock bits only and remove PM/AM and 24/12 hour format bits.
	CLOCK_HOLDER_NEW.hours &= 0b00011111 ;

	//Printing current time
	double_digit_write(5, 41, bcd_to_dec(CLOCK_HOLDER_NEW.hours));

	//Printing :
	setColumnAddress(55,128);
	setPageAddress(5,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(double_dot_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(55,128);
	setPageAddress(4,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(double_dot_bitmap[i]);
	}
	I2C_Stop();

	double_digit_write(5 ,62 ,bcd_to_dec(CLOCK_HOLDER_NEW.minutes));

	//writing pm or am
	if(CLOCK_HOLDER_NEW.am_pm){
		//this means that we are pm
		letter_write(5,76,15);
		letter_write(5,83,12);
	}else if(CLOCK_HOLDER_NEW.am_pm == 0){
		letter_write(5,76,0);
		letter_write(5,83,12);
	}

	//writing the day from date
	double_digit_write(2,20,bcd_to_dec(DATE_HOLDER_NEW.date));


	//Printing -
	setColumnAddress(34,128);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(34,128);
	setPageAddress(1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	//writing the month
	double_digit_write(2, 41, bcd_to_dec(DATE_HOLDER_NEW.month));

	//Printing -
	setColumnAddress(55,128);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 7 ;i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	setColumnAddress(55,128);
	setPageAddress(1,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 7 ; i < 14 ; i++){
		I2C_Write(dash_bitmap[i]);
	}
	I2C_Stop();

	//writing the thousand index 2 in 2023
	number_write(2,62,2);
	triple_digit_write(2, 69, bcd_to_dec(DATE_HOLDER_NEW.year));

	//printing the day
	day_name_print(DATE_HOLDER_NEW.day - 1 , days);





	uint8 which_button = 0 ;
	do{
		which_button = button_check();

		//now checking and reading time
		RTC_CLOCK_Read(0x00,&CLOCK_HOLDER_NEW);
		if(CLOCK_HOLDER_NEW.hours != CLOCK_HOLDER_OLD.hours){
			CLOCK_HOLDER_NEW.hours &= 0b00011111 ;
			CLOCK_HOLDER_OLD.hours = CLOCK_HOLDER_NEW.hours;
			double_digit_write(5, 41, bcd_to_dec(CLOCK_HOLDER_OLD.hours));
		}

		if(CLOCK_HOLDER_NEW.minutes != CLOCK_HOLDER_OLD.minutes){
			CLOCK_HOLDER_OLD.minutes = CLOCK_HOLDER_NEW.minutes ;
			double_digit_write(5, 62, bcd_to_dec(CLOCK_HOLDER_OLD.minutes));
		}

		if(CLOCK_HOLDER_NEW.am_pm != CLOCK_HOLDER_OLD.am_pm){
			CLOCK_HOLDER_OLD.am_pm = CLOCK_HOLDER_NEW.am_pm ;
			//writing pm or am
			if(CLOCK_HOLDER_OLD.am_pm){
				//this means that we are pm
				letter_write(5,76,15);
				letter_write(5,83,12);
			}else if(CLOCK_HOLDER_OLD.am_pm == 0){
				letter_write(5,76,0);
				letter_write(5,83,12);
			}
		}



		//now checking and reading date
		RTC_DATE_Read(0x03,&DATE_HOLDER_NEW);

		if(DATE_HOLDER_NEW.date != DATE_HOLDER_OLD.date){
			DATE_HOLDER_OLD.date = DATE_HOLDER_NEW.date ;
			double_digit_write(2,20,bcd_to_dec(DATE_HOLDER_NEW.date));

			if(DATE_HOLDER_NEW.month != DATE_HOLDER_OLD.month){
				DATE_HOLDER_OLD.month = DATE_HOLDER_NEW.month ;
				double_digit_write(2, 41, bcd_to_dec(DATE_HOLDER_NEW.month));
			}

			if(DATE_HOLDER_NEW.year != DATE_HOLDER_OLD.year){
				DATE_HOLDER_OLD.year = DATE_HOLDER_NEW.year ;
				triple_digit_write(2, 69, bcd_to_dec(DATE_HOLDER_NEW.year));
			}

			if(DATE_HOLDER_NEW.day != DATE_HOLDER_OLD.day){
				DATE_HOLDER_OLD.day = DATE_HOLDER_NEW.day ;
				day_name_print(DATE_HOLDER_NEW.day - 1 , days);
			}

		}

	}while(which_button != 5);

	return 1;

}
/*********************************************************************/

uint8 study_timer(void){

	black_entire_screen();
	//studying min
	letter_write(7,1,18);
	letter_write(7,8,19);
	letter_write(7,15,20);
	letter_write(7,22,3);
	letter_write(7,29,24);
	letter_write(7,36,8);
	letter_write(7,43,13);
	letter_write(7,50,6);

	letter_write(7,64,12);
	letter_write(7,71,8);
	letter_write(7,78,13);
	letter_write(7,85,18);

	//first we will print 00
	number_write(4,48,0);
	number_write(4,55,0);

	//writing min beside 00
	letter_write(4,69,12);
	letter_write(4,76,8);
	letter_write(4,83,13);

	//drawing the underline
	setColumnAddress(48,62);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 14 ; i++){
		I2C_Write(0xC0);
	}
	I2C_Stop();


	uint8 timer_tracker = 0 ;
	uint8 which_button = 0 ;
	do{
		which_button = 0 ;
		which_button = button_check();

		if(which_button == 3){
			//this means that we pressed left
			//check if we stopping at letter a
			if(timer_tracker == 0){
				timer_tracker = 95 ;
				double_digit_write(4,48,timer_tracker);
			}else{
				timer_tracker-=5 ;
				double_digit_write(4,48,timer_tracker);
			}

		}else if(which_button == 4){
			//this means that we pressed right
			//check if we stopping at letter z
			if(timer_tracker == 95){
				timer_tracker = 0 ;
				double_digit_write(4,48,timer_tracker);
			}else{
				timer_tracker+=5 ;
				double_digit_write(4,48,timer_tracker);
			}
		}

	}while(which_button != 5);

	//here we will black entire screen and print a studying motive and then start the timer.
	black_entire_screen();

	//keep going
	letter_write(7,1,10);
	letter_write(7,8,4);
	letter_write(7,15,4);
	letter_write(7,22,15);

	letter_write(7,36,6);
	letter_write(7,43,14);
	letter_write(7,50,8);
	letter_write(7,57,13);
	letter_write(7,64,6);

	//print start min
	double_digit_write(4,48,timer_tracker);
	//writing min beside 00
	letter_write(4,69,12);
	letter_write(4,76,8);
	letter_write(4,83,13);

	//drawing the underline
	setColumnAddress(48,62);
	setPageAddress(2,7);
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(uint8 i = 0 ; i < 14 ; i++){
		I2C_Write(0xC0);
	}
	I2C_Stop();

	while(timer_tracker ){
		minute_delay();
		timer_tracker--;
		double_digit_write(4,48,timer_tracker);
	}

	//session finished
	return 1 ;

}

/*********************************************************************/
void lamp_on_off(void){
	static uint8 status = 0 ;

	if(status == 0){
		DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_VAL_HIGH);
		status = 1;
	}else if(status){
		DIO_SetPinValue(DIO_PORTC,DIO_PIN7,DIO_PIN_VAL_LOW);
		status = 0;
	}
}
/*********************************************************************/

uint8 main_menu(void){

	printing_menu_with_choice();

	//now we want to take the buttons input
	uint8 which_button = 0 ;
	uint8 menu_tracker = 1 ; //this means that we will land on the first option on the main menu.
	do{
		which_button = 0 ;
		which_button = button_check();

		if(which_button == 3){//here which_button == 3 (we will deal with it as UP direction).
			if(menu_tracker == 1){
				menu_tracker = 3 ;
				color_choice_black(1);
				color_choice_white(3);
			}else{
				//working fine
				menu_tracker-- ;
				color_choice_black(menu_tracker+1);
				color_choice_white(menu_tracker);
			}
		}else if(which_button == 4){// here which_button == 4 (we will deal with it as DOWN Direction).
			if(menu_tracker == 3){
				menu_tracker = 1 ;
				color_choice_black(3);
				color_choice_white(1);
			}else{
				//working fine
				menu_tracker++ ;
				color_choice_black(menu_tracker-1);
				color_choice_white(menu_tracker);
			}
		}
	}while(which_button != 5);

	//now we want to call (study_timer function , clock function , lamp ON/OFF).
	//we want to track menu_tracker variable.
	//if "menu_tracker" ----> 1 , We will call study_timer function.
	//if "menu_tracker" ----> 2 , We will call clock function.
	//if "menu_tracker" ----> 3 , We will call Lamp ON/OFF function.


	if(menu_tracker == 1){
		study_timer();
	}else if(menu_tracker == 2){
		live_clock();
	}else if(menu_tracker == 3){
		lamp_on_off();
	}

	return 1 ;

}
/****************************************************************************/

