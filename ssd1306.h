/*
 * ssd1306.h
 *
 *  Created on: Nov 17, 2023
 *      Author: orabi
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include "Atmega32_Registers.h"
#include "Bit_Operation.h"
#include "STD.h"
#include "I2C.h"

//SLA+W , SLA+R
#define oled_write_address 0b01111010
#define oled_read_address  0b01111011

//for CONTROL_COMMAND
#define CONTROL_COMMAND 			0x00
//for CONTROL_DATA
#define CONTROL_DATA 				0x40

//for enable function
#define COMMAND_DISPLAY_ON 			0xAE
//for COM display offset
#define COMMAND_DISPLAY_OFFSET 		0xD3
//for COM0 attached to which line in RAM
#define COMMAND_DISPLAY_START_LINE 	0x40
//for segment remap
#define COMMAND_SEGMENT_REMAP 		0xA0
//for COM Scan reverse
#define COMMAND_COM_SCAN_DIRECTION  0xC0
//for COM configuration
#define COMMAND_COM_CONFIG			0xDA
//for Contrast
#define COMMAND_CONTRAST 			0x81
//for DCLK
#define COMMAND_DISPLAY_CLOCK_DIVIDE 0xD5
//for setMultiplexRatio
#define COMMAND_MULTIPLEX_RATIO		0xA8
//for ChargePump
#define COMMAND_CHARGE_PUMP 		0x8D
//for inverting the display
#define COMMAND_DISPLAY_INVERSE		0xA6
//for scroll activating
#define COMMAND_SCROLL_ACTIVATION   0x2E
//for resuming GDDRAM
#define COMMAND_DISPLAY_RESUME 		0xA4
//for Page Start
#define COMMAND_SET_PAGE_START_ADDRESS 0xB0
//for Addressing mode
#define COMMAND_ADDRESSING_MODE 0x00

void sendCommand(uint8 cmd);
//void sendCommand(uint8 cmd);
/*
 * Argument : 		Takes the command and send it on the i2c bus.
 * Return Value : 	VOID - No return value.
 *
 * Operation: This function makes the following operation
 * 1)Start I2C communication.
 * 2)Write Control Command 0x00.
 * 3)Write Argument : "cmd" on the bus.
 * 4)Stop the communication
 *
 */


void enable(uint8 on);
//void enable(uint8 on);
/*
 * Argument : 		Status of the screen argument.
 * Return Value : 	No values are returned from the function.
 *
 * Operations : This function set the value of the oled screen either
 * 0xAE--> Sleep Mode.
 * OR
 * 0xAF--> Normal Mode.
 *
 */


void setDisplayOffset(uint8 offset);
//void setDisplayOffset(uint8 offset);
/*
 * Argument : 		it takes the offset of the COM mapping as an argument.
 * Return Value : 	VOID - No values are returned from the function.
 *
 * Operations : Double byte command . The second command specifies the mapping of the display start line to
 * one of COM0~COM63 (assuming that COM0 is the display start line then the display start line register is equal
 * to 0).
 *
 */

void setDisplayStartLine(uint8 line);
//void setDisplayStartLine(uint8 line);
/*
 * Argument : 		it takes the offset of the COM mapping as an argument.
 * Return Value : 	VOID - No values are returned from the function.
 *
 * Operations : This command sets the Display Start line Register to determine starting address of display RAM,
 * by selecting a value from 0 to 63 with value equal to 0 , RAM row 0 is mapped to COM0 . With value equal to 1
 * RAM row 1 is mapped to COM0 and so on.
 *
 */


void setSegmentRemap(uint8 remap);
//void setSegmentRemap(uint8 remap);
/*
 * Argument : 0 or 1 value either remap or not.
 * Return Value : VOID - No return value.
 *
 * Operations : This command changes the mapping between the display data column address and the
 * segment driver.
 * This command only affects subsequent data input . Data already stored in GDDRAM will have no changes.
 *
 * ( 0xA0 = column address 0 is mapped to SEG0 , 0xA1 = column address 127 is mapped to SEG0 )
 */

void setComScanReverse(uint8 r);
//void setComScanReverse(uint8 r);
/*
 * Argument : 0 or 1 value either reverse scan or not.
 * Return Value : VOID - No return value.
 *
 * Operations : If the sent value true (1) the scan direction will be from COM[N-1] to COM0 (0xC8)
 * If the sent value false (0) the scan direction will be from COM0 to COM[N-1] (0xC0)
 *
 */

void setComConfig(uint8 com_alt, uint8 left_right_remap);
//void setComConfig(uint8 com_alt, uint8 left_right_remap);
/*
 * Argument :
 * com_alt --> Use alternative COM pin configuration.
 * left_right_remap --> enable left right remap.
 *
 * Return Value : VOID - No return value.
 *
 * Operations : *)For Alternative COM pin configuration (0xDA A[4] = 1)
 * 				*)COM Output Scan Direction from COM0 to COM63 (0xC0)
 * 				*)Disable COM left/right remap (0xDA A[5] = 0)
 */

void setContrast(uint8 value);
//void setContrast(uint8 value)
/*
 * Argument : value of the contrast (varies from 0x00 to 0xFF)
 *
 * Return Value : VOID - No return value.
 *
 * Operations : Double byte command . First , It send the contrast command (0x81) and after that you send
 * the value of the contrast 0 to 256.
 * Note : The segment output current increases as the contrast step value increases.
 */

void setClockConfig(uint8 divide , uint8 freq);
//void setClockConfig(uint8 divide , uint8 freq);
/*
 * Argument : this command consists of two functions.
 *			*)Display Clock Divide Ratio(D) A[0:3]
 *			set the divide ration to generate DCLK(Display Clock) from CLK the divide ratio is from
 *			1-->16 with reset value = 1
 *
 *			*)Oscillator Frequency (A[4:7])
 *			Program the oscillator frequency Fosc that is the source of CLK if CLS pin is pulled high
 *			the 4-bit value results in 16 different frequency settings is 1000b
 *
 * Return Value : VOID - No return value.
 *
 * Operations : first it sends 0xD5 on the bus to tell the display that we will send a byte that contains
 * in the Most significant nibble the frequency and the Least significant nibble the divide value.
 */

void setMuliplexRatio(uint8 ratio);
//void setMuliplexRatio(uint8 ratio);
/*
 * Argument : ratio value as an argument
 *
 * Return Value : VOID - No return value.
 *
 * Operations : Double byte command . First, It sends the COMMAND_MULTIPLEX_RATIO and after that sends
 * the MUX ratio value on the bus (ratio & 0x3F).
 */

void enableChargePump(uint8 enabled);
//void enableChargePump(uint8 enabled);
/*
 * Argument : state if the Internal voltage supply is enabled or not ( 0 or 1 )
 *
 * Return Value : VOID - No return value.
 *
 * Operations : This function is responsible for enabling the Internal Voltage Supply
 * 0x14 to enable
 * 0x10 to disable
 *
 * for COMMAND_CHARGE_PUMP 0x8D.
 */

void Invert(uint8 invert);
//void Invert(uint8 invert);
/*
 * Argument : state if the display if it inverted or not ( 0 or 1 )
 *
 * Return Value : VOID - No return value.
 *
 * Operations : This function is responsible for inverting the display.
 * 0xA6 Normal display
 * 0xA7 Inverted display
 *
 * for COMMAND_DISPLAY_INVERSE 0xA6.
 */

void scroll(uint8 e);
//void scroll(uint8 e);
/*
 * Argument : activate or deactivate the scroll option
 *
 * Return Value : VOID - No return value.
 *
 * Operations : This function is responsible for activating or deactivating the scroll option.
 *
 * for COMMAND_SCROLL_ACTIVATION 0x2E.
 * for deactivating scrolling 0x2F
 *
 */


void resume(uint8 ignore_ram);
//void resume(uint8 ignore_ram=0);
/*
 * Argument : default argument ignore_ram=0 but you can send true value(1) to make it ignore ram.
 *
 * Return Value : VOID - No return value.
 *
 * Operations : This function is responsible for Display content configuration , In Detail:
 * 0xA4 command enable display outputs according to the GDDRAM contents.
 * if 0xA5 command is issued then it forces the entire display to be 'ON' , regardless of the contents of the
 * GDDRAM.
 *
 */


void setPageStart(uint8 address);
//void setPageStart(uint8 address);
/*
 * Argument : PAGE number = address
 *
 * Return Value : VOID - No return value.
 *
 * Operations : In normal mode display data Ram read or write and page addressing mode , the following steps
 * are required to define the starting RAM access pointer location.
 *
 * set the page start address of the target display location by command 0xB0 to 0xB7.
 * set the lower start column address of pointer by command 0x00~0x0F
 * set the upper start column address of pointer by command 0x10~0x1F
 *
 * but here we are going to address the PAGE in GDDRAM
 * COMMAND_SET_PAGE_START_ADDRESS 0xB0
 */


void sendBuffer(const uint8 *buffer , unsigned long length);
//void sendBuffer(const uint8 *buffer , unsigned long length);
/*
 * Argument :
 * *)pointer to uint8 , this will almost hold buffer array that contains the content.
 * *)length , size of the array(number of bytes sent to the display)
 *
 * Return Value : VOID - No return value.
 *
 * Operations : sending data bytes to the display.
 */


void sendBufferPage(const uint8 *buffer , uint8 page);
//void sendBuffer(const uint8 *buffer , unsigned long length);
/*
 * Argument :
 * *)pointer to uint8 , this will almost hold buffer array that contains the content.
 * *)length , size of the array(number of bytes sent to the display)
 *
 * Return Value : VOID - No return value.
 *
 * Operations : sending data bytes to the display.
 */

void clear();
//void clear();
/*
 * Argument : VOID - No arguments are passed.
 *
 * Return Value : VOID - No return value.
 *
 * Operations : sending 128 zero data bytes for each page.
 */


//some spaghetti code
#define COMMAND_COLUMN_ADDRESS   0x21
#define COMMAND_SET_PAGE_ADDRESS 0x22
void setColumnAddress(uint8 start, uint8 end);
void setPageAddress(uint8 start, uint8 end);


void setAddressingMode(uint8 mode);
//void setAddressingMode(uint8 mode);
/*
 * Argument : mode argument , choose the memory addressing mode
 *
 * Return Value : VOID - No return value.
 *
 * Operations :  There are 3 different memory addressing modes in SSD1306 :
 * 		*)Page addressing mode.
 * 		*)Horizontal Addressing mode.
 * 		*)Vertical Addressing mode.
 *
 * 		for setting memory addressing mode 0x20 -> COMMAND_ADDRESSING_MODE
 * 		    Horizontal = 0x00,
 *  		Vertical   = 0x01,
 *  		Page       = 0x02
 */



void Initialize(void);
//void Initialize(void);
/*
 * Argument : 		VOID - No arguments passed to the function.
 * Return Value : 	VOID - No values returned from the function.
 *
 * Operations:
 * 1)enable function - for normal or sleep mode ;
 * 2)setDisplayOffset - for mapping the COM display if you want to shift the mapping of COM in the display.
 * 3)setDisplayStartline -
 */




#endif /* SSD1306_H_ */
