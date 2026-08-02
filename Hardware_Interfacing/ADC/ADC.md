# Session 16 Labs (Analog-to-Digital Converter - ADC)

### **Lab:** LM35 Temperature Sensor & Alarm System

Write an AVR C program to interface an **LM35 Temperature Sensor** connected to `ADC0`. Convert sensor voltage output ($10\text{ mV} / ^\circ\text{C}$) into temperature in Celsius, driving a safety status panel:

* $T < 20^\circ\text{C}$ $\rightarrow$ **Green LED (`PB0`) ON**
* $20^\circ\text{C} \le T < 40^\circ\text{C}$ $\rightarrow$ **Yellow LED (`PB1`) ON**
* $T \ge 40^\circ\text{C}$ $\rightarrow$ **Red LED (`PB2`)**

<img width="768" height="493" alt="Screenshot (252)" src="https://github.com/user-attachments/assets/30c186e5-686f-43c7-8f44-b4bbac18f650" />

**Code:**

```c
#define F_CPU 8000000UL

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"

int main(void)
{
    u16 L_u16ADCValue;

    /* Initialize drivers */
    MDIO_vInit();
    MADC_vInit();

    /* LEDs and buzzer output */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN0, DIO_OUTPUT); // Green
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN1, DIO_OUTPUT); // Yellow
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN2, DIO_OUTPUT); // Red

    while(1)
    {
        /* Read LM35 on ADC0 */
        L_u16ADCValue = MADC_u16AnalogRead(0);

        /* Convert ADC value to mV */
        L_u16ADCValue = (L_u16ADCValue * 5000UL) / 1023;

        /* Convert mV to Celsius */
        L_u16ADCValue = L_u16ADCValue / 10;

        if(L_u16ADCValue < 20)
        {
            /* Green ON */
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN1, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN2, DIO_LOW);
        }
        else if(L_u16ADCValue < 40)
        {
            /* Yellow ON */
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN1, DIO_HIGH);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN2, DIO_LOW);
        }
        else
        {
            /* Dangerous temperature: Red  */
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN1, DIO_LOW);
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN2, DIO_HIGH);
        }

        _delay_ms(500);
    }

    return 0;
}

```

---

### **Lab :** LDR Automatic Light System

<img width="860" height="508" alt="Screenshot (256)" src="https://github.com/user-attachments/assets/943591f0-6bee-4c83-abbe-3def359f9ed4" />

Write an AVR C program using a Light Dependent Resistor (LDR) connected to `ADC0` to automatically turn on an active-low light/LED on `PB0` during dark conditions and turn it off when ambient light is sufficient.

**Code:**

```c
#define F_CPU 8000000UL

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"

int main(void)
{
    u16 L_u16ADCValue;

    /* Initialize drivers */
    MDIO_vInit();
    MADC_vInit();

    /* LED output */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN0, DIO_OUTPUT);

    while(1)
    {
        /* Read LDR from ADC0 */
        L_u16ADCValue = MADC_u16AnalogRead(0);

        /* Dark condition (ADC value is low) */
        if(L_u16ADCValue < 500)
        {
            /* Turn LED ON */
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_HIGH);
        }
        /* Bright condition */
        else
        {
            /* Turn LED OFF */
            MDIO_vSetPinVal(DIO_PORTB, DIO_PIN0, DIO_LOW);
        }

        _delay_ms(200);
    }

    return 0;
}

```
