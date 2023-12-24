/*
 * seven_segment.h
 *
 *  Created on: Aug 20, 2023
 *      Author: orabi
 */

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_
#include <avr/io.h>

//we want to make two seven segments work properly

void display(int print){



	//theses values for common cathode
	unsigned int values[10] = { 0b0111111 , 0b00000110 ,
	0b01011011,0b01001111,0b01100110,0b1101101,0b1111101,
	0b00000111,0b01111111,0b01101111
	};

	//we will output on portd
	DDRD = 0xff ;
	PORTD = values[print] ;


}

#endif /* SEVEN_SEGMENT_H_ */
