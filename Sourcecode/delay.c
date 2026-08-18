#include "types.h"

/*---------------------------------------------------------
 * Function Name : delay_us
 * Description   : Generates approximate delay in microseconds
 * Argument      : us -> delay time in microseconds
 * Return Type   : void
 *---------------------------------------------------------*/
void delay_us(u32 us)
{
        /* 
         * Loop count adjusted for processor speed
         * to generate 1 microsecond delay
         */
        for(us *= 12; us > 0; us--);
}


/*---------------------------------------------------------
 * Function Name : delay_ms
 * Description   : Generates approximate delay in milliseconds
 * Argument      : ms -> delay time in milliseconds
 * Return Type   : void
 *---------------------------------------------------------*/
void delay_ms(u32 ms)
{
        /*
         * Loop count adjusted for processor speed
         * to generate 1 millisecond delay
         */
        for(ms *= 12000; ms > 0; ms--);
}


/*---------------------------------------------------------
 * Function Name : delay_s
 * Description   : Generates approximate delay in seconds
 * Argument      : s -> delay time in seconds
 * Return Type   : void
 *---------------------------------------------------------*/
void delay_s(u32 s)
{
        /*
         * Loop count adjusted for processor speed
         * to generate 1 second delay
         */
        for(s *= 12000000; s > 0; s--);
}
