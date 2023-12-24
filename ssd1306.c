/*
 * ssd1306.c
 *
 *  Created on: Nov 17, 2023
 *      Author: orabi
 */

#include "ssd1306.h"


void sendCommand(uint8 cmd){
	I2C_Init();
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_COMMAND);
	I2C_Write(cmd);
	I2C_Stop();
}

void enable(uint8 on){
	sendCommand(COMMAND_DISPLAY_ON | on) ;
}

void setDisplayOffset(uint8 offset){
	sendCommand(COMMAND_DISPLAY_OFFSET);
	sendCommand(offset & 0x3F); //anded with 0x3F to choose from 0 to 63 ; 0x3F = 63d.
}

void setDisplayStartLine(uint8 line){
	sendCommand(COMMAND_DISPLAY_START_LINE | (line & 0x3F));
}

void setSegmentRemap(uint8 remap){
	sendCommand(COMMAND_SEGMENT_REMAP | remap);
}

void setComScanReverse(uint8 r){
	sendCommand(COMMAND_COM_SCAN_DIRECTION | (r<<3));
}

void setComConfig(uint8 com_alt, uint8 left_right_remap){
	const uint8 config = (com_alt <<4) | (left_right_remap << 5) | (0x02);

	sendCommand(COMMAND_COM_CONFIG);
	sendCommand(config);
}

void setContrast(uint8 value){
	sendCommand(COMMAND_CONTRAST);
	sendCommand(value);
}

void setClockConfig(uint8 divide , uint8 freq){
	sendCommand(COMMAND_DISPLAY_CLOCK_DIVIDE);
	sendCommand( ((freq&0x0F)<<4) | (divide & 0x0F));
}

void setMuliplexRatio(uint8 ratio){
	sendCommand(COMMAND_MULTIPLEX_RATIO);
	sendCommand(ratio & 0x3F);
}

void enableChargePump(uint8 enabled){
	sendCommand(COMMAND_CHARGE_PUMP);
	sendCommand(0x10 | (enabled<<2));
}

void Invert(uint8 invert){
	sendCommand(COMMAND_DISPLAY_INVERSE | invert);
}

void scroll(uint8 e){
	sendCommand(COMMAND_SCROLL_ACTIVATION | e);
}

void resume(uint8 ignore_ram){
	sendCommand(COMMAND_DISPLAY_RESUME | ignore_ram);
}

void setPageStart(uint8 address){
	sendCommand(COMMAND_SET_PAGE_START_ADDRESS | (address & 0x07));
}

void sendBuffer(const uint8 *buffer , unsigned long length ){
	I2C_Init();
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);
	for(unsigned long i = 0 ; i < length ; i++){
		I2C_Write(buffer[i]);
	}
	I2C_Stop();
}

void setAddressingMode(uint8 mode){
	sendCommand(COMMAND_ADDRESSING_MODE);
	sendCommand(mode);
}

void clear(){
	//clear the display by writing a zeroed page buffer
	uint8 page_buf[128] = {0};
	setAddressingMode(0x02);
	for(int i = 0 ; i < 8 ; i++){
		setPageStart(i);
		sendBuffer(page_buf,sizeof(page_buf));
	}
}

void setColumnAddress(uint8 start, uint8 end){
        sendCommand(COMMAND_COLUMN_ADDRESS);
        sendCommand(start);
        sendCommand(end);
}

void setPageAddress(uint8 start, uint8 end){
    sendCommand(COMMAND_SET_PAGE_ADDRESS);
    sendCommand(start & 0x07);
    sendCommand(end & 0x07);
}

void sendBufferPage(const uint8 *buffer , uint8 page){
	//we want to make a loop for each page
	setColumnAddress(0,127);
	setPageAddress(page,7);

	//first initialize the communication
	I2C_Init();
	I2C_Start(oled_write_address);
	I2C_Write(CONTROL_DATA);

	uint8 start_byte_in_bitmap = page * 128 ;
	uint8 end_byte_in_bitmap = start_byte_in_bitmap + 127 ;
	for(;start_byte_in_bitmap <= end_byte_in_bitmap ; start_byte_in_bitmap++){
		I2C_Write(buffer[start_byte_in_bitmap]);
	}
	I2C_Stop();


}


void Initialize(void){
	enable(0);
	setDisplayOffset(0);
	setDisplayStartLine(0);
	setSegmentRemap(1);
	setComScanReverse(0);
	setComConfig(1, 0);
	setContrast(0x7F);
	setClockConfig(0x00, 0x08);
	setMuliplexRatio(63);
	enableChargePump(1);
	Invert(0);
	scroll(0);
	enable(1);
	resume(0);
	clear();
}
