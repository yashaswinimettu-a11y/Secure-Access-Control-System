/*---------------------------------------------------------
 * File Name    : i2c_defines.h
 * Description  : I2C Macro Definitions
 *---------------------------------------------------------*/

#ifndef _I2C_DEFINES_H_              // Start of conditional compilation
#define _I2C_DEFINES_H_              // Define header guard


// I2C pin definitions
#define SCL 2                         // Serial clock pin
#define SDA 3                         // Serial data pin


// PINSEL0 values for I2C pin function selection
#define SCL_PIN_FUNC 0X00000010      // Enable SCL function
#define SDA_PIN_FUNC 0X00000040      // Enable SDA function


// Clock configuration values
#define FOSC       12000000          // Oscillator frequency

#define CCLK      (FOSC*5)           // CPU clock frequency

#define PCLK      (CCLK/4)           // Peripheral clock frequency

#define I2C_SPEED 100000             // I2C communication speed

#define LOAD_VAL  ((PCLK/I2C_SPEED)/2) // SCL timing load value


// I2CONSET register bit definitions
#define AA   2                       // Assert acknowledge bit

#define SI   3                       // Interrupt flag bit

#define STO  4                       // STOP condition bit

#define STA  5                       // START condition bit

#define I2EN 6                       // I2C enable bit


// I2CONCLR register bit definitions
#define AAC    2                     // Clear acknowledge bit

#define SIC    3                     // Clear interrupt flag

#define STAC   5                     // Clear START condition bit

#define I2ENC  6                     // Disable I2C interface


#endif                               // End of conditional compilation
/*---------------------------------------------------------
 *File Name    : i2c_defines.h
 * Description  : I2C Macro Definitions
 *---------------------------------------------------------*/

#ifndef _I2C_DEFINES_H_              // Start of conditional compilation
#define _I2C_DEFINES_H_              // Define header guard


// I2C pin definitions
#define SCL 2                         // Serial clock pin
#define SDA 3                         // Serial data pin


// PINSEL0 values for I2C pin function selection
#define SCL_PIN_FUNC 0X00000010      // Enable SCL function
#define SDA_PIN_FUNC 0X00000040      // Enable SDA function


// Clock configuration values
#define FOSC       12000000          // Oscillator frequency

#define CCLK      (FOSC*5)           // CPU clock frequency

#define PCLK      (CCLK/4)           // Peripheral clock frequency

#define I2C_SPEED 100000             // I2C communication speed

#define LOAD_VAL  ((PCLK/I2C_SPEED)/2) // SCL timing load value


// I2CONSET register bit definitions
#define AA   2                       // Assert acknowledge bit

#define SI   3                       // Interrupt flag bit

#define STO  4                       // STOP condition bit

#define STA  5                       // START condition bit

#define I2EN 6                       // I2C enable bit


// I2CONCLR register bit definitions
#define AAC    2                     // Clear acknowledge bit

#define SIC    3                     // Clear interrupt flag

#define STAC   5                     // Clear START condition bit

#define I2ENC  6                     // Disable I2C interface


#endif                               // End of conditional compilation
