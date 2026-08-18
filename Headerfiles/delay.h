/*---------------------------------------------------------
 * File Name    : delay.h
 * Description  : Delay Function Prototypes
 *                 -> Microsecond delay
 *                 -> Millisecond delay
 *                 -> Second delay
 *---------------------------------------------------------*/

#ifndef _DELAY_H_                // Start of conditional compilation
#define _DELAY_H_                // Define header guard


#include "types.h"               // User defined data types


/*---------------------------------------------------------
 * Function Name : delay_us
 * Description   : Generates microsecond delay
 * Return Type   : void
 *---------------------------------------------------------*/

void delay_us(u32);


/*---------------------------------------------------------
 * Function Name : delay_ms
 * Description   : Generates millisecond delay
 * Return Type   : void
 *---------------------------------------------------------*/

void delay_ms(u32);


/*---------------------------------------------------------
 * Function Name : delay_s
 * Description   : Generates second delay
 * Return Type   : void
 *---------------------------------------------------------*/

void delay_s(u32);


#endif                          // End of conditional compilation
