/*
 * USART_prv.h
 *
 *  Created on: Aug 4, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_USART_USART_PRV_H_
#define MCAL_USART_USART_PRV_H_

#define UDR			*((volatile u8*)(0x2C))
#define UCSRA		*((volatile u8*)(0x2B))
#define UCSRB		*((volatile u8*)(0x2A))
#define UCSRC		*((volatile u8*)(0x40))
#define UBRRL		*((volatile u8*)(0x29))
#define UBRRH		*((volatile u8*)(0x40))

/* NOTE:
 * UCSRC and UBRRH share the same I/O address (0x40) in the ATmega32.
 * When writing:
 *   URSEL = 1  -> Access UCSRC (USART Control Register C)
 *   URSEL = 0  -> Access UBRRH (Upper Baud Rate Register)
 */

/*
Why these two registers specifically?

Because you rarely write to them at the same time.

UBRRH is usually written once during initialization to set the baud rate.
UCSRC is also usually written once during initialization to configure the USART.

Since they're not accessed simultaneously, they can safely share an address.
*/


#define UDRE	5
#define RXC		7

#endif /* MCAL_USART_USART_PRV_H_ */
