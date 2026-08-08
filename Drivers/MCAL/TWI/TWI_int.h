/*
 * TWI_int.h
 *
 *  Created on: Aug 7, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TWI_TWI_INT_H_
#define MCAL_TWI_TWI_INT_H_

#define TWI_WRITE	0
#define TWI_READ	1

#define TWI_ACK		1
#define TWI_NOT_ACK 0

void MTWI_vInit(void);

u8 MTWI_u8SendStartCondition(void);

u8 MTWI_u8ResendStartCondition(void);

u8 MTWI_u8SentStopCondition(void);

u8 MTWI_u8SendSLA_RW(u8 A_u8SLA, u8 A_u8RW);

u8 MTWI_u8SendByte(u8 A_u8Byte);

u8 MTWI_u8ReceiveByte(u8* PtrByte, u8 A_u8Ack_NAck);

u8 MTWI_u8GetStatusCode(void);

#endif /* MCAL_TWI_TWI_INT_H_ */




