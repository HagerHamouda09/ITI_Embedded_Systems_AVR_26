/*
 * EXTI_prg.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Hager Adel
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../DIO/DIO_int.h"
#include "EXTI_int.h"
#include "EXTI_prv.h"

// array of function pointers
static void (*G_EXTI_Callback[3])(void) = {NULL};

void MEXTI_vInit(void)
{

#if EXTI_INT0_STATE == ENABLE
	/* Sense control */
#if EXTI_INT0_SENSE_CTRL==EXTI_FALLING
	// falling edge for INT0
	CLR_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#elif EXTI_INT0_SENSE_CTRL == EXTI_RISING
	// rising edge for INT0
	SET_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#elif EXTI_INT0_SENSE_CTRL == EXTI_LOW_LVL
	// low level for INT0
	CLR_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
#elif EXTI_INT0_SENSE_CTRL == EXTI_ONCHANGE
	// any logical change for INT0
	SET_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);
#else
#error "Sense control must be EXTI_FALLING , EXTI_RISING , EXTI_LOW_LVL or EXTI_ONCHANGE "
#endif
	/* Enable interrupt */
	SET_BIT(GICR,6);
#endif

#if EXTI_INT1_STATE == ENABLE
	/* Sense control */
#if EXTI_INT1_SENSE_CTRL == EXTI_FALLING
	// falling edge for INT1
	CLR_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
#elif EXTI_INT1_SENSE_CTRL == EXTI_RISING
	// rising edge for INT1
	SET_BIT(MCUCR,2);
	SET_BIT(MCUCR,3);
#elif EXTI_INT1_SENSE_CTRL == EXTI_LOW_LVL
	// low level for INT1
	CLR_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);
#elif EXTI_INT1_SENSE_CTRL == EXTI_ONCHANGE
	// any logical change for INT1
	SET_BIT(MCUCR,2);
	CLR_BIT(MCUCR,3);
#else
#error "Sense control must be EXTI_FALLING , EXTI_RISING , EXTI_LOW_LVL or EXTI_ONCHANGE "
#endif
	/* Enable interrupt */
	SET_BIT(GICR,7);
#endif

#if EXTI_INT2_STATE == ENABLE
	/* Sense control */
#if EXTI_INT2_SENSE_CTRL == EXTI_FALLING
	// falling edge for INT2
	CLR_BIT(MCUCSR,6);
#elif EXTI_INT2_SENSE_CTRL == EXTI_RISING
	// rising edge for INT2
	SET_BIT(MCUCSR,6);
#else
#error "Sense control must be EXTI_FALLING or EXTI_RISING "
#endif
	/* Enable interrupt */
	SET_BIT(GICR,5);
#endif

}

void MEXTI_vCallBackFunction(void (*Fptr)(void), u8 A_u8InterruptNo)
{
	G_EXTI_Callback[A_u8InterruptNo] = Fptr;
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	// call a specific function
	if(G_EXTI_Callback[EXTI_INT0_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT0_ID]();
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	// call a specific function
	if(G_EXTI_Callback[EXTI_INT1_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT1_ID]();
	}
}


void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	// call a specific function
	if(G_EXTI_Callback[EXTI_INT2_ID] != NULL)
	{
		G_EXTI_Callback[EXTI_INT2_ID]();
	}
}

