
#ifndef _UART_H_                     // Start of conditional compilation
#define _UART_H_                     // Define header guard


// Clock configuration values
#define FOSC 12000000                // Oscillator frequency

#define PLL  5                       // PLL multiplier value

#define CCLK (FOSC*PLL)              // CPU clock frequency

#define PCLK (CCLK/4)                // Peripheral clock frequency

#define BAUD 9600                    // UART baud rate

#define DIVISOR (PCLK/(16*BAUD))     // Baud rate divisor value


// Pin connect block definitions
#define TXD0_PIN 0x00000001          // TXD0 pin function

#define RXD0_PIN 0x00000004          // RXD0 pin function


// UxLCR register bit definitions
#define DLAB 7                       // Divisor latch access bit

#define _8BIT 3                      // 8-bit data mode

#define WORD_LENGTH_SELECT _8BIT     // Word length selection


// UxLSR register bit definitions
#define TEMT_BIT 6                   // Transmitter empty bit

#define DR_BIT  0                    // Data ready bit


// Function declarations
void init_uart0(void);               // Initialize UART0

void u0_Tx_byte(unsigned char byte); // Transmit one byte

unsigned char u0_Rx_byte(void);      // Receive one byte

void u0_Tx_str(char *str);           // Transmit string

char* u0_Rx_str(void);               // Receive string

void UART0_isr(void) __irq;          // UART0 interrupt service routine


#endif                               // End of conditional compilation
