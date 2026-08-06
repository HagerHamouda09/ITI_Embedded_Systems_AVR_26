#  Session 20 Labs (Watchdog Timer - WDT)

### **Lab 1:** Watchdog Timer Reset Verification (Blinking LED Cycle)
Write an AVR C program to demonstrate the functionality of the **Watchdog Timer (WDT)**. 

<img width="956" height="469" alt="image" src="https://github.com/user-attachments/assets/38af608e-85ad-44c7-aca4-5461eeeeb3c4" />

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/WDT/WDT_int.h"

#include <util/delay.h>

int main(void)
{
    MDIO_vInit();
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    /* 1. LED ON for 500 ms upon startup/reset */
    MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
    _delay_ms(500);

    /* 2. Turn LED OFF */
    MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_LOW);

    /* 3. Configure prescaler (2.1s) & Enable Watchdog Timer */
    TIMER_voidWDTSleep(); // Configures 2.1s timeout prescaler from WDT_cfg.h
    MWDT_vEnable();       // Turns WDT ON

    /* 4. Trapped in empty loop without WDT refresh -> Microcontroller resets after 2.1s */
    while (1)
    {

    }

    return 0;
}

```

