/*
 * TMR_prg.c
 *
 *  Created on: Aug 1, 2026
 *      Author: Hager Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TMR_int.h"
#include "TMR_prv.h"
#include "TMR_cfg.h"

static void (*G_TIMER_OVF_CB)(void) = NULL;
static void(*G_TIMER_CTC_CB)(void) = NULL;

static u8 G_u8Timer0Preload = 0;
static u32 G_u32IntervalCount=0;

// ICU
static void(*G_TIMER1_ICU_CB)(void) = NULL;

void MTIMERS_vInit(void)
{

#if TIMER0_STATE == ENABLE

#if TIMER0_MODE == NORMAL_OVERFLOW
	CLR_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, WGM00);

#elif TIMER0_MODE == CTC
	SET_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, WGM00);

#elif TIMER0_MODE == PWM_PHASE_CORRECT
	CLR_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

#if PWM_OUTPUT_MODE == NON_INVERTING
    CLR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

#elif PWM_OUTPUT_MODE == INVERTING
    SET_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

#elif PWM_OUTPUT_MODE == DISCONNECTED
    CLR_BIT(TCCR0, COM00);
    CLR_BIT(TCCR0, COM01);

#else
#error "Wrong PWM mode"
#endif


#elif TIMER0_MODE == FAST_PWM
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);

#if PWM_OUTPUT_MODE == NON_INVERTING
    CLR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

#elif PWM_OUTPUT_MODE == INVERTING
    SET_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

#elif PWM_OUTPUT_MODE == DISCONNECTED
    CLR_BIT(TCCR0, COM00);
    CLR_BIT(TCCR0, COM01);

#else
#error "Wrong PWM mode"
#endif

#else
#error "Incorrect mode"

#endif

#if INTERRUPT_CONTROL == ENABLE
	MTIMERS_vEnableInterrupt(TIM_0, TIMER0_MODE);


#elif INTERRUPT_CONTROL == DISABLE
	MTIMERS_vDisableInterrupt(TIM_0, TIMER0_MODE);

#else
#error "Incorrect value"
#endif

	//STOP TIMER TILL YOU SET EVERTHING
	CLR_BIT(TCCR0,CS02);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS00);

#endif


#if TIMER1_STATE == ENABLE

#if TIMER1_MODE == FAST_PWM
    // Fast PWM Mode 14 (TOP = ICR1)
    /* -------- Fast PWM Mode 14 (TOP = ICR1) -------- */

    /* WGM10 = 0 */
    CLR_BIT(TCCR1A, 0);

    /* WGM11 = 1 */
    SET_BIT(TCCR1A, 1);

    /* WGM12 = 1 */
    SET_BIT(TCCR1B, 3);

    /* WGM13 = 1 */
    /* Together (WGM13:0 = 1110) selects Fast PWM Mode 14,
       where ICR1 is used as the TOP value. */
    SET_BIT(TCCR1B, 4);


    /* -------- OC1A Output Configuration -------- */

    CLR_BIT(TCCR1A, 6);

    /* Non-inverting PWM:
    SET_BIT(TCCR1A, 7);


    /* -------- PWM Period -------- */

    /* Set the TOP value to 20000 counts.
       With:
           F_CPU = 8 MHz
           Prescaler = 8
       Timer tick = 1 µs

       Therefore:
           20000 × 1 µs = 20 ms

       This produces a 50 Hz PWM signal, which is the standard
       control signal required by hobby servos. */
    ICR1 = 20000;

#elif TIMER1_MODE == ICU
    /* Normal mode */
    CLR_BIT(TCCR1A, 0);
    CLR_BIT(TCCR1A, 1);
    CLR_BIT(TCCR1B, 3);
    CLR_BIT(TCCR1B, 4);

    /* Disconnect OC1A */
    CLR_BIT(TCCR1A, 6);
    CLR_BIT(TCCR1A, 7);

    /* Initial trigger */
    SET_BIT(TCCR1B, 6);    // or CLR_BIT for falling

#endif

#if INTERRUPT_CONTROL == ENABLE
	MTIMERS_vEnableInterrupt(TIM_1, TIMER1_MODE);


#elif INTERRUPT_CONTROL == DISABLE
	MTIMERS_vDisableInterrupt(TIM_1, TIMER1_MODE);

#else
#error "Incorrect value"
#endif

	// stop timer 1
	CLR_BIT(TCCR1B,2);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,0);
#endif

}


void MTIMERS_vStartTimer(u8 A_u8TimerID)
{
	if(A_u8TimerID == TIM_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM0);
	}
	if(A_u8TimerID == TIM_1)
	{
		TCCR1B = (TCCR1B & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM1);
	}

}
void MTIMERS_vStopTimer(u8 A_u8TimerID)
{
	if(A_u8TimerID == TIM_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & 0x00);
	}
	if(A_u8TimerID == TIM_1)
	{
		TCCR1B = (TCCR1B & 0xF8) | (0x07 & 0x00);
	}
}


void MTIMER_vSetPreloadValue(u8 A_u8TimerId ,u16 A_u16Preload)
{
	switch(A_u8TimerId)
	{
	case TIM_0:
		TCNT0 = (u8)A_u16Preload;
		G_u8Timer0Preload = (u8)A_u16Preload;
		break;

	case TIM_1:
		 TCNT1 = A_u16Preload;

	}


}


// ASYNCHRONOUS CALL BACK FOR THE INTERRUPT
void MTIMERS_vSetInterval_OVF(void (*Fptr)(void), u32 A_u32IntervalCount)
{
	G_u32IntervalCount = A_u32IntervalCount;
	G_TIMER_OVF_CB = Fptr;
}

// the number of compare matches to wait (A_u32IntervalCount)
void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount)
{
	G_u32IntervalCount = A_u32IntervalCount;
	G_TIMER_CTC_CB = Fptr;
}


// It loads the value that the timer should count up to
	//before generating a Compare Match event.

void MTIMERS_vSetCompareMatch(u8 A_u8TimerID, u16 A_16OCR_val)
{
	switch(A_u8TimerID)
	{
	case TIM_0:
		// ocr0 is 8 bits so it will automatically
		//convert it to 8 bits
		OCR0 = A_16OCR_val;
		break;

	case TIM_1_A:
	    OCR1A = A_16OCR_val;
	    break;
	}

}

void MTIMERS_vEnableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode)
{
	if(A_u8TimerID == TIM_0)
	{
		switch(A_u8TimerMode)
		{
		case NORMAL_OVERFLOW:
			SET_BIT(TIMSK, 0);
			break;
		case CTC:
			SET_BIT(TIMSK, 1);
			break;
		}
	}
	if(A_u8TimerID == TIM_1)
		{
			switch(A_u8TimerMode)
			{
			case ICU:
				SET_BIT(TIMSK, 5);
				break;
			}
		}

}
void MTIMERS_vDisableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode)
{
	if(A_u8TimerID == TIM_0)
	{
		switch(A_u8TimerMode)
		{
		case NORMAL_OVERFLOW:
			CLR_BIT(TIMSK, 0);
			break;
		case CTC:
			CLR_BIT(TIMSK, 1);
			break;
		}
	}

	if(A_u8TimerID == TIM_1)
	{
		switch(A_u8TimerMode)
		{
		case ICU:
			CLR_BIT(TIMSK, 5);
			break;
		}
	}
}


// ICU FUCNTIONS

void MTIMERS_vSetICU_CB(void (*Fptr)(void))
{
	G_TIMER1_ICU_CB = Fptr;
}

u16 MTIMERS_u16GetCapturedValue(void)
{
	return ICR1;
}
void MTIMERS_SetTrigger(u8 A_Trigger_Type)
{
	switch (A_Trigger_Type)
	{
	case TRIG_TYPE_RISING:
		SET_BIT(TCCR1B, 6);
		break;
	case TRIG_TYPE_FALLING:
		CLR_BIT(TCCR1B, 6);
		break;
	}
	/* CLEAR PENDING ICU FLAG TO PREVENT FALSE TRIGGERS */
	    SET_BIT(TIFR, 5); // ICF1 = 1 clears the flag in AVR hardware!
}


// tim0 overflow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	//A local static unsigned 32-bit variable used to count timer overflows."
	static u32 LS_u32T_OVF = 0;


	LS_u32T_OVF++;
	if(LS_u32T_OVF == G_u32IntervalCount)
	{
	    // Reload the preload value FOR THE NEXT INTERVAL
		TCNT0 = G_u8Timer0Preload;

		if(G_TIMER_OVF_CB != NULL)
		{
			G_TIMER_OVF_CB();
		}
		LS_u32T_OVF = 0;
	}

}

//tim0 ctc
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u32 LS_u32Counter = 0;
	LS_u32Counter++;
	if(LS_u32Counter == G_u32IntervalCount)
	{
		if(G_TIMER_CTC_CB != NULL)
		{
			G_TIMER_CTC_CB();
			// LS_u32Counter = 0;
		}
		//MOVED HERE AS MAYBE NO FUNCTION IS ASSIGNED
		LS_u32Counter = 0;

	}
}

//ICU
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(	G_TIMER1_ICU_CB != NULL)
	{
		G_TIMER1_ICU_CB();
	}
}
