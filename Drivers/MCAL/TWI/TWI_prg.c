/*
 * TWI_prg.c
 *
 *  Created on: Aug 7, 2026
 *      Author: Hager Adel
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TWI_int.h"
#include "TWI_prv.h"

void MTWI_vInit(void)
{
	/* Enable/Disable Interrupt (disable) */
	CLR_BIT(TWCR, TWINT);

    /* Prescaler = 1 */
    CLR_BIT(TWSR, 0);
    CLR_BIT(TWSR, 1);

	// FCPU = 8 M
	// SCL Frequency = F_CPU / (16 + 2 × TWBR* Prescaler)
	/*Set bit rate speed*/
	TWBR = 32;

}

u8 MTWI_u8SendStartCondition(void)
{
	/* Clear TWINT to start a new TWI operation,
	       generate START condition, and enable TWI */
	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);

	 /* Wait until the START condition is transmitted
	       and the TWI operation is completed */
	while (!(TWCR & (1<<TWINT)))
		;

	/* Status code */
	return (TWSR & 0xF8);

}
u8 MTWI_u8ResendStartCondition(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)| (1<<TWEN);

	while (!(TWCR & (1<<TWINT)))
		;

	/* Status code */
	return (TWSR & 0xF8);
}

u8 MTWI_u8SentStopCondition(void)
{
	/* Generate STOP condition to release the TWI bus
	       after completing the communication */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

	/* Status code */
	return (TWSR & 0xF8);
}

u8 MTWI_u8SendSLA_RW(u8 A_u8SLA, u8 A_u8RW)
{
	/* Shift the 7-bit slave address left by one bit
	       to reserve bit 0 for the R/W bit,
	       then add the requested read/write operation */

	TWDR = (A_u8SLA<<1) | A_u8RW;

	/* Clear TWINT to start transmission
	       and keep the TWI peripheral enabled */
	TWCR = (1<<TWINT) | (1<<TWEN);

	 /* Clear TWSTA because the START condition
	       has already been generated and the next
	       operation is SLA transmission */

	CLR_BIT(TWCR, TWSTA);

    /* Wait until SLA + R/W transmission is completed */

	while (!(TWCR & (1<<TWINT)))
		;

	/* Status code */
	return (TWSR & 0xF8);
}
u8 MTWI_u8SendByte(u8 A_u8Byte)
{
	 /* Load the byte to be transmitted into
	       the TWI Data Register */
	TWDR = A_u8Byte;

	 /* Clear TWINT by shifting one to its position to start transmission
	       and keep the TWI peripheral enabled */

	TWCR = (1<<TWINT) | (1<<TWEN);

	/* Wait until the byte has been transmitted
	       and the slave has responded with ACK/NACK */
	while (!(TWCR & (1<<TWINT)))
		;

	/* Status code */
	return (TWSR & 0xF8);
}
u8 MTWI_u8ReceiveByte(u8* PtrByte, u8 A_u8Ack_NAck)
{
	switch(A_u8Ack_NAck)
	{

	case TWI_ACK:
		TWCR = (1<<TWINT) | (1<<TWEN) ;
		//After receiving this byte, send ACK → I want another byte.
		SET_BIT(TWCR, TWEA);
		break;

	case TWI_NOT_ACK:
		TWCR = (1<<TWINT) | (1<<TWEN) ;
		//After receiving this byte, send NACK → I don't want another byte.
		CLR_BIT(TWCR, TWEA);
		break;
	}

    /* Wait until the byte has been received */

	while (!(TWCR & (1<<TWINT)))
		;

	/* Copy the received byte from the hardware register
	       into the variable supplied by the caller */
	*PtrByte = TWDR;

	 /* Return the TWI status code to indicate
	       the result of the reception */
	/* Status code */
	return (TWSR & 0xF8);
}

u8 MTWI_u8GetStatusCode(void)
{
	/* Status code */
	return (TWSR & 0xF8);
}


