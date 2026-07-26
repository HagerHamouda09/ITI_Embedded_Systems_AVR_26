#  Session 10 Labs (AVR MCAL DIO Driver)

### **Lab 1:** Turn ON LED on Pin PA0
Write an AVR C program using layered MCAL architecture to configure Pin 0 on PORTA as an output pin and set its value to HIGH to turn on an LED.

**Code:**
```c
#include "../MCAL/DIO/DIO_int.h"

int main()
{
    // Initialize DIO peripheral hardware registers
    MDIO_vInit();

    // Configure PORTA Pin 0 as OUTPUT
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    // Set PORTA Pin 0 to HIGH to turn on the LED
    MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);

    while(1)
    {
        // Infinite Super Loop to keep the MCU active
    }

    return 0;
}

```

### **Lab 3:** DIP Switch Controlled Flashing LEDs (Pull-Up Configuration)
Write a code that uses a DIP switch to control a string of 8 LEDs. When the DIP switch is On the LED string shall be flashing every 500 ms. When the DIP switch off the LED string shall be also off.

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

int main(void)
{
    MDIO_vInit();

    // Configure PORTA (8 LEDs) as output
    MDIO_vSetPortDir(DIO_PORTA, DIO_PORT_OUTPUT);

    // Configure PB0 (DIP switch) as input
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN0, DIO_INPUT);

    // Enable the internal pull-up resistor on PB0
    MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_HIGH);

    while (1)
    {
        // If the switch is ON, PB0 is connected to GND (Active LOW)
        if (MDIO_u8GETPinVal(DIO_PORTB, DIO_PIN0) == DIO_LOW)
        {
            // Turn all LEDs ON
            MDIO_vSetPortVal(DIO_PORTA, 0xFF);
            _delay_ms(500);

            // Turn all LEDs OFF
            MDIO_vSetPortVal(DIO_PORTA, 0x00);
            _delay_ms(500);
        }
        else
        {
            // Switch is OFF -> Keep all LEDs OFF
            MDIO_vSetPortVal(DIO_PORTA, 0x00);
        }
    }

    return 0;
}

```
