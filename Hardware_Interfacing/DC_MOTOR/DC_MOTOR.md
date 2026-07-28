# Session 13 Labs (DC Motor Control)

### **Lab 1:** DC Motor Driver Using NPN Transistor & Switch
Write an AVR C program to control a DC motor via an NPN Transistor (2N2222) switching circuit. 
A tactile switch connected to -> when the switch is unpressed, the motor runs; when pressed, the motor stops.

**Hardware Connections:**
* **MCU Pin `PA0`** $\rightarrow$ $1\text{ k}\Omega$ resistor $\rightarrow$ **Base (B)** of 2N2222 Transistor
* **Emitter (E)** $\rightarrow$ GND
* **Collector (C)** $\rightarrow$ Negative terminal of DC Motor
* **DC Motor Positive Terminal** $\rightarrow$ $+5\text{V}$
* **Tactile Switch (`PB0`)** $\rightarrow$ Terminal 1 $\rightarrow$ `PB0`, Terminal 2 $\rightarrow$ GND

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

int main(void)
{
    MDIO_vInit();

    /* Motor Control Pin (PA0) -> Output */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    /* Switch Pin (PB0) -> Input */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN0, DIO_INPUT);

    /* Enable Internal Pull-up Resistor on PB0 */
    MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_HIGH);

    while(1)
    {
        /* Switch is NOT pressed (PB0 reads HIGH) */
        if(MDIO_u8GETPinVal(DIO_PORTB, DIO_PIN0) == DIO_HIGH)
        {
            /* Motor ON */
            MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
        }
        else
        {
            /* Switch is pressed (PB0 reads LOW) -> Motor OFF */
            MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_LOW);
        }
    }

    return 0;
}

```


### Lab 2: Bidirectional DC Motor Control (H-Bridge Driver)

Write an AVR C program to control the directional rotation of a DC Motor using an H-Bridge driver connected to control pins PA0 and PA1.
The motor cycles continuously through Clockwise (CW) rotation, Counter-Clockwise (CCW) rotation, and Braking/Stopping states at 500 ms intervals.

Code:
```c

#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KPD/KPD_int.h"
#include <util/delay.h>

int main()
{
    /* Configure H-Bridge Direction Control Pins as Outputs */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);

    while(1)
    {
        /* Clockwise Rotation (CW) */
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN1, DIO_LOW);
        _delay_ms(500);

        /* Counter-Clockwise Rotation (CCW) */
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN1, DIO_HIGH);
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_LOW);
        _delay_ms(500);

        /* Stop / Active Brake */
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN1, DIO_HIGH);
        _delay_ms(500);
    }

    return 0;
}
```
