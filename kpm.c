/*---------------------------------------------------------
 * File Name    : keypad.c
 * Description  : 4x4 Matrix Keypad Driver Functions
 *                 -> Keypad initialization
 *                 -> Key scanning
 *                 -> Password input
 *                 -> ID input
 *                 -> Numeric input handling
 *---------------------------------------------------------*/

#include "kpm.h"
#include "types.h"
#include "macros.h"
#include "delay.h"
#include "lcd.h"
#include <lpc21xx.h>

// Menu flag variable
u8 menu_flag = 0;

// Enable keypad mode
#define KEYPAD


/*---------------------------------------------------------
 * Keypad Lookup Table
 *---------------------------------------------------------*/

#ifdef KEYPAD

s32 kpmlut[4][4] =
{
        {'1','2','3','A'},
        {'4','5','6','B'},
        {'7','8','9','-'},
        {'*','0','=','B'}
};

#else

s32 kpmlut[4][4] =
{
        {'1','2','3','4'},
        {'5','6','7','8'},
        {'9','0','+','-'},
        {'*','/','=','B'}
};

#endif

void init_kpm(void)
{
        // Configure keypad row pins as output
        WNIBBLE(IODIR1,row0,15);
}

u32 colscan(void)
{
        // Return 0 if key pressed
        // Return 1 if no key pressed
        return (RNIBBLE(IOPIN1,col0)<15)?0:1;
}

u32 rowcheck(void)
{
        // Variable for row number
        u32 rno;

        // Scan all rows
        for(rno=0;rno<4;rno++)
        {
                // Activate one row
                WNIBBLE(IOPIN1,row0,~(1<<rno));

                // Check key press
                if(colscan()==0)
                {
                        break;
                }
        }

        // Clear all rows
        WNIBBLE(IOPIN1,row0,0X0);

        // Return row number
        return rno;
}

u32 colcheck(void)
{
        // Variable for column number
        u32 cno;

        // Scan all columns
        for(cno=0;cno<4;cno++)
        {
                // Check active column
                if(RBIT(IOPIN1,(col0+cno))==0)
                {
                        break;
                }
        }

        // Return column number
        return cno;
}


s32 keyscan(void)
{
        // Variables for key value, row and column
        s32 keyv,rno,cno;
		menu_flag=0;

        // Wait until key is pressed
        while(colscan() && menu_flag==0);

        // Exit condition
        if(menu_flag==1)
        {
                return -1;
        }

        // Detect row
        rno = rowcheck();

        // Detect column
        cno = colcheck();

        // Read key from lookup table
        keyv = kpmlut[rno][cno];

        // Wait until key release
        while(!colscan());

        // Debounce delay
        delay_ms(100);

        // Return key value
        return keyv;
}

s32 readnum(void)
{
        // Variable for keypad input
        s32 key;

        // Digit counter
        s32 cnt = 0;

        // Variable for final number
        int num = 0;

        while(1)
        {
                        // Read keypad input
                        key = keyscan();

                        // Exit condition
                        if(key == -1)
                        {
                                cnt = 0;

                                return -1;
                        }

                        // Accept numeric digits
                        if((key>='0') && (key<='9') && (cnt<4))
                        {
                                 // Increment count
                                 cnt++;

                                 // Display digit
                                 char_lcd(key);

                                 // Convert ASCII to integer
                                 num = num*10 + (key-48);
                        }

                        // Backspace operation
                        else if((key=='B') && (cnt!=0))
                        {
                                // Decrement count
                                cnt--;

                                // Move cursor left
                                cmd_lcd(0x10);

                                // Clear character
                                char_lcd(' ');

                                // Move cursor back
                                cmd_lcd(0x10);

                                // Remove last digit
                                num /= 10;
                        }

                        // Enter key pressed
                        else if((key == '=') && (cnt!=0))
                        {
                                // Reset counter
                                cnt = 0;

                                // Return entered number
                                return num;
                        }
        }
}


void password_kpm(char *ptr)
{
        // Variable for keypad input
        u8 a;

        // Digit counter
        u8 cnt = 0;

        while(1)
        {
                // Read keypad input
                a = keyscan();

                // Accept numeric digits
                if((a>='0') && (a<='9') && (cnt!=4))
                {
                        // Increment counter
                        cnt++;

                        // Display digit
                        char_lcd(a);

                        // Delay for visibility
                        delay_ms(300);

                        // Move cursor left
                        cmd_lcd(0x10);

                        // Display '*'
                        char_lcd('*');

                        // Store password digit
                        *ptr = a;

                        // Move pointer
                        ptr++;
                }

                // Backspace operation
                else if((a=='B') && (cnt!=0))
                {
                        // Move cursor left
                        cmd_lcd(0x10);

                        // Clear character
                        char_lcd(' ');

                        // Move cursor back
                        cmd_lcd(0x10);

                        // Decrement counter
                        cnt--;

                        // Move pointer backward
                        ptr--;
                }

                // Enter key pressed
                else if((a=='=') && (cnt==4))
                {
                        // Reset counter
                        cnt = 0;

                        // Null terminate string
                        *ptr = '\0';

                        // Exit function
                        return;
                }
        }
}

s8 id_kpm1(s8 *ptr)
{
        // Variable for keypad input
        s8 a;

        // Digit counter
        s8 cnt = 0;
		cmd_lcd(0xc0);
        while(1)
        {
                // Read keypad input
                a = keyscan();
				if(a==-1)
					return -1;
				//break;
				 // char_lcd(a);
                // Accept numeric digits
                if((a>='0') && (a<='9'))
                {
				if(cnt<4)
				{
                        // Display digit
                        char_lcd(a);

                        // Store digit
                        ptr[cnt] = a;

                        // Increment counter
                        cnt++;
						}
                }

                // Backspace operation
                else if((a=='B') && (cnt!=0))
                {
                        // Decrement counter
                        cnt--;

                        // Move cursor left
                        cmd_lcd(0x10);

                        // Clear character
                        char_lcd(' ');

                        // Move cursor back
                        cmd_lcd(0x10);
                }

                // Enter key pressed
                else if((a == '='))
                {
				if(cnt==4)
				{
                        // Null terminate string
                        ptr[cnt] = '\0';

                        // Exit function
                      //  return;
					  break;
                }
				}
        }
}
  s8 id_kpm(s8 *ptr)
{
        // Variable for keypad input
        s8 a;

        // Digit counter
        s8 cnt = 0;
		cmd_lcd(0xc0);
        while(1)
        {
                // Read keypad input
                a = keyscan();
				if(a==-1)
					return -1;
				//break;
				 // char_lcd(a);
                // Accept numeric digits
                if((a>='0') && (a<='9'))
                {
				
				
                        // Display digit
                        char_lcd(a);

                        // Store digit
                        ptr[cnt] = a;

                        // Increment counter
                        cnt++;
						
                }

                // Backspace operation
                else if((a=='B') && (cnt!=0))
                {
                        // Decrement counter
                        cnt--;

                        // Move cursor left
                        cmd_lcd(0x10);

                        // Clear character
                        char_lcd(' ');

                        // Move cursor back
                        cmd_lcd(0x10);
                }

                // Enter key pressed
                else if((a == '='))
                {

                        // Null terminate string
                        ptr[cnt] = '\0';

                        // Exit function
                      //  return;
					  break;
                
				}
        }
}

