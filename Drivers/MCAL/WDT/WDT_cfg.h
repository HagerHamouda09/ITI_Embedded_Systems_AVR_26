/*
 * WDT_cfg.h
 *
 *  Created on: Aug 3, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_WDT_WDT_CFG_H_
#define MCAL_WDT_WDT_CFG_H_

/*
 * Select Watchdog Prescaler Timeout:
 * Options (at 5V VCC):
 * - WDT_TIMEOUT_16_3_MS
 * - WDT_TIMEOUT_32_5_MS
 * - WDT_TIMEOUT_65_MS
 * - WDT_TIMEOUT_0_13_S
 * - WDT_TIMEOUT_0_26_S
 * - WDT_TIMEOUT_0_52_S
 * - WDT_TIMEOUT_1_0_S
 * - WDT_TIMEOUT_2_1_S
 */
#define WDT_PRESCALER    WDT_TIMEOUT_2_1_S

#endif /* MCAL_WDT_WDT_CFG_H_ */
