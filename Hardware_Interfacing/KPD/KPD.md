#  Session 12 Labs (Keypad & LCD Interfacing)

### **Lab 1:** 3x3 Keypad Key Detection Displayed on LCD (Bare-Metal Scanning)
Write an AVR C program to interface a $3\times3$ keypad matrix (`PORTB`) with a character LCD screen (`HAL LCD Driver`). 

The columns (`PB0`-`PB2`) are configured as outputs initially driven HIGH, while rows (`PB4`-`PB6`) are set as inputs with internal pull-up resistors enabled. The program performs matrix scanning by pulling each column LOW sequentially, reading row pin states, applying debouncing, and printing the pressed key onto the LCD.

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include <util/delay.h>

const u8 KeyMap[3][3] =
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

int main(void)
{
    u8 row, col;

    MDIO_vInit();
    HLCD_vInit();

    /* Columns (PB0-PB2) -> Output (Default HIGH) */
    for(col = DIO_PIN0; col <= DIO_PIN2; col++)
    {
        MDIO_vSetPinDir(DIO_PORTB, col, DIO_OUTPUT);
        MDIO_vSetPinVal(DIO_PORTB, col, DIO_HIGH);
    }

    /* Rows (PB4-PB6) -> Input with Internal Pull-up Enabled */
    for(row = DIO_PIN4; row <= DIO_PIN6; row++)
    {
        MDIO_vSetPinDir(DIO_PORTB, row, DIO_INPUT);
        MDIO_vSetPinVal(DIO_PORTB, row, DIO_HIGH);
    }

    while(1)
    {
        for(col = DIO_PIN0; col <= DIO_PIN2; col++)
        {
            /* Activate current column (Drive LOW) */
            MDIO_vSetPinVal(DIO_PORTB, col, DIO_LOW);

            for(row = DIO_PIN4; row <= DIO_PIN6; row++)
            {
                /* Check if a key in the active column is pressed */
                if(MDIO_u8GETPinVal(DIO_PORTB, row) == DIO_LOW)
                {
                    _delay_ms(20); // Software Debounce Delay

                    if(MDIO_u8GETPinVal(DIO_PORTB, row) == DIO_LOW)
                    {
                        /* Wait until button is released */
                        while(MDIO_u8GETPinVal(DIO_PORTB, row) == DIO_LOW);

                        /* Display mapped key character on LCD */
                        HLCD_vClearScreen();
                        HLCD_vSendChar(KeyMap[row - DIO_PIN4][col - DIO_PIN0]);
                    }
                }
            }

            /* Deactivate current column (Return to HIGH) */
            MDIO_vSetPinVal(DIO_PORTB, col, DIO_HIGH);
        }
    }

    return 0;
}


```



 ### KPD & LCD WITH KPD DRIVER

```c

#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"

#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KPD/KPD_int.h"

const u8 KeyMap[KPD_ROW][KPD_COL] =
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

int main(void)
{
    u8 PressedKey;

    MDIO_vInit();

    HLCD_vInit();
    HKPD_vInit();

    while(1)
    {
        PressedKey = HKPD_u8GetPressedKey(KeyMap);

        if(PressedKey != NO_KEY)
        {
            HLCD_vClearScreen();    
            HLCD_vSendChar(PressedKey);
        }
    }

    return 0;
}

```
