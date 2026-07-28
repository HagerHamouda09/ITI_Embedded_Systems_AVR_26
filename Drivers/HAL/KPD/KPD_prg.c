
/*
 * KPD_prg.c
 *
 *  Created on: Jul 26, 2026
 *      Author: Hager Adel
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_int.h"

#include "KPD_cfg.h"
#include "KPD_int.h"


/*================ Initialization ================*/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_int.h"

#include "KPD_cfg.h"
#include "KPD_int.h"


void HKPD_vInit(void)
{
    u8 i;

    /* Configure all column pins as outputs */
    for(i = COL_INIT; i <= COL_END; i++)
    {
        MDIO_vSetPinDir(KPD_COL_PORT, i, DIO_OUTPUT);

        /* Deactivate all columns initially (HIGH) */
        MDIO_vSetPinVal(KPD_COL_PORT, i, DIO_HIGH);
    }

    /* Configure all row pins as inputs */
    for(i = ROW_INIT; i <= ROW_END; i++)
    {
        MDIO_vSetPinDir(KPD_ROW_PORT, i, DIO_INPUT);

        /* Enable internal pull-up resistors */
        MDIO_vSetPinVal(KPD_ROW_PORT, i, DIO_HIGH);
    }
}


u8 HKPD_u8GetPressedKey(const u8 KeyMap[KPD_ROWS][KPD_COLS])
{
    /* Scan every column one by one */
    for(u8 col = COL_INIT; col <= COL_END; col++)
    {
        /* Activate the current column by making it LOW */
        MDIO_vSetPinVal(KPD_COL_PORT, col, DIO_LOW);

        /* Check all rows */
        for(u8 row = ROW_INIT; row <= ROW_END; row++)
        {
            /* If row becomes LOW, then a key is pressed */
            if(MDIO_u8GETPinVal(KPD_ROW_PORT, row) == DIO_LOW)
            {
                /* Debouncing delay */
                _delay_ms(20);

                /* Confirm the key is still pressed */
                if(MDIO_u8GETPinVal(KPD_ROW_PORT, row) == DIO_LOW)
                {
                    /* Wait until the user releases the key */
                    while(MDIO_u8GETPinVal(KPD_ROW_PORT, row) == DIO_LOW);

                    /* Restore the current column to HIGH */
                    MDIO_vSetPinVal(KPD_COL_PORT, col, DIO_HIGH);

            
                    return KeyMap[row - ROW_INIT][col - COL_INIT];
                }
            }
        }

        /* Deactivate the current column before scanning the next one */
        MDIO_vSetPinVal(KPD_COL_PORT, col, DIO_HIGH);
    }

    /* No key was pressed */
    return NO_KEY;
}