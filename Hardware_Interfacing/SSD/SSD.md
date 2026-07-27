#  Session 12 Labs (7-Segment Display)

### **Lab 1:** 7-Segment Auto Counter (0 to 9)
Write an AVR C program to display digits from 0 to 9 sequentially on a Common Cathode 7-segment display  with a **1-second delay**. 

*(Note: For a Common Anode configuration, use `~Sevensegment[i]` to invert the bit pattern).*

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

// Common Cathode segment values for digits 0-9
u8 Sevensegment[] =
{
    0b00111111,   // 0
    0b00000110,   // 1
    0b01011011,   // 2
    0b01001111,   // 3
    0b01100110,   // 4
    0b01101101,   // 5
    0b01111101,   // 6
    0b00000111,   // 7
    0b01111111,   // 8
    0b01101111    // 9
};

int main(void)
{
    MDIO_vInit();

    // Configure PORTD as OUTPUT for 7-Segment
    MDIO_vSetPortDir(DIO_PORTA, DIO_PORT_OUTPUT);

    u8 size = sizeof(Sevensegment) / sizeof(Sevensegment[0]);

    while (1)
    {
        for (u8 i = 0; i < size; i++)
        {
            MDIO_vSetPortVal(DIO_PORTA, Sevensegment[i]);
            _delay_ms(1000);
        }
    }

    return 0;
}

```

---

### **Lab 2:** Push Button Controlled 7-Segment Counter with Debouncing

Write an AVR C program to increment a Common Cathode 7-segment display  each time a push button on `PB0` (Active LOW with internal pull-up) is pressed. The code includes a **20 ms software debounce delay** and waits for button release before registering the next count.

**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

/* Common Cathode Values */
u8 Sevensegment[] =
{
    0b00111111,   // 0
    0b00000110,   // 1
    0b01011011,   // 2
    0b01001111,   // 3
    0b01100110,   // 4
    0b01101101,   // 5
    0b01111101,   // 6
    0b00000111,   // 7
    0b01111111,   // 8
    0b01101111    // 9
};

int main(void)
{
    u8 counter = 0;

    MDIO_vInit();

    /* Configure PORTA for 7-Segment */
    MDIO_vSetPortDir(DIO_PORTA, DIO_PORT_OUTPUT);

    /* Configure PB0 for Push Button Input */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN0, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_HIGH);   // Enable internal pull-up

    /* Display '0' initially */
    MDIO_vSetPortVal(DIO_PORTA, Sevensegment[counter]);

    while(1)
    {
        /* Check if Button is Pressed (Active LOW) */
        if(MDIO_u8GETPinVal(DIO_PORTB, DIO_PIN0) == DIO_LOW)
        {
            _delay_ms(20);   // Software Debounce Delay

            if(MDIO_u8GETPinVal(DIO_PORTB, DIO_PIN0) == DIO_LOW)
            {
                counter++;

                if(counter > 9)
                {
                    counter = 0;
                }

                MDIO_vSetPortVal(DIO_PORTA, Sevensegment[counter]);

                /* Wait until button is released */
                while(MDIO_u8GETPinVal(DIO_PORTB, DIO_PIN0) == DIO_LOW);
            }
        }
    }

    return 0;
}

```

```

```
