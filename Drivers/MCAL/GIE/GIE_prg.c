/*
 * GIE_prg.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Hager Adel
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "GIE_int.h"
#include "GIE_prv.h"


void MGIE_vEnableGlobalInterrupt(void)
{
	SET_BIT(SREG,7);
}
void MGIE_vDisableGlobalInterrupt(void)
{
	CLR_BIT(SREG,7);
}
