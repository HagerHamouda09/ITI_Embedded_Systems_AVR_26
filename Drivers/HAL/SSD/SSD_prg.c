/*
 * SSD_prg.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Hager Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "SSD_int.h"


static u8 Sevensegment[] = {
		0b00111111 ,  // 0
		0b00000110 ,  // 1
		0b01011011 ,  // 2
		0b01001111 ,  // 3
		0b01100110 ,  // 4
		0b01101101 ,  // 5
		0b01111101 ,  // 6
		0b00000111 ,  // 7
		0b01111111 ,  // 8
		0b01101111    // 9

};

void HSSD_vInit(void)
{
	MDIO_vSetPortDir(SSD_PORT,DIO_PORT_OUTPUT);
}
void HSSD_vDisplayNumber(u8 A_u8Num)
{
	if(A_u8Num < 10 && A_u8Num >= 0)
	{
#if SSD_TYPE == SSD_COM_CATHODE
	MDIO_vSetPortVal(SSD_PORT, Sevensegment[A_u8Num]);
#elif SSD_TYPE == SSD_COM_ANODE
	MDIO_vSetPortVal(SSD_PORT, ~Sevensegment[A_u8Num]);
#endif
	}
}

void HSSD_vTurnOff(void)
{
#if SSD_TYPE == SSD_COM_CATHODE
	MDIO_vSetPortVal(SSD_PORT, 0x00);
#elif SSD_TYPE == SSD_COM_ANODE
	MDIO_vSetPortVal(SSD_PORT, 0xFF);
#endif
}



