# Session 22 Labs (USART / UART Communication)

### **Lab 1:** Periodic Character Transmission via USART
Write an AVR C program to continuously transmit character sequence signals (`'A'`, `'B'`, `'C'`) over the serial TX line with a **500 ms delay** between transmissions.

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TMR/TMR_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/WDT/WDT_int.h"
#include "../MCAL/USART/USART_int.h"
#include <util/delay.h>

int main()
{
    /* Initialize USART Peripheral Driver */
    MUSART_vInit();

    while(1)
    {
        /* Transmit 'A' */
        MUSART_vTransmit('A');
        _delay_ms(500);

        /* Transmit 'B' */
        MUSART_vTransmit('B');
        _delay_ms(500);

        /* Transmit 'C' */
        MUSART_vTransmit('C');
        _delay_ms(500);
    }

    return 0;
}

```

---

### **Lab 2:** Terminal LED Control with Echo Feedback

Write an AVR C program to interface the microcontroller with a terminal application (PuTTY) over USART.

<img width="1147" height="227" alt="image" src="https://github.com/user-attachments/assets/8c6cd387-ca18-4655-a066-19f43fabe5c9" />


**Code:**

```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/USART/USART_int.h"

int main(void)
{
    u8 L_u8ReceivedChar = 0;

    /* 1. Configure entire PORTA as Output for LEDs */
    MDIO_vSetPortDir(DIO_PORTA, DIO_PORT_OUTPUT);

    /* Turn off all LEDs initially */
    MDIO_vSetPortVal(DIO_PORTA, DIO_LOW);

    /* 2. Initialize USART driver */
    MUSART_vInit();

    while (1)
    {
        /* 3. Blocking wait until a character is received from Terminal */
        L_u8ReceivedChar = MUSART_vReceive();

        /* 4. Match ASCII commands ('1', '2') to toggle LED pins */
        switch (L_u8ReceivedChar)
        {
            case '1':
                MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
                MUSART_vTransmit('1'); // Echo '1' back to terminal
                break;

            case '2':
                MDIO_vTogPinVal(DIO_PORTA, DIO_PIN1);
                MUSART_vTransmit('2'); // Echo '2' back to terminal
                break;

            default:
                /* Ignore unmapped key presses */
                break;
        }
    }

    return 0;
}

```
