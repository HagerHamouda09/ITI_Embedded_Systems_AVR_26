/*
 * SPI_prg.c
 *
 *  Created on: Aug 5, 2026
 *      Author: Hager Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../DIO/DIO_int.h"

#include "SPI_int.h"
#include "SPI_prv.h"
#include "SPI_cfg.h"

void MSPI_vInit(void)
{
#if SPI_MODE == SPI_MASTER
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);   		// SS
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN5, DIO_OUTPUT);           // MOSI
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN7, DIO_OUTPUT);          	// sck
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN6, DIO_INPUT);          	// MISO
	MDIO_vSetPinVal(DIO_PORTB, DIO_PIN6, DIO_HIGH);				// pullup resistor

	// SPI enable | Master | pre_64
	SPCR = 0b01011010;      // MSTR = 1

#endif
#if SPI_MODE == SPI_SLAVE
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN4, DIO_INPUT);    		// SS
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN5, DIO_INPUT);          	// MOSI
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN7, DIO_INPUT);          	// sck
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN6, DIO_OUTPUT);         	// MISO
    SPCR = 0b01001010;
	#endif


	//double speed disable
	CLR_BIT(SPSR, 0);
}


void MSPI_vTransmit(u8 A_u8Byte)
{
	/* Start transmission */
	SPDR = A_u8Byte;

	/* Wait for transmission complete */
	while(!GET_BIT(SPSR, 7))
		;
}
u8 MSPI_u8Receive(void)
{
	/* Wait for reception complete */
	while(!GET_BIT(SPSR, 7))
		;
	/* Return data register */
	return SPDR;
}


u8 MSPI_vTransceive(u8 A_u8Byte)
{
	/* Start transmission */
	SPDR = A_u8Byte;

	/* Wait for transmission complete */
	while(!GET_BIT(SPSR, 7))
		;

	/* Return data register */
	return SPDR;

}

