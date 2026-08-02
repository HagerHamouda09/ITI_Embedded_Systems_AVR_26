/*
 * ADC_int.h
 *
 *  Created on: Jul 29, 2026
 *      Author: Hager Adel
 */

#ifndef MCAL_ADC_ADC_INT_H_
#define MCAL_ADC_ADC_INT_H_

#define CHANNEL_0           0
#define CHANNEL_1           1
#define CHANNEL_2           2
#define CHANNEL_3           3
#define CHANNEL_4           4
#define CHANNEL_5           5
#define CHANNEL_6           6
#define CHANNEL_7           7




void MADC_vInit(void);
u16  MADC_u16AnalogRead(u8 A_u8Channel);

#endif /* MCAL_ADC_ADC_INT_H_ */
