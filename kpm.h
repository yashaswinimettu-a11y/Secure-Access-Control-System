#ifndef __kpm_h__                    // Start of conditional compilation
#define __kpm_h__                    // Define header guard


#include "types.h"                  // User defined data types


// Row pin definitions
#define row0 16                      // Row 0 pin
#define row1 17                      // Row 1 pin
#define row2 18                      // Row 2 pin
#define row3 19                      // Row 3 pin


// Column pin definitions
#define col0 20                      // Column 0 pin
#define col1 21                      // Column 1 pin
#define col2 22                      // Column 2 pin
#define col3 23                      // Column 3 pin


// Function declarations
void init_kpm(void);                 // Initialize keypad

u32 colscan(void);                   // Scan keypad columns

s32 keyscan(void);                   // Scan and return pressed key

u32 rowcheck(void);                  // Detect active row

u32 colcheck(void);                  // Detect active column

s32 readnum(void);                   // Read numeric input

s8 id_kpm(s8 *ptr);                // Read ID from keypad
		   s8 id_kpm1(s8 *ptr); 
void password_kpm(char *ptr);          // Read password from keypad

#endif                               // End of conditional compilation
