#  Session 20 Labs (Serial Peripheral Interface - SPI Loopback Test)

### **Lab 1:** SPI Full-Duplex Loopback Verification Test
Write an AVR C program to verify SPI transceiver functionality using a hardware loopback test. The microcontroller acts as an SPI Master,
sending a character (`'R'`) over the **MOSI** line while simultaneously receiving the incoming byte on the **MISO** line.

---

### **Hardware Connection & Testing Instructions:**
1. **Upload the Code:** Flash the compiled code onto the ATmega32 microcontroller first.
2. **Connect Loopback Jumper:** Wire the **MOSI** pin (`PB5`) directly to the **MISO** pin (`PB6`).
3. **Reset Microcontroller:** Press the hardware **RESET** button on the kit to execute the code with the loopback connection active.
4. **Verification:** If the transceived byte (`c`) matches `'R'`, Pin `PA0` (Status LED) goes `HIGH` (turns ON).

---

### **C Implementation Code:**

```c
/*
 * SPI.c
 *
 *  Created on: Aug 6, 2026
 *      Author: Hager Adel
 */

#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/SPI/SPI_int.h"
#include <util/delay.h>

int main()
{
    u8 c = 0;

    /* Initialize DIO Driver & Configure PA0 as Output for Status LED */
    MDIO_vInit();
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
    MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_LOW);

    /* Initialize SPI Master Peripheral Driver */
    MSPI_vInit();

    /* Transceive byte ('R') over SPI Loopback (MOSI connected to MISO) */
    c = MSPI_vTransceive('R');

    /* Verify if received character matches sent character */
    if (c == 'R')
    {
        /* Loopback Success: Turn Status LED ON */
        MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
    }

    while(1)
    {
        // Infinite Super Loop
    }

    return 0;
}
