/*
 * SPI_prv.h
 *
 *  Created on: Aug 5, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_SPI_SPI_PRV_H_
#define MCAL_SPI_SPI_PRV_H_


#define SPCR		*((volatile u8*)(0x2D))
#define SPSR		*((volatile u8*)(0x2E))
#define SPDR		*((volatile u8*)(0x2F))

/* --- SPI Configuration --- */
#define SPI_MASTER	0
#define SPI_SLAVE	1


#endif /* MCAL_SPI_SPI_PRV_H_ */
