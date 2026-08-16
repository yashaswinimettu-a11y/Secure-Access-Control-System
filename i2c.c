#include <lpc21xx.h>
#include "i2c_defines.h"
#include "types.h"
/*---------------------------------------------------------
 * Function Name : init_i2c
 * Description   : Initializes I2C peripheral
 *                 -> Configures SDA and SCL pins
 *                 -> Sets I2C clock frequency
 *                 -> Enables I2C module
 * Return Type   : void
 *---------------------------------------------------------*/

void init_i2c(void)
{
        // Clear SDA and SCL pin configuration bits
        PINSEL0 &= ~(15<<2*2);

        // Configure pins for I2C functionality
        PINSEL0 |=  SCL_PIN_FUNC | SDA_PIN_FUNC;

        // Set low period of I2C clock
        I2SCLL = LOAD_VAL;

        // Set high period of I2C clock
        I2SCLH = LOAD_VAL;

        // Enable I2C peripheral
        I2CONSET = 1<<I2EN;
}


/*---------------------------------------------------------
 * Function Name : i2c_start
 * Description   : Generates I2C start condition
 *                 -> Sends START signal
 *                 -> Waits until operation completes
 *                 -> Clears start condition flag
 * Return Type   : void
 *---------------------------------------------------------*/

void i2c_start(void)
{
        // Generate START condition
        I2CONSET = 1<<STA;

        // Wait until SI flag is set
        while(((I2CONSET>>SI)&1)==0);

        // Clear START condition flag
        I2CONCLR = 1<<STAC;
}


/*---------------------------------------------------------
 * Function Name : i2c_stop
 * Description   : Generates I2C stop condition
 *                 -> Sends STOP signal
 *                 -> Clears interrupt flag
 * Return Type   : void
 *---------------------------------------------------------*/

void i2c_stop(void)
{
        // Generate STOP condition
        I2CONSET  = 1<<STO;

        // Clear SI flag
        I2CONCLR = 1<<SIC;
}


/*---------------------------------------------------------
 * Function Name : i2c_restart
 * Description   : Generates repeated start condition
 *                 -> Sends repeated START signal
 *                 -> Clears interrupt flag
 *                 -> Waits for completion
 * Return Type   : void
 *---------------------------------------------------------*/

void i2c_restart(void)
{
        // Generate repeated START condition
        I2CONSET = 1<<STA;

        // Clear SI flag
        I2CONCLR = 1<<SIC;

        // Wait until SI flag is set
        while(((I2CONSET>>SI)&1)==0);

        // Clear START flag
        I2CONCLR = 1<<STA;
}


/*---------------------------------------------------------
 * Function Name : i2c_write
 * Description   : Writes one byte on I2C bus
 *                 -> Loads data into I2C data register
 *                 -> Clears interrupt flag
 *                 -> Waits until transmission completes
 * Return Type   : void
 * Arguments     : sdat -> Data byte to transmit
 *---------------------------------------------------------*/

void i2c_write(u8 sdat)
{
        // Load data into I2C data register
        I2DAT = sdat;

        // Clear SI flag
        I2CONCLR = 1<<SIC;

        // Wait until transmission completes
        while(((I2CONSET>>SI)&1)==0);
}
/*---------------------------------------------------------
 * Function Name : i2c_nack
 * Description   : Receives data byte from I2C bus
 *                 without acknowledgment
 *                 -> Used for last byte reception
 *                 -> Clears interrupt flag
 *                 -> Waits for data reception
 *                 -> Returns received data
 * Return Type   : u8
 *---------------------------------------------------------*/

u8 i2c_nack(void)
{
        // Explicitly disable master ACK generation for this byte
        I2CONCLR = 1<<AAC; // Clear Assert Acknowledge flag

        // Clear SI flag to start transaction
        I2CONCLR = 1<<SIC;

        // Wait until data is received
        while(((I2CONSET>>SI)&1)==0);

        // Return received data
        return I2DAT;
}


/*---------------------------------------------------------
 * Function Name : i2c_mack
 * Description   : Receives data byte from I2C bus
 *                 with acknowledgment
 *                 -> Sends ACK after reception
 *                 -> Clears interrupt flag
 *                 -> Waits for data reception
 *                 -> Returns received data
 * Return Type   : u8
 *---------------------------------------------------------*/

u8 i2c_mack(void)
{
        // Enable acknowledge bit
        I2CONSET = 1<<AA;

        // Clear SI flag
        I2CONCLR = 1<<SIC;

        // Wait until data is received
        while(((I2CONSET>>SI)&1)==0);

        // Clear acknowledge flag
        I2CONCLR = 1<<AAC;

        // Return received data
        return I2DAT;
}
