/*---------------------------------------------------------
 * File Name    : l293d.h
 * Description  : L293D Motor Driver Definitions and
 *                 Function Prototypes
 *---------------------------------------------------------*/

#ifndef __l293d                     // Start of conditional compilation
#define __l293d                     // Define header guard


#define M1 5                        // Motor control pin M1

#define M2 6                        // Motor control pin M2


void init_l293d(void);              // Initialize motor driver

void door_open(void);               // Open door using motor

void door_close(void);              // Close door using motor

void motor_stop(void);              // Stop motor rotation


#endif                              // End of conditional compilation
