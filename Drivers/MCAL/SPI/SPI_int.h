/*
 * SPI_int.h
 *
 *  Created on: Aug 5, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_SPI_SPI_INT_H_
#define MCAL_SPI_SPI_INT_H_

void MSPI_vInit(void);

void MSPI_vTransmit(u8 A_u8Byte);

u8 MSPI_u8Receive(void);

u8 MSPI_vTransceive(u8 A_u8Byte);


#endif
