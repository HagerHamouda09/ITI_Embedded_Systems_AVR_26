/*
 * SSD_int.h
 *
 *  Created on: Jul 23, 2026
 *      Author: Hager Adel
 */

#ifndef HAL_SSD_SSD_INT_H_
#define HAL_SSD_SSD_INT_H_

/*
 * Configuration Options:
 * SSD_TYPE could be
 * SSD_COM_CATHODE
 * SSD_COM_ANODE
 * */
#define SSD_COM_CATHODE		0
#define SSD_COM_ANODE		1

#define SSD_TYPE	SSD_COM_CATHODE

/*
 * Configuration Options:
 * SSD_PORT could be
 * DIO_PORTA
 * DIO_PORTB
 * DIO_PORTC
 * DIO_PORTD
 * */
#define SSD_PORT	DIO_PORTA

void HSSD_vInit(void);
void HSSD_vDisplayNumber(u8 A_u8Num);
void HSSD_vTurnOff(void);

#endif /* HAL_SSD_SSD_INT_H_ */
