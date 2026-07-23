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
