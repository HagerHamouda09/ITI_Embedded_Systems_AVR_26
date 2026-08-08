#  Session 21 Labs (I²C / TWI & External EEPROM Interfacing)

### **Lab 1:** External EEPROM Byte Read/Write Verification over I²C (TWI)
Write an AVR C program to interface with an external I²C EEPROM chip ( AT24C08) using the TWI MCAL driver. 

**Driver Functions & Main Implementation:**
```c
#define F_CPU 8000000UL

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TWI/TWI_int.h"
#include <util/delay.h>

/* Function Declarations */
void HEEPROM_vWriteByte(u8 A_u8Byte, u8 A_u8SlaAdd, u16 A_u16WordAdd);
u8 HEEPROM_u8ReadByte(u8 A_u8SlaAdd, u16 A_u16WordAdd);

/*=========================================================
 * Write Byte to External EEPROM
 *=========================================================*/
void HEEPROM_vWriteByte(u8 A_u8Byte, u8 A_u8SlaAdd, u16 A_u16WordAdd)
{
    /* 1. Generate START condition */
    MTWI_u8SendStartCondition();

    /* 2. Send Slave Address with Write Bit (SLA+W) */
    MTWI_u8SendSLA_RW(A_u8SlaAdd, TWI_WRITE);

    /* 3. Send Target Internal Memory Word Address */
    MTWI_u8SendByte((u8)A_u16WordAdd);

    /* 4. Send Data Byte to write */
    MTWI_u8SendByte(A_u8Byte);

    /* 5. Generate STOP condition */
    MTWI_u8SentStopCondition();
}

/*=========================================================
 * Read Byte from External EEPROM (Random Read via Repeated Start)
 *=========================================================*/
u8 HEEPROM_u8ReadByte(u8 A_u8SlaAdd, u16 A_u16WordAdd)
{
    u8 L_u8Data = 0;

    /* 1. Generate START condition */
    MTWI_u8SendStartCondition();

    /* 2. Send Slave Address with Write Bit  */
    MTWI_u8SendSLA_RW(A_u8SlaAdd, TWI_WRITE);

    /* 3. Send Target Internal Memory Word Address */
    MTWI_u8SendByte((u8)A_u16WordAdd);

    /* 4. Resend Repeated START condition to switch bus direction to READ */
    MTWI_u8ResendStartCondition();

    /* 5. Send Slave Address with Read Bit (SLA+R) */
    MTWI_u8SendSLA_RW(A_u8SlaAdd, TWI_READ);

    /* 6. Receive Data Byte and respond with NACK (Single-byte read termination) */
    MTWI_u8ReceiveByte(&L_u8Data, TWI_NOT_ACK);

    /* 7. Generate STOP condition */
    MTWI_u8SentStopCondition();

    return L_u8Data;
}

/*=========================================================
 * Main Application
 *=========================================================*/
//
//Initialize the required LED pin(s).
//
//Initialize TWI.
//
//Write a known byte to EEPROM memory location 5 using slave address.
//
//Wait for the EEPROM write cycle to complete.
//
//Read the byte back from the same memory location.
//
//Compare the received byte with the transmitted byte.
//
//Turn the LED ON if they match; otherwise, turn the LED OFF.
//



```
