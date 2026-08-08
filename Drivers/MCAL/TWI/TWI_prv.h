/*
 * TWI_prv.h
 *
 *  Created on: Aug 7, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TWI_TWI_PRV_H_
#define MCAL_TWI_TWI_PRV_H_

#define TWBR		*((volatile u8*)(0x20))
#define TWCR		*((volatile u8*)(0x56))
#define TWSR		*((volatile u8*)(0x21))
#define TWDR		*((volatile u8*)(0x23))
#define TWAR		*((volatile u8*)(0x22))

/* -------------- Register -------------- */
#define TWEN		2
#define TWINT		7
#define TWEA 		6
#define TWSTA		5
#define TWSTO		4

#endif /* MCAL_TWI_TWI_PRV_H_ */
