/*
 * TMR_int.h
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TMR_TMR_INT_H_
#define MCAL_TMR_TMR_INT_H_

#define TIM_0	0

//TIMER ITSELF
#define TIM_1	1
//Refers specifically to Output Compare Unit A of Timer1.
#define TIM_1_A  2

void MTIMERS_vInit(void);

void MTIMERS_vStartTimer(u8 A_u8TimerID);
void MTIMERS_vStopTimer(u8 A_u8TimerID);

//ovf
void MTIMERS_vSetPreloadValue(u8 A_u8TimerID , u16 A_u16Preload);
void MTIMERS_vSetInterval_OVF(void (*Fptr)(void),u32 A_u32IntervalCount);


//ctc
void MTIMERS_vSetCompareMatch(u8 A_u8TimerID , u16 A_u16OCR_val);
void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32IntervalCount);



void MTIMERS_vEnableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);
void MTIMERS_vDisableInterrupt(u8 A_u8TimerID, u8 A_u8TimerMode);


#endif /* MCAL_TMR_TMR_INT_H_ */
