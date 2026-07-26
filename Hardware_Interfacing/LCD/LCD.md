# Session 11 Labs (AVR HAL LCD Driver)

### **Lab 1:** Display Single Character on LCD
Write your name on the LCD

**Code:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include <util/delay.h>

int main()
{
	HLCD_vInit();

   HLCD_vDisplayString("Hager");

	while(1)
	{

	}

	return 0;
}

```

---

### **Lab 2:** Moving Text Animation (Ping-Pong Scroll)

Write your name and make it move from right to left until it reaches the end of the display, then move it left to right. Keep the name moving forever
 
**Code:**

```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include <util/delay.h>

int main(void)
{
    // Initialize DIO and LCD drivers
    MDIO_vInit();
    HLCD_vInit();

    while(1)
    {
        /* Move Right -> Left */
        for(s8 col = 15; col >= 0; col--)
        {
            HLCD_vClearScreen();
            HLCD_vSetCursorPosition(0, col);
            HLCD_vDisplayString("Hager");
            _delay_ms(300);
        }

        /* Move Left -> Right */
        for(u8 col = 0; col <= 15; col++)
        {
            HLCD_vClearScreen();
            HLCD_vSetCursorPosition(0, col);
            HLCD_vDisplayString("Hager");
            _delay_ms(300);
        }
    }

    return 0;
}

```

```

```
