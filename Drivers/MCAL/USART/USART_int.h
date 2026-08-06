/*
 * USART_int.h
 *
 *  Created on: Aug 4, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_USART_USART_INT_H_
#define MCAL_USART_USART_INT_H_


void MUSART_vInit(void);
void MUSART_vTransmit(u8 A_u8Byte);
u8 MUSART_vReceive(void);


#endif /* MCAL_USART_USART_INT_H_ */
