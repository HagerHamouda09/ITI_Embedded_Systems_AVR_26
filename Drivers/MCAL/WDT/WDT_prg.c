/*
 * WDT_prg.c
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "WDT_int.h"
#include "WDT_prv.h"
#include "WDT_cfg.h"

void MWDT_vEnable(void)
{

	/* Enable */
	SET_BIT(WDTCR, 3);

}
void MWDT_vDisable(void)
{
	/* Set Bit 3&4 at the same CLK cycle  */
	WDTCR |= 0b00011000 ;
	/* WDTCR_WDE = 0 */
	/* I don't care for any value in this Reg Cuz I want to Disable */
	WDTCR = 0 ;
}

/* Hint : prebuild config  */
void MWDT_vSleep(void)
{
	/* CLear The Prescaler bits  */
	WDTCR &= WDT_PS_MASKING ;
	/* Set The required prescaller */
	WDTCR |= WDT_PRESCALER ;
}

