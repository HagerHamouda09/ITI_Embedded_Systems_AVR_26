/*
 * TMR_int.h
 *
 *  Created on: Aug 1, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TMR_TMR_INT_H_
#define MCAL_TMR_TMR_INT_H_

#define TIM_0	 0

//// TWO OUTPUT COMPARE CHANNELS
//TIMER ITSELF
#define TIM_1	1
//Refers specifically to Output Compare Unit A of Timer1.
#define TIM_1_A  2

// ICU
#define TRIG_TYPE_RISING	0
#define TRIG_TYPE_FALLING	1



void MTIMERS_vInit(void);
void MTIMERS_vSetInterval_OVF(void (*Fptr)(void), u32 A_u32IntervalCount);
void MTIMER_vSetPreloadValue(u8 A_u8TimerId ,u16 A_u16Preload);

// CTC
void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount);
void MTIMERS_vSetCompareMatch(u8 A_u8TimerID, u16 A_16OCR_val);

// ICU
void MTIMERS_vSetICU_CB(void (*Fptr)(void));
u16 MTIMERS_u16GetCapturedValue(void);
void MTIMERS_SetTrigger(u8 A_Trigger_Type);


void MTIMERS_vEnableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);
void MTIMERS_vDisableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);


void MTIMERS_vStartTimer(u8 A_u8TimerID);
void MTIMERS_vStopTimer(u8 A_u8TimerID);


#endif /* MCAL_TMR_TMR_INT_H_ */


