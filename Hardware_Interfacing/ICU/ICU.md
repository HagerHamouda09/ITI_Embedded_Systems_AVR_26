#  Session 20 Labs (Hardware Input Capture Unit - Hardware ICU)

### **Lab 1:** Frequency & Duty Cycle Measurement Using Hardware ICU (Timer1 ICP1 Pin)

Implement a system that takes an input PWM and display its frequency and duty cycle on a character LCD.

<img width="331" height="146" alt="image" src="https://github.com/user-attachments/assets/a6a11d67-613c-4417-97f0-25504a6738d3" />

**System Operations:**
1. **PWM Generation:** Timer0 operates in **Fast PWM Mode** on `PB3` (`OC0`) generating a test PWM signal ($OCR_0 = 127 \implies \approx 50\%$ Duty Cycle).
2. **Hardware Measurement:** Timer1 hardware ICU captures the timestamp values on `PD6` across 3 edge states:
   * **State 0 $\rightarrow$ State 1:** Captures 1st Rising Edge ($T_1$) and switches trigger sensitivity to **Falling Edge**.
   * **State 1 $\rightarrow$ State 2:** Captures 1st Falling Edge ($T_2$) to calculate High Time ($T_{\text{ON}} = T_2 - T_1$) and switches trigger sensitivity to **Rising Edge**.
   * **State 2 $\rightarrow$ State 3:** Captures 2nd Rising Edge ($T_3$) to calculate Total Period ($T_{\text{total}} = T_3 - T_1$), then disables ICU interrupts to prevent frame corruption during processing.
3. **Display Output:** Computes frequency ($f = \frac{10^6}{T_{\text{total}}}$) and duty cycle ($D\% = \frac{T_{\text{ON}} \times 100}{T_{\text{total}}}$), renders them on a 16x2 LCD screen, and re-enables ICU captures after a 300 ms sampling delay.

**Configuration:**
```c
#define TIMER0_MODE                FAST_PWM
#define TIMER1_MODE                ICU

#define CLK_SELECT_PRESCALER_TIM0  CLK_8
#define CLK_SELECT_PRESCALER_TIM1  CLK_8

#define PWM_OUTPUT_MODE            NON_INVERTING

```

**Code:**

```c

#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TMR/TMR_int.h"
#include "../HAL/LCD/LCD_int.h"

#include <util/delay.h>

/* Capture Variables */
volatile u16 G_T1 = 0;
volatile u16 G_T2 = 0;
volatile u16 G_T3 = 0;

volatile u8 G_State = 0;

/*=========================================================
 * Hardware ICU Callback Function
 *=========================================================*/
void ICU_Callback(void)
{
    if (G_State == 0)
    {
        /* First Rising Edge */
        G_T1 = MTIMERS_u16GetCapturedValue();

        /* Switch hardware trigger to Falling Edge */
        MTIMERS_SetTrigger(TRIG_TYPE_FALLING);

        G_State = 1;
    }
    else if (G_State == 1)
    {
        /* First Falling Edge */
        G_T2 = MTIMERS_u16GetCapturedValue();

        /* Switch hardware trigger back to Rising Edge */
        MTIMERS_SetTrigger(TRIG_TYPE_RISING);

        G_State = 2;
    }
    else if (G_State == 2)
    {
        /* Second Rising Edge */
        G_T3 = MTIMERS_u16GetCapturedValue();

        /*
         * Disable ICU interrupt temporarily to guarantee that one complete 
         * PWM measurement cycle is processed before new captures occur.
         */
        MTIMERS_vDisableInterrupt(TIM_1, ICU);

        G_State = 3;
    }
}

/*=========================================================
 * Main Application
 *=========================================================*/
int main(void)
{
    MDIO_vInit();

    /* Set PB3 (OC0 - Timer0 Fast PWM Output) as Output */
    MDIO_vSetPinDir(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);

    /* Set PD6 (ICP1 - Timer1 Hardware ICU Input) as Input */
    MDIO_vSetPinDir(DIO_PORTD, DIO_PIN6, DIO_INPUT);

    HLCD_vInit();
    MTIMERS_vInit();

    /* Register Hardware ICU callback */
    MTIMERS_vSetICU_CB(ICU_Callback);

    /* Configure initial capture edge sensitivity to Rising Edge */
    MTIMERS_SetTrigger(TRIG_TYPE_RISING);

    /* Generate PWM signal (~50% Duty Cycle) */
    MTIMERS_vSetCompareMatch(TIM_0, 127);

    /* Enable Global Interrupts */
    MGIE_vEnableGlobalInterrupt();

    /* Start Timers */
    MTIMERS_vStartTimer(TIM_0);
    MTIMERS_vStartTimer(TIM_1);

    while (1)
    {
        if (G_State == 3)
        {
            u16 Ton;
            u16 Ttotal;

            u32 Frequency = 0;
            u8 Duty = 0;

            /* Compute active ON-time and total signal period */
            Ton = G_T2 - G_T1;
            Ttotal = G_T3 - G_T1;

            if (Ttotal != 0)
            {
                /* Prescaler 8 @ F_CPU 8MHz -> 1 Tick = 1 µs */
                Frequency = 1000000UL / Ttotal;

                Duty = (u8)(((u32)Ton * 100UL) / Ttotal);
            }

            /* Display Results on LCD */
            HLCD_vClearScreen();

            HLCD_vSetCursorPosition(0, 0);
            HLCD_vDisplayString("F:");
            HLCD_vPrintNumber(Frequency);
            HLCD_vDisplayString("Hz");

            HLCD_vSetCursorPosition(1, 0);
            HLCD_vDisplayString("D:");
            HLCD_vPrintNumber(Duty);
            HLCD_vDisplayString("%");

            _delay_ms(300);

            /* 
             * Reset state machine and re-enable trigger & interrupt 
             * to allow continuous PWM signal monitoring.
             */
            G_State = 0;

            MTIMERS_SetTrigger(TRIG_TYPE_RISING);

            MTIMERS_vEnableInterrupt(TIM_1, ICU);
        }
    }

    return 0;
}

```
