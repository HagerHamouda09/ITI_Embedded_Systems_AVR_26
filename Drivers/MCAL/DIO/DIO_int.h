/*
 * DIO_int.h
 *
 *  Created on: Jul 22, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_DIO_DIO_INT_H_
#define MCAL_DIO_DIO_INT_H_


#define DIO_OUTPUT		1
#define DIO_INPUT		0

#define DIO_PORTA 		0
#define DIO_PORTB 		1
#define DIO_PORTC 		2
#define DIO_PORTD 		3

#define DIO_PIN0		0
#define DIO_PIN1		1
#define DIO_PIN2		2
#define DIO_PIN3		3
#define DIO_PIN4		4
#define DIO_PIN5		5
#define DIO_PIN6		6
#define DIO_PIN7		7

#define DIO_HIGH		1
#define DIO_LOW			0

#define DIO_PORT_OUTPUT  0xFF
#define DIO_PORT_INPUT	 0x00

/* Initialize Registers */
void MDIO_vInit(void);

/* Pin functions */
void MDIO_vSetPinDir(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8PinDir);
void MDIO_vSetPinVal(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8PinVal);
u8 MDIO_u8GETPinVal(u8 A_u8PortNo, u8 A_u8PinNo);
void MDIO_vTogPinVal(u8 A_u8PortNo, u8 A_u8PinNo);

/* Port functions */
void MDIO_vSetPortDir(u8 A_u8PortNo, u8 A_u8PortDir);
void MDIO_vSetPortVal(u8 A_u8PortNo, u8 A_u8PortVal);
u8 MDIO_u8GETPortVal(u8 A_u8PortNo);



#endif /* MCAL_DIO_DIO_INT_H_ */
