#  Session 15 Labs (External Interrupts - EXTI)

### **Lab 1:** Hardware ISR & EXTI Callback Mechanism
Write an AVR C program using the EXTI MCAL driver to toggle an LED on `PA0` when an external interrupt is triggered on `PD2` (INT0). 

//Make sure to comment the ISR Vectors from EXTI_prg.c

**Implementation 1 (Direct ISR in main):**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include <util/delay.h>

#include <avr/interrupt.h>

// Hardware Interrupt Service Routine
ISR(INT0_vect)
{
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

int main()
{
    // INT0 Pin (PD2) -> Input with active Pull-Up
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

    // LED Pin (PA0) -> Output
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    MEXTI_vInit();
    MGIE_vEnableGlobalInterrupt();

    while(1)
    {

    }

    return 0;
}

```

**Implementation 2 (Callback Mechanism):**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include <util/delay.h>

void Toggel_func(void)
{
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

int main()
{
    // LED Pin -> Output
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    // Switch Pin (PD2) -> Input with Pull-Up
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

    MEXTI_vInit();
    MGIE_vEnableGlobalInterrupt();

    // Pass callback function to EXTI driver (0 = INT0)
    MEXTI_vCallBackFunction(Toggel_func, 0);

    while(1)
    {

    }

    return 0;
}

```

---

### **Lab 2:** Dual External Interrupts (INT0 & INT1)

<img width="941" height="203" alt="image" src="https://github.com/user-attachments/assets/0c399cd5-e01f-4111-9a56-d5de548dc5ff" />


Write an AVR C program configuring two independent external interrupts:

* `INT0` (`PD2`): Toggles `PA0` (LED0)
* `INT1` (`PD3`): Toggles `PA1` (LED1)

*Configuration:*

```c
#define EXTI_INT0             ENABLE
#define EXTI_INT1             ENABLE
#define EXTI_INT2             DISABLE

#define EXTI_INT0_SENSE_CTRL  EXTI_ONCHANGE
#define EXTI_INT1_SENSE_CTRL  EXTI_ONCHANGE
#define EXTI_INT2_SENSE_CTRL  EXTI_FALLING

```

**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include <util/delay.h>

void LED0_Toggle(void);
void LED1_Toggle(void);

int main(void)
{
    /* INT0 Pin (PD2) */
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

    /* INT1 Pin (PD3) */
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN3, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTD, DIO_PIN3, DIO_HIGH);

    /* LED Outputs */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);

    /* Initialize External Interrupts */
    MEXTI_vInit();

    /* Register Callbacks */
    MEXTI_vCallBackFunction(LED0_Toggle, EXTI_INT0_ID);
    MEXTI_vCallBackFunction(LED1_Toggle, EXTI_INT1_ID);

    /* Enable Global Interrupt */
    MGIE_vEnableGlobalInterrupt();

    while(1)
    {

    }

    return 0;
}

void LED0_Toggle(void)
{
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

void LED1_Toggle(void)
{
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN1);
}

```

---

### **Lab 3:** Interrupt-Driven LED Animation Mode Switcher

<img width="932" height="206" alt="image" src="https://github.com/user-attachments/assets/7ac51cb6-0c32-4060-b09b-a90d7254c0c7" />


Write an AVR C program where pressing a push button connected to `INT0` (`PD2`) cycles through 3 different LED pattern modes on `PORTA`.

Modes:
0. Left to Right sequence
1. Right to Left sequence
2. All LEDs Blinking

**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include <util/delay.h>

volatile u8 G_u8AnimationMode = 0;

void ChangeAnimation(void)
{
    G_u8AnimationMode++;

    if(G_u8AnimationMode == 3)
    {
        G_u8AnimationMode = 0;
    }
}

int main(void)
{
    u8 i;

    /* LEDs on PORTA */
    MDIO_vSetPortDir(DIO_PORTA, DIO_PORT_OUTPUT);

    /* INT0 Pin (PD2) */
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
    MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

    MEXTI_vInit();
    MEXTI_vCallBackFunction(ChangeAnimation, EXTI_INT0_ID);
    MGIE_vEnableGlobalInterrupt();

    while(1)
    {
        switch(G_u8AnimationMode)
        {
            case 0:
                /* Left to Right */
                for(i = 0; i < 8; i++)
                {
                    MDIO_vSetPinVal(DIO_PORTA, i, DIO_HIGH);
                    _delay_ms(150);
                }
                break;

            case 1:
                /* Right to Left */
                for(i = 7; i > 0; i--)
                {
                    MDIO_vSetPinVal(DIO_PORTA, i, DIO_HIGH);
                    _delay_ms(150);
                }
                break;

            case 2:
                /* Blink All LEDs */
                MDIO_vSetPortVal(DIO_PORTA, 0xFF);
                _delay_ms(300);

                MDIO_vSetPortVal(DIO_PORTA, 0x00);
                _delay_ms(300);
                break;
        }
    }

    return 0;
}

```

---

