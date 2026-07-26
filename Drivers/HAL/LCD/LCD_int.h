
/*
 * LCD_int.h
 *
 *  Created on: Jul 24, 2026
 *      Author: Hager Adel
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_



#define DDRAM_BASE_ADDR_R0  0x80
#define DDRAM_BASE_ADDR_R1  0xC0


#define CGRAM_BASE_ADDR      0x40





void HLCD_vInit(void);
void HLCD_vSendCmd(u8 A_u8cmd);

void HLCD_vSendChar(u8 A_u8Char);
void HLCD_vDisplayString(const u8 A_u8Str[]);

void HLCD_vPrintNumber(u32 A_u32Number);

void HLCD_vSetCursorPosition(u8 A_u8Row, u8 A_u8Col);

void HLCD_vClearScreen(void);

void HLCD_vWriteCGRAM(u8 A_u8PatternIdx, u8* A_u8PatternValue);

void HLCD_vDisplayCGRAM(u8 A_u8PatternIdx, u8 A_u8Row, u8 A_u8Col);


#endif /* HAL_LCD_LCD_INT_H_ */
