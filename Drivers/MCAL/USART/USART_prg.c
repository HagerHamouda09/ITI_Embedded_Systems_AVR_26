/*
 * USART_prg.c
 *
 *  Created on: Aug 4, 2026
 *      Author: Hager Adel
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_int.h"
#include "USART_prv.h"

/*----------------------------------------------------------
 * USART Configuration
 *
 * Asynchronous Mode:
 * - No separate clock wire is used.
 * - Both transmitter and receiver agree on the same baud rate
 *   (e.g., 9600 bps) to communicate.
 *
 * No Parity:
 * - No extra bit is added for error detection.
 * - Data frame is shorter and transmission is faster.
 *
 * 1 Stop Bit:
 * - One stop bit marks the end of each transmitted frame.
 * - This is the most commonly used configuration.
 *
 * 8-bit Data:
 * - Each transmitted character consists of 8 data bits.
 * - Allows sending values from 0 to 255 (ASCII characters,
 *   numbers, symbols, etc.).
 *
 * Clock Polarity:
 * - Used only in Synchronous mode.
 * - Ignored in Asynchronous mode.
 *---------------------------------------------------------*/

void MUSART_vInit(void)
{
	// enable receiver & transmitter
	//two-way communication
	UCSRB = 0b00011000;
	// enable UCSRC reg | asynch | no parity | 1 stop bit | 8 bit data | no clk polarity
	UCSRC = 0b10000110;

	//The baud rate is the communication speed.
//	/For UART/USART, it is usually the number of
	//bits transmitted per second (bps).
	/*
	 * 9600 bps
19200 bps
38400 bps
57600 bps
115200 bps

If one device is set to 9600 bps and the other to 115200 bps,
 they won't understand each other because they
sample the bits at different times
	 */
	//The baud rate register is 12 bits wide in the ATmega32.
	//UBRR = (F_CPU / (16 × Baud Rate)) - 1
	UBRRL = 51;
	UBRRH = 0;


}
void MUSART_vTransmit(u8 A_u8Byte)
{
	/* Wait for empty transmit buffer */
	//It tells you whether UDR is ready to accept a new byte.
	/*
	 * UDRE = 1 → UDR is empty → You can write a new byte.
		UDRE = 0 → UDR is still busy → Wait.
	 */
	while(!GET_BIT(UCSRA, UDRE));

	/* Put data into buffer, sends the data */
	UDR = A_u8Byte;
}

u8 MUSART_vReceive(void)
{
	/* Wait for data to be received */
	while(!GET_BIT(UCSRA, RXC));

	/* Get and return received data from buffer */
	return UDR;
}
