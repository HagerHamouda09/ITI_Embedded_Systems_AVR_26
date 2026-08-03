/*
 * TMR_prv.h
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_TMR_TMR_PRV_H_
#define MCAL_TMR_TMR_PRV_H_

#define OCR0	*((volatile u8*)(0x5C))
#define TIMSK	*((volatile u8*)(0x59))
#define TCCR0	*((volatile u8*)(0x53))
#define TCNT0	*((volatile u8*)(0x52))
#define TIFR	*((volatile u8*)(0x58))

//TCCR0 BITS
#define	FOC0	7
#define	WGM00	6
#define	COM01	5
#define	COM00	4
#define	WGM01	3
#define	CS02	2
#define	CS01	1
#define	CS00	0


// MODES
#define	NORMAL_OVERFLOW		0
#define	CTC					1
#define	PWM_PHASE_CORRECT	2
#define	FAST_PWM			3

// PRESCALER
#define NO_CLK	0x00
#define CLK_NO_PRESCALLING	0x01
#define CLK_8	0x02
#define CLK_64	0x03
#define CLK_256	0x04
#define CLK_1024	0x05

#define EXTERNAL_TO_FALLING	0x06
#define EXTERNAL_TO_RISING	0x07

#define ENABLE	1
#define DISABLE	0

#endif /* MCAL_TMR_TMR_PRV_H_ */
