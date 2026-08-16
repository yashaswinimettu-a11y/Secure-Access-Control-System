/*---------------------------------------------------------
 * File Name    : i2c_eeprom.h
 * Description  : EEPROM Function Prototypes
 *---------------------------------------------------------*/

#ifndef _I2C_EEPROM_H_              // Start of conditional compilation
#define _I2C_EEPROM_H_              // Define header guard


#include "types.h"                  // User defined data types


void i2c_eeprom_write_byte          // Write single byte into EEPROM
(
        u8 SlaveAddr,
        u8 BuffAddr,
        u8 data
);

u8 i2c_eeprom_read_byte             // Read single byte from EEPROM
(
        u8 SlaveAddr,
        u8 BufferAddr
);

void i2c_eeprom_write_page          // Write multiple bytes into EEPROM
(
        u8 SlavAddr,
        u8 BuffAddr,
        s8 *P,
        u8 nbytes
);

void i2c_eeprom_seq_read            // Sequential EEPROM read
(
        u8 SlaveAddr,
        u8 BuffAdrr,
        s8 *p,
        u8 nbytes
);

#define USER_ID_ADDR 0x0000
#define USER_PASS_ADDR 0x0020
#define ENROLL_ID 0x0040

#endif                              // End of conditional compilation
