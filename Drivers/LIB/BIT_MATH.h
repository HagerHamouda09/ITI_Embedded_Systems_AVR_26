#ifndef BIT_MATH_H
#define BIT_MATH_H

#define No_of_bits 8


#define SET_BIT(reg,bitN)       	((reg) |=  (1U << (bitN) ))

#define CLR_BIT(reg,bitN)       	((reg) &= (~(1U << (bitN) )))

#define TOG_BIT(reg,bitN)           ((reg) ^=  (1U << (bitN) ))

#define GET_BIT(reg,bitN)           (((reg) >> (bitN) ) & (1U))

#define SET_BYTE(reg,value)         ( (reg) = (value) )

#define ROT_LEFT(reg,bitN)          ((unsigned char)((reg<<bitN)|(reg>>(No_of_bits - bitN))))

#define ROT_RIGHT(reg,bitN)         ((unsigned char)((reg>>bitN)|(reg<<(No_of_bits - bitN))))

#endif

































