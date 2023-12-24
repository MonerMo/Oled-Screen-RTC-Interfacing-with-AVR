/*
 * DIO.c
 *
 *  Created on: Aug 20, 2023
 *      Author: orabi
 */


#include "DIO.h"

void DIO_SetPortDirection(uint8 Port, uint8 Direction){

	switch(Port){
	case(DIO_PORTA):
						if(Direction == DIO_PORT_DIR_INPUT)
							DDRA = DIO_PORT_DIR_INPUT ;
						else if(Direction == DIO_PORT_DIR_OUTPUT)
							DDRA = DIO_PORT_DIR_OUTPUT ;
	break ;

	case(DIO_PORTB):
						if(Direction == DIO_PORT_DIR_INPUT)
							DDRB = DIO_PORT_DIR_INPUT ;
						else if(Direction == DIO_PORT_DIR_OUTPUT)
							DDRB = DIO_PORT_DIR_OUTPUT ;
	break ;


	case(DIO_PORTC):
						if(Direction == DIO_PORT_DIR_INPUT)
							DDRC = DIO_PORT_DIR_INPUT ;
						else if(Direction == DIO_PORT_DIR_OUTPUT)
							DDRC = DIO_PORT_DIR_OUTPUT ;
	break ;


	case(DIO_PORTD):
						if(Direction == DIO_PORT_DIR_INPUT)
							DDRD = DIO_PORT_DIR_INPUT ;
						else if(Direction == DIO_PORT_DIR_OUTPUT)
							DDRD = DIO_PORT_DIR_OUTPUT ;
	break ;

	default:
		break;
	}

}

void DIO_SetPinDirection(uint8 Port, uint8 Pin, uint8 Direction){
	switch(Port){

	case(DIO_PORTA):
			if(Direction == DIO_PIN_DIR_INPUT)
				CLR_BIT(DDRA,Pin);
			else if(Direction == DIO_PIN_DIR_OUTPUT)
				SET_BIT(DDRA,Pin);
	break;

	case(DIO_PORTB):
			if(Direction == DIO_PIN_DIR_INPUT)
				CLR_BIT(DDRB,Pin);
			else if(Direction == DIO_PIN_DIR_OUTPUT)
				SET_BIT(DDRB,Pin);
	break;

	case(DIO_PORTC):
			if(Direction == DIO_PIN_DIR_INPUT)
				CLR_BIT(DDRC,Pin);
			else if(Direction == DIO_PIN_DIR_OUTPUT)
				SET_BIT(DDRC,Pin);
		break;

	case(DIO_PORTD):
			if(Direction == DIO_PIN_DIR_INPUT)
				CLR_BIT(DDRD,Pin);
			else if(Direction == DIO_PIN_DIR_OUTPUT)
				SET_BIT(DDRD,Pin);
		break;

	default:
		break;
	}

}

void DIO_SetPortValue(uint8 Port, uint8 Value){
	switch(Value){

	case(DIO_PORT_VAL_HIGH):
			switch(Port){
			case(DIO_PORTA):
					PORTA = DIO_PORT_VAL_HIGH ;
					break;
			case(DIO_PORTB):
					PORTB = DIO_PORT_VAL_HIGH ;
					break;
			case(DIO_PORTC):
					PORTC = DIO_PORT_VAL_HIGH ;
					break;
			case(DIO_PORTD):
					PORTD = DIO_PORT_VAL_HIGH ;
					break;
			default:
				break;
			}
		break;

		case(DIO_PORT_VAL_LOW):
			switch(Port){
			case(DIO_PORTA):
					PORTA = DIO_PORT_VAL_LOW ;
					break;
			case(DIO_PORTB):
					PORTB = DIO_PORT_VAL_LOW ;
					break;
			case(DIO_PORTC):
					PORTC = DIO_PORT_VAL_LOW ;
					break;
			case(DIO_PORTD):
					PORTD = DIO_PORT_VAL_LOW ;
					break;
			default:
				break;
			}
			break;

			default:
				switch(Port){
				case(DIO_PORTA):
						PORTA = Value ;
						break;
				case(DIO_PORTB):
						PORTB = Value ;
						break;
				case(DIO_PORTC):
						PORTC = Value ;
						break;
				case(DIO_PORTD):
						PORTD = Value ;
						break;
				default:
					break;
				}
			break;
	}

}

void DIO_SetPinValue(uint8 Port, uint8 Pin, uint8 Value){
	switch(Value){

	case(DIO_PIN_VAL_HIGH):
			switch(Port){
			case(DIO_PORTA):
					SET_BIT(PORTA,Pin) ;
					break;
			case(DIO_PORTB):
					SET_BIT(PORTB,Pin) ;
					break;
			case(DIO_PORTC):
					SET_BIT(PORTC,Pin) ;
					break;
			case(DIO_PORTD):
					SET_BIT(PORTD,Pin) ;
					break;
			default:
				break;
			}
	break;

	case(DIO_PIN_VAL_LOW):
			switch(Port){
			case(DIO_PORTA):
					CLR_BIT(PORTA,Pin) ;
					break;
			case(DIO_PORTB):
					CLR_BIT(PORTB,Pin) ;
					break;
			case(DIO_PORTC):
					CLR_BIT(PORTC,Pin) ;
					break;
			case(DIO_PORTD):
					CLR_BIT(PORTD,Pin) ;
					break;
			default:
				break;
			}
		break;

	default:
		break;

	}

}



void DIO_GetPortValue(uint8 Port, uint8 *Value){

	switch(Port){
	case DIO_PORTA :
		*Value = PINA ;
		break;

	case DIO_PORTB :
		*Value = PINB ;
		break;

	case DIO_PORTC :
		*Value = PINC ;
		break;

	case DIO_PORTD :
		*Value = PIND ;
		break;

	default:
		break;
	}

}

void DIO_GetPinValue(uint8 Port, uint8 Pin, uint8 *Value){

	switch(Port){
	case DIO_PORTA :
		*Value = GET_BIT(PINA,Pin) ;
		break;

	case DIO_PORTB :
		*Value = GET_BIT(PINB,Pin) ;
		break;

	case DIO_PORTC :
		*Value = GET_BIT(PINC,Pin) ;
		break;

	case DIO_PORTD :
		*Value = GET_BIT(PIND,Pin) ;
		break;

	default:
		break;
	}

}

void DIO_TogglePin(uint8 Port, uint8 Pin){
	switch(Port){
	case DIO_PORTA :
		Toggle_BIT(PORTA,Pin);
		break;

	case DIO_PORTB :
		Toggle_BIT(PORTB,Pin);
		break;

	case DIO_PORTC :
		Toggle_BIT(PORTC,Pin);
		break;

	case DIO_PORTD :
		Toggle_BIT(PORTD,Pin);
		break;

	default:
		break;
	}

}


void DIO_SetPullUpRes(uint8 Port, uint8 Pin){
	switch(Port){
	case DIO_PORTA :
		SET_BIT(PORTA,Pin);
		break;

	case DIO_PORTB :
		SET_BIT(PORTB,Pin);
		break;

	case DIO_PORTC :
		SET_BIT(PORTC,Pin);
		break;

	case DIO_PORTD :
		SET_BIT(PORTD,Pin);
		break;

	default:
		break;
	}

}

