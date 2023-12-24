/*
 * ds3231.h
 *
 *  Created on: Nov 29, 2023
 *      Author: orabi
 */

#ifndef DS3231_H_
#define DS3231_H_

//INCLUDES
#include "I2C.h"
#include "STD.h"


//Holding Data
typedef struct Clock_Data{
	uint8 seconds ;
	uint8 minutes ;
	uint8 hours ;
	uint8 am_pm ;
}CLOCK_DATA;

typedef struct Date_Data{
	uint8 day ;
	uint8 date ;
	uint8 month ;
	uint16 year ;
}DATE_DATA;


//DEFINES
//Write & Read Slave Addresses
#define RTC_SLA_W 0xD0 //SLA+W 11010000
#define RTC_SLA_R 0xD1 //SLA+R 11010001

//PM/AM mode
#define PM_MODE 0b01000000
#define AM_MODE 0b00000000

//Write Operations from the Master to the RTC
void RTC_CLOCK_Write(uint8 hour , uint8 min , uint8 sec , uint8 AM_PM);
void RTC_DATE_Write(uint8 day , uint8 date , uint8 month , uint8 year);

//Read Operations from the Master to the RTC
void RTC_CLOCK_Read(uint8 starting_read_address , CLOCK_DATA *Data_Holder);
void RTC_DATE_Read(uint8 starting_read_address , DATE_DATA *Data_Holder);


#endif /* DS3231_H_ */
