/*
 * WDT_prv.h
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_WDT_WDT_PRV_H_
#define MCAL_WDT_WDT_PRV_H_

#define WDTCR	*((volatile u8*)(0x41))

/* Mask to clear prescaler bits (Bits 0, 1, 2) */
#define WDT_PS_MASKING    0xF8

/* Prescaler Timeout Options for ATmega32 */
#define WDT_TIMEOUT_16_3_MS   0b000
#define WDT_TIMEOUT_32_5_MS   0b001
#define WDT_TIMEOUT_65_MS     0b010
#define WDT_TIMEOUT_0_13_S    0b011
#define WDT_TIMEOUT_0_26_S    0b100
#define WDT_TIMEOUT_0_52_S    0b101
#define WDT_TIMEOUT_1_0_S     0b110
#define WDT_TIMEOUT_2_1_S     0b111


#endif /* MCAL_WDT_WDT_PRV_H_ */
