/*
 * TMR_prg.c
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TMR_int.h"
#include "TMR_prv.h"
#include "TMR_cfg.h"

// Callback function pointer.
static void (*G_TIMER_OVF_CB)(void) = {NULL};
static void (*G_TIMER_CTC_CB)(void) = {NULL};

static u8 G_u8Time0Preload=0;
static  u32 G_32IntervalCount=0;

void MTIMERS_vInit(void)
{
#if TIMER0_STATE == ENABLE

#if TIMER0_MODE == NORMAL_OVERFLOW
	CLR_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);

#elif TIMER0_MODE == CTC
	SET_BIT(TCCR0,WGM01);
	CLR_BIT(TCCR0,WGM00);

#elif TIMER0_MODE == PWM_PHASE_CORRECT
	CLR_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);

#if	PWM_OUTPUT_MODE ==	NON_INVERTING
	SET_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	INVERTING
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	DISCONNECTED
	CLR_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#else
#error "Wrong PWM mode"

#endif

#elif TIMER0_MODE == FAST_PWM
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);

#if	PWM_OUTPUT_MODE ==	NON_INVERTING
	SET_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	INVERTING
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,COM00);

#elif	PWM_OUTPUT_MODE ==	DISCONNECTED
	CLR_BIT(TCCR0,COM01);
	CLR_BIT(TCCR0,COM00);

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

	//STOP TIMER0
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);


#endif


#if TIMER1_STATE == ENABLE

#if TIMER1_MODE == FAST_PWM

	CLR_BIT(TCCR1A , 0);
	SET_BIT(TCCR1A , 1);
	SET_BIT(TCCR1B , 3);
	SET_BIT(TCCR1B , 4);

	// NON INVERTING

	CLR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);
	
// ONLY WITH PRESCALLER 8
	ICR1 = 20000;

#endif

#endif
}

void MTIMERS_vStartTimer(u8 A_u8TimerID)
{
	if (A_u8TimerID == TIM_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM0) ;

	}
	if (A_u8TimerID == TIM_1)
	{
		TCCR1B = (TCCR1B & 0xF8) | (0x07 & CLK_SELECT_PRESCALER_TIM1) ;

	}
}
void MTIMERS_vStopTimer(u8 A_u8TimerID)
{
	if (A_u8TimerID == TIM_0)
	{
		TCCR0 = (TCCR0 & 0xF8) | (0x07 & 0x00) ;
	}

	if (A_u8TimerID == TIM_1)
		{
			TCCR1B = (TCCR1B & 0xF8) | (0x07 & 0x00) ;
		}
}

//ovf
void MTIMERS_vSetPreloadValue(u8 A_u8TimerID , u16 A_u16Preload)
{
	switch(A_u8TimerID)
	{
	case TIM_0:
		TCNT0 = (u8)A_u16Preload;
		G_u8Time0Preload = (u8)A_u16Preload;
		break;
	}
}

//ctc
void MTIMERS_vSetCompareMatch(u8 A_u8TimerID , u16 A_u16OCR_val)
{
	switch(A_u8TimerID)
	{
	case TIM_0:
		OCR0 = (u8)A_u16OCR_val;
		break;

	case TIM_1_A:
		OCR1A = A_u16OCR_val;
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
			SET_BIT(TIMSK,0);
			break;

		case CTC:
			SET_BIT(TIMSK,1);
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
			CLR_BIT(TIMSK,0);
			break;

		case CTC:
			CLR_BIT(TIMSK,1);
			break;
		}
	}

}


void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount)
{
	G_32IntervalCount= A_u32IntervalCount;
	G_TIMER_CTC_CB = Fptr;

}

void MTIMERS_vSetInterval_OVF(void (*Fptr)(void),u32 A_u32IntervalCount)
{
	G_32IntervalCount= A_u32IntervalCount;
	G_TIMER_OVF_CB = Fptr;

}
// tim0 overflow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	//A local static unsigned 32-bit variable used to count timer overflows."
	static u32 LS_u32T_OVF = 0;


	LS_u32T_OVF++;
	if(LS_u32T_OVF == G_32IntervalCount)
	{
	    // Reload the preload value FOR THE NEXT INTERVAL
		TCNT0 = G_u8Time0Preload;

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
	if(LS_u32Counter == G_32IntervalCount)
	{
		if(G_TIMER_CTC_CB != NULL)
		{
			G_TIMER_CTC_CB();
		}
		LS_u32Counter = 0;

	}
}
