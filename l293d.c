/*---------------------------------------------------------
 * File Name    : l293d.c
 * Description  : L293D Motor Driver Functions
 *                 -> Motor initialization
 *                 -> Door open control
 *                 -> Door close control
 *                 -> Motor stop control
 *---------------------------------------------------------*/

#include <lpc21xx.h>
#include "macros.h"
#include "l293d.h"


/*---------------------------------------------------------
 * Function Name : init_l293d
 * Description   : Initializes L293D motor driver
 *                 -> Configures motor control pins
 *                    as output pins
 * Return Type   : void
 *---------------------------------------------------------*/

void init_l293d(void)
{
        // Configure motor pins as output
        IODIR0 |= ((1<<M1) | (1<<M2));
}


/*---------------------------------------------------------
 * Function Name : door_open
 * Description   : Rotates motor in forward direction
 *                 -> Opens the door
 * Return Type   : void
 *---------------------------------------------------------*/

void door_open(void)
{
         // Set M1 high
         G_SETBIT(IOSET0,M1);

         // Set M2 low
         G_SETBIT(IOCLR0,M2);
}


/*---------------------------------------------------------
 * Function Name : door_close
 * Description   : Rotates motor in reverse direction
 *                 -> Closes the door
 * Return Type   : void
 *---------------------------------------------------------*/

void door_close(void)
{
         // Set M1 low
         G_SETBIT(IOCLR0,M1);

         // Set M2 high
         G_SETBIT(IOSET0,M2);
}


/*---------------------------------------------------------
 * Function Name : motor_stop
 * Description   : Stops motor rotation
 *                 -> Clears both motor control pins
 * Return Type   : void
 *---------------------------------------------------------*/

void motor_stop(void)
{
         // Clear M1 pin
         G_SETBIT(IOCLR0,M1);

         // Clear M2 pin
         G_SETBIT(IOCLR0,M2);
}
