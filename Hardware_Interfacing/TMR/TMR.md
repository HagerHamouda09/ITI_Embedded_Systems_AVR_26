# Session 17 Labs (Timers - Timer0 Overflow Interrupt)

### **TIMER CALCULATIONS**

<img width="1000" height="503" alt="image" src="https://github.com/user-attachments/assets/411830d9-4549-4e4f-b169-eb72cb2bbb05" />



### **Lab 1:**  LED Toggle Using Timer0 Overflow (OVF) Interrupt

<img width="962" height="165" alt="image" src="https://github.com/user-attachments/assets/2f52b68b-8f29-42b2-b50f-2750963fe90d" />


**Calculations Breakdown:**
* **System Frequency ($F_{\text{CPU}}$):** $8\text{ MHz}$
* **Prescaler:** $8 \implies \text{Timer Frequency} = \frac{8\text{ MHz}}{8} = 1\text{ MHz}$ ($\text{Tick Time} = 1\ \mu\text{s}$)
* **Timer Resolution (8-bit):** $2^8 = 256\text{ ticks per overflow} \implies \text{Overflow Time} = 256\ \mu\text{s}$
* **Required Delay:** $1\text{ second} = 1,000,000\ \mu\text{s}$
* **Number of Overflows:** $\frac{1,000,000}{256} = 3906.25\text{ overflows}$
* **Preload Value:** $256 * (1 - 0.25) = 192$
* **Adjusted Overflows:** $3907\text{ counts}$

**Code:**
```c
/*
 * main.c
 *
 *  Created on: Aug 2, 2026
 *      Author: Hager Adel
 */

#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TMR/TMR_int.h"

void LED_Toggle(void);

int main(void)
{
    /* Initialize DIO Driver */
    MDIO_vInit();

    /* Configure PA0 as Output for LED */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

    /* Enable Global Interrupts */
    MGIE_vEnableGlobalInterrupt();

    /* Initialize Timer0 Hardware */
    MTIMERS_vInit();

    /* Set Preload Value = 192 for initial overflow alignment */
    MTIMERS_vSetPreloadValue(TIM_0, 192);

    /* Set Callback function and total overflow count (3907) for 1s interval */
    MTIMERS_vSetInterval_OVF(LED_Toggle, 3907);

    /* Start Timer0 with prescaler */
    MTIMERS_vStartTimer(TIM_0);

    while(1)
    {
        // Super Loop
    }

    return 0;
}

void LED_Toggle(void)
{
    /* Toggle LED on Pin PA0 */
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}
