
#include "uart.h"                    // UART header file
#include "lcd.h"                     // LCD header file
#include "types.h"                   // User defined data types
#include <LPC21xx.H>                 // LPC214x controller header

char ch,dummy;                       // Global variables

extern u8 i,rec_buf[25],frame_ready; // External receive variables

void init_uart0(void)
{
        // Configure P0.0 and P0.1 as TXD0 and RXD0 pins
        PINSEL0 &= ~(15<<0);         // Clear UART pin configuration bits

        PINSEL0 |= (TXD0_PIN|RXD0_PIN); // Enable UART pin functions

        // Enable DLAB bit for baud rate configuration
        U0LCR = (1<<DLAB);

        // Configure UART word length
        U0LCR |= (WORD_LENGTH_SELECT);

        // Configure baud rate using divisor registers
        U0DLM = DIVISOR>>8;          // Load divisor high byte

        U0DLL = DIVISOR;             // Load divisor low byte

        // Disable DLAB bit after baud rate configuration
        U0LCR &= ~(1<<DLAB);

        // Configure UART interrupt as IRQ
        VICIntSelect = 0x00000000;

        // Set UART0 ISR address
        VICVectAddr0 = (unsigned)UART0_isr;

        // Enable UART0 interrupt channel
        VICVectCntl0 = 0x20 | 6;

        // Enable UART0 interrupt in VIC
        VICIntEnable = 1 << 6;

        // Enable UART0 RX and THRE interrupts
        U0IER = 0x03;
}

void UART0_isr(void) __irq
{
        if((U0IIR & 0x04))           // Check receive interrupt
        {
                ch = U0RBR;          // Read received byte

                rec_buf[i++] = ch;   // Store received data into buffer

                if(i >= 12)          // Check complete frame received
                {
                        frame_ready = 1; // Set frame ready flag
                }
        }

        else
        {
                dummy = U0IIR;       // Read IIR to clear transmit interrupt
        }

        VICVectAddr = 0;             // Dummy write to VIC
}

void u0_Tx_byte(unsigned char byte)
{
        U0THR = byte;                // Load data into transmit register

        while(((U0LSR>>TEMT_BIT)&1)==0); // Wait until transmission complete
}

unsigned char u0_Rx_byte(void)
{
        while(((U0LSR>>DR_BIT)&1)==0); // Wait until data received

        return U0RBR;               // Return received byte
}

void u0_Tx_str(char *str)
{
         while(*str)                 // Repeat until null character
         {
                  u0_Tx_byte(*str++); // Transmit character
         }
}



char* u0_Rx_str(void)
{
        static char str[50];         // Buffer to store received string

        char i = 0;                  // Index variable

        do
        {
                str[i] = u0_Rx_byte(); // Receive character

                u0_Tx_byte(str[i]);  // Echo received character

                if((str[i]=='\r') || (str[i]=='\n')) // Check ENTER key
                {
                        break;       // Exit loop
                }

                i++;                 // Increment index

        }while((i!=49));             // Prevent buffer overflow

        str[i-1] = 0;                // Replace ENTER with null character

        return str;                  // Return received string
}

