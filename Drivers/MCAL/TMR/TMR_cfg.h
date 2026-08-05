/*
 * TMR_cfg.h
 *
 *  Created on: Aug 1, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TMR_TMR_CFG_H_
#define MCAL_TMR_TMR_CFG_H_


/* Enable and Disable Timers*/
/*Options:
 * ENABLE
 * DISABLE
 * */
#define TIMER0_STATE  	ENABLE
#define TIMER1_STATE  	ENABLE
//#define TIMER2_STATE  	DISABLE

#define DISCONNECTED    0
#define NON_INVERTING   1
#define INVERTING       2

#define PWM_OUTPUT_MODE NON_INVERTING

/* Configuire Prescaller */
/*Options:
 *  NO_CLK
	CLK_NO_PRESCALLING
 	CLK_8
 	CLK_64
    CLK_256
    CLK_1024
    EXTERNAL_T0_FALLING
    EXTERNAL_T0_RISING
 * */
#define CLK_SELECT_PRESCALER_TIM0	CLK_8
#define CLK_SELECT_PRESCALER_TIM1	CLK_8

/* SELECT MODE */
/*Options:
 * NORMAL_OVERFLOW
   PWM_PHASE_CORRECT
   CTC
   FAST_PWM
 * */
#define TIMER0_MODE	FAST_PWM
#define TIMER1_MODE	ICU


/*Interrupt enable/ disable */
#define INTERRUPT_CONTROL	ENABLE

#endif /* MCAL_TMR_TMR_CFG_H_ */


