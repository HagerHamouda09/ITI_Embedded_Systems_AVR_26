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

```

#  Session 18 Labs (Timer0 CTC Mode & Fast PWM)

### **Lab 1:** Variable Frequency Tone Generator (CTC Mode)

<img width="934" height="488" alt="image" src="https://github.com/user-attachments/assets/7e8c25b1-7296-4d2a-8ec7-a429173aac05" />

**Configuration:**
```c
#define TIMER0_MODE                CTC
#define CLK_SELECT_PRESCALER_TIM0  CLK_8

```

**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TMR/TMR_int.h"
#include "../MCAL/ADC/ADC_int.h"

void Buzzer_Toggle(void);

int main(void)
{
    u16 ADC_Value;
    u8 OCR_Value;

    /* Initialize DIO Driver */
    MDIO_vInit();

    /* Configure PA1 as Output for Buzzer */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);

    /* Enable Global Interrupts & Peripheral Drivers */
    MGIE_vEnableGlobalInterrupt();
    MADC_vInit();
    MTIMERS_vInit();

    /* Initial Compare Match value = 100 (~101 µs interrupt interval) */
    MTIMERS_vSetCompareMatch(TIM_0, 100);

    /* Set Callback for Compare Match interrupt */
    MTIMERS_vSetInterval_CTC(Buzzer_Toggle, 1);

    /* Start Timer0 */
    MTIMERS_vStartTimer(TIM_0);

    while(1)
    {
        /* Read Analog Input on ADC Channel 0 */
        ADC_Value = MADC_u16AnalogRead(CHANNEL_0);

        /* Map 10-bit ADC (0-1023) to OCR Range (20-250) */
        OCR_Value = 20 + ((u32)ADC_Value * 230) / 1023;

        /* Update Compare Match Register dynamically */
        MTIMERS_vSetCompareMatch(TIM_0, OCR_Value);
    }

    return 0;
}

void Buzzer_Toggle(void)
{
    MDIO_vTogPinVal(DIO_PORTA, DIO_PIN1);
}

```
---

### **Lab 2:** Potentiometer Controlled LED Dimmer (ADC + Fast PWM)

<img width="860" height="449" alt="image" src="https://github.com/user-attachments/assets/1578f78d-bbd8-4267-94fa-3d6b83e8f32a" />

**Configuration:**
```c
#define TIMER0_MODE                FAST_PWM
#define CLK_SELECT_PRESCALER_TIM0  CLK_8

```

**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../MCAL/TMR/TMR_int.h"

int main(void)
{
    u16 ADC_Value;

    /* Potentiometer Pin (PA0) -> Input */
    MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_INPUT);

    /* PWM Output Pin OC0 (PB3) -> Output */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);

    /* Initialize Drivers */
    MADC_vInit();
    MTIMERS_vInit();

    /* Start Timer0 */
    MTIMERS_vStartTimer(TIM_0);

    while(1)
    {
        /* Read Potentiometer on Channel 0 */
        ADC_Value = MADC_u16AnalogRead(CHANNEL_0);

        /* Convert 10-bit ADC (0-1023) to 8-bit PWM (0-255) */
        MTIMERS_vSetCompareMatch(TIM_0, ADC_Value / 4);
    }

    return 0;
}

```

