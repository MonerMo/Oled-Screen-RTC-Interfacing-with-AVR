/*
 * Bit_Operation.h
 *
 *  Created on: Aug 20, 2023
 *      Author: orabi
 */

#ifndef BIT_OPERATION_H_
#define BIT_OPERATION_H_

#define SET_BIT(REG,BIT)    (REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)    (REG &= ~(1<<BIT))
#define Toggle_BIT(REG,BIT) (REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)    (REG>>BIT & 1)

#endif /* BIT_OPERATION_H_ */
