#include <lpc21XX.h>                 // LPC214x header file
#include "macros.h"                  // Macro definitions
#include "types.h"                   // User defined data types
#include "delay.h"                   // Delay functions
#include "lcd.h"                     // LCD function declarations

void write_lcd(u8 data)
{
         G_SETBIT(IOCLR0,RW);        // Select write operation

         WBYTE(IOPIN0,DATA,data);    // Send data to LCD pins

         G_SETBIT(IOSET0,EN);        // Enable LCD

         delay_us(1);                // Small delay

         G_SETBIT(IOCLR0,EN);        // Disable enable pin

         delay_ms(2);                // LCD processing delay
}

void cmd_lcd(u8 cmd)
{
        G_SETBIT(IOCLR0,RS);         // Select command register

        write_lcd(cmd);              // Send command to LCD
}

void init_lcd()
{
        WBYTE(IODIR0,DATA,0XFF);     // Configure data pins as output

        SETBIT(IODIR0,RS);           // Configure RS pin as output

        SETBIT(IODIR0,RW);           // Configure RW pin as output

        SETBIT(IODIR0,EN);           // Configure EN pin as output

        delay_ms(15);                // LCD power ON delay

        cmd_lcd(MODE_8BIT_LINE1);    // Initialize LCD in 8-bit mode

        delay_ms(5);                 // Delay after command

        cmd_lcd(0x30);               // Function set command

        delay_us(100);               // Small delay

        cmd_lcd(MODE_8BIT_LINE1);    // Reinitialize LCD

        cmd_lcd(MODE_8BIT_LINE2);    // Configure LCD in 2-line mode

        cmd_lcd(DISP_ON);            // Turn ON display

        cmd_lcd(LCD_CLR);            // Clear LCD screen

        cmd_lcd(DISP_SHIFT_OFF_INC); // Cursor increment mode
}


void char_lcd(u8 character)
{
        SETBIT(IOSET0,RS);           // Select data register

        write_lcd(character);        // Send character to LCD
}

void str_lcd(u8 *p)
{
        while(*p)                    // Repeat until null character
                char_lcd(*p++);      // Display character
}

void u32_lcd(u32 n)
{
        u8 a[10];                    // Array to store digits

        s32 i=0;                     // Loop variable

        if(n==0)                     // Check for zero
        {
                char_lcd('0');       // Display zero
        }

        else
        {
                while(n)             // Extract digits
                {
                        a[i]=(n%10)+48; // Convert digit to ASCII

                        i++;         // Increment index

                        n/=10;       // Remove last digit
                }

                for(--i;i>=0;i--)    // Display digits in correct order
                {
                        char_lcd(a[i]); // Display digit
                }
        }
}

void float_lcd(f32 f,s32 np)
{
        s32 i;                       // Variable for integer part

        if(f<0)                      // Check for negative number
        {
                char_lcd('-');       // Display negative sign

                f*=-1;               // Convert into positive value
        }

        i=f;                         // Extract integer part

        u32_lcd(i);                  // Display integer part

        char_lcd('.');               // Display decimal point

        f = f-i;                     // Extract fractional part

        while(np)                    // Shift decimal digits
        {
                f*=10;               // Multiply by 10

                np--;                // Decrement precision count
        }

        i = f;                       // Convert fractional part to integer

        u32_lcd(i);                  // Display fractional part
}

void s32_lcd(s32 n)
{
        if(n<0)                      // Check for negative number
        {
                char_lcd('-');       // Display negative sign

                n*=-1;               // Convert into positive value
        }

        u32_lcd(n);                  // Display integer value
}

void title(void)
{
		u8 i;
        char line1[] = " SECURE ACCESS "; // First line message

        char line2[] = " CONTROL SYSTEM "; // Second line message

        cmd_lcd(0x01);               // Clear LCD
for(i=0;line1[i]!=0;i++)
	{
        cmd_lcd(GOTO_LINE1_POS_0+i);  
				 delay_ms(100);
        char_lcd(line1[i]);
        delay_ms(100);  
	}
	for(i=0;line2[i]!=0;i++)
	{
		cmd_lcd(GOTO_LINE2_POS_0+i);   
		delay_ms(100);		
    char_lcd(line2[i]); 
		delay_ms(100);
	}
   
}
void bulid_symbols(void)
{
	u8 i,sy[60]={
				 0x00,0x11,0x0A,0x04,0x0A,0x11,0x00,0x00,  // x
				 0x00,0x01,0x02,0x14,0x08,0x00,0x00,0x00,  // correct
				 0x02,0x02,0x0e,0x1f,0x1f,0x1f,0x0e,0x00,	 //finger
				 0x00,0x1F,0X11,0X11,0X1F,0X1B,0X1F,0X00, //LOCKED
				 0X1F,0X11,0X01,0X01,0X1F,0X1B,0X1F,0X00,	//UNLOCKED
				 0x00,0x04,0x06,0x1F,0X1F,0X06,0X04,0X00,
				 0X00,0X04,0X0C,0X1F,0X1F,0X0C,0X04,0X00
				 }; 
	cmd_lcd(GOTO_CGRAM);
	for(i=0;i<=55;i++)
	{
		char_lcd(sy[i]);	
	}
	cmd_lcd(0x80);
}
