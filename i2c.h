/*---------------------------------------------------------
 * File Name    : i2c.h
 * Description  : I2C Function Prototypes
 *---------------------------------------------------------*/

#ifndef _I2C_H_                      // Start of conditional compilation
#define _I2C_H_                      // Define header guard


#include "types.h"                  // User defined data types


void init_i2c(void);                // Initialize I2C peripheral

void i2c_start(void);               // Generate I2C start condition

void i2c_stop(void);                // Generate I2C stop condition

void i2c_restart(void);             // Generate I2C repeated start

void i2c_write(u8 sdat);            // Write data byte on I2C bus

u8 i2c_mack(void);                  // Read byte with ACK

u8 i2c_nack(void);                  // Read byte with NACK


#endif                              // End of conditional compilation
