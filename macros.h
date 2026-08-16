/*---------------------------------------------------------
 * File Name    : macros.h
 * Description  : Bit, Byte and Nibble Manipulation Macros
 *---------------------------------------------------------*/

#ifndef _MACROS_H_                   // Start of conditional compilation
#define _MACROS_H_                   // Define header guard


// BIT manipulation macros
#define SETBIT(WORD,POS) (WORD |= 1<<POS)           // Set specific bit

#define CLRBIT(WORD,POS) (WORD &= ~(1<<POS))        // Clear specific bit

#define G_SETBIT(WORD,POS) (WORD = 1<<POS)          // Assign single bit

#define RBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)        // Read specific bit


// BYTE manipulation macros
#define WBYTE(WORD,POS,DATA) \
(WORD = (WORD&~(255<<POS))|(DATA<<POS))             // Write byte data


// NIBBLE manipulation macros
#define WNIBBLE(WORD,POS,DATA) \
(WORD =(WORD&~(15<<POS))|(DATA<<POS))               // Write nibble data

#define RNIBBLE(WORD,POS) ((WORD>>POS)&15)          // Read nibble data


#endif                                               // End of conditional compilation
