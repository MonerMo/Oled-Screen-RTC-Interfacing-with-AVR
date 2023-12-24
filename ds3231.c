/*
 * ds3231.c
 *
 *  Created on: Nov 29, 2023
 *      Author: orabi
 */


#include "ds3231.h"


void RTC_CLOCK_Write(uint8 hour , uint8 min , uint8 sec , uint8 AM_PM){
	//first we want to Initialize clock rate of I2C & Generate start and send SLA+W address
	I2C_Init();
	I2C_Start(RTC_SLA_W);

	//now we want to write the starting writing register address
	I2C_Write(0x00); //Starting from seconds register address (0x00)
	//now you pass the values : sec , min , hours ;
	I2C_Write(sec);
	I2C_Write(min);

	//0b01000000 means 12 hours mode
	hour = hour | (AM_PM<<5) | 0b01000000;
	I2C_Write(hour);

	//stop communication
	I2C_Stop();

}

void RTC_DATE_Write(uint8 day , uint8 date , uint8 month , uint8 year){
	//first we want to Initialize clock rate of I2C & Generate start and send SLA+W address
	I2C_Init();
	I2C_Start(RTC_SLA_W);

	//now we want to write the starting writing register address
	I2C_Write(0x03); //Starting from seconds register address (0x03)
	//now you pass the values : day , date , month , year
	I2C_Write(day);
	I2C_Write(date);
	I2C_Write(month);
	I2C_Write(year);
	I2C_Stop();
}


void RTC_CLOCK_Read(uint8 starting_read_address , CLOCK_DATA *Data_Holder){
	//first we want to Initialize clock rate of I2C & Generate start and send SLA+W address
	I2C_Init();
	I2C_Start(RTC_SLA_W);
	//now we will set the pointer to the address we want to read from
	I2C_Write(starting_read_address);

	//now we will generate a repeated start but in reading mode this time
	I2C_Repeated_Start(RTC_SLA_R);
	Data_Holder->seconds = I2C_Read_ACK();
	Data_Holder->minutes = I2C_Read_ACK();
	Data_Holder->hours = I2C_Read_NACK() ;
	Data_Holder->am_pm = ( ( Data_Holder->hours & 0b00100000 ) >> 5 ) ;

	I2C_Stop();

}

void RTC_DATE_Read(uint8 starting_read_address , DATE_DATA *Data_Holder){
	//first we want to Initialize clock rate of I2C & Generate start and send SLA+W address
	I2C_Init();
	I2C_Start(RTC_SLA_W);
	//now we will set the pointer to the address we want to read from
	I2C_Write(starting_read_address);

	//now we will generate a repeated start but in reading mode this time
	I2C_Repeated_Start(RTC_SLA_R);
	Data_Holder->day = I2C_Read_ACK();
	Data_Holder->date = I2C_Read_ACK();
	Data_Holder->month = I2C_Read_ACK();
	Data_Holder->year = I2C_Read_NACK();

	I2C_Stop();

}
