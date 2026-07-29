
### **Stepper Motor CW and CCW** 
```c

///*
// * STEPPER.c
// *
// *  Created on: Jul 27, 2026
// *      Author: Hager Adel
// */
//
//
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/STEPPER/STEPPER_int.h"
#include <util/delay.h>

int main()

{
	MDIO_vInit();
	HSTEPPER_vInit();

	while(1)
	{
		for(u8 i =0; i<128; i++)
		{
			HSTEPPER_vRotateCW(5);
		}
		_delay_ms(1000);

		HSTEPPER_vStop();
		_delay_ms(1000);

		for(u8 i =0; i<128; i++)
		{
			HSTEPPER_vRotateCCW(5);
		}
		_delay_ms(1000);

		HSTEPPER_vStop();
		_delay_ms(1000);

	}

	return 0;
}



```
