/*
 * ADC_prg.c
 *
 *  Created on: Jul 29, 2026
 *      Author: Hager Adel
 */

/*
 * ADC_prg.c
 *
 *  Created on: Jul 29, 2026
 *      Author: Hager Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_int.h"
#include "ADC_prv.h"


void MADC_vInit(void)
{
    /* Select AVCC as reference voltage
     * REFS1:REFS0 = 01
     */
    CLR_BIT(ADMUX, 7);
    SET_BIT(ADMUX, 6);


    /* Right adjust ADC result
     * ADLAR = 0
     */
    CLR_BIT(ADMUX, 5);

    /* Select ADC clock prescaler = 64
     * ADPS2:ADPS0 = 110
     * ADC Clock = F_CPU / 64
     */
    SET_BIT(ADCSRA,2);
    SET_BIT(ADCSRA,1);
    CLR_BIT(ADCSRA,0);

    /* Disable Auto Trigger
     * Single Conversion Mode
     */
    CLR_BIT(ADCSRA, 5);

    /* Disable ADC Interrupt
     * Polling mode will be used
     */
    CLR_BIT(ADCSRA, 3);

    /* Enable ADC peripheral
     * ADEN = 1
     */
    SET_BIT(ADCSRA, 7);
}


u16 MADC_u16AnalogRead(u8 A_u8Channel)
{
    /* Select required ADC channel
     * Preserve reference voltage and adjustment bits
     */
	// 0xE0 = 1110 0000
    ADMUX = (ADMUX & (0xE0)) | (A_u8Channel & 0x07);

    /* Start ADC conversion */
    SET_BIT(ADCSRA, 6);

    /* Poll until conversion is complete
     * Wait until ADIF becomes 1
     */
    while(GET_BIT(ADCSRA, 4) == 0){}

    /* Clear ADIF flag
     * ADC flags are cleared by writing '1'
     */
    SET_BIT(ADCSRA, 4);

    /* Return the 10-bit conversion result */
    return ADC;
}


