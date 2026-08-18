#ifndef _LCD_H_                      // Start of conditional compilation
#define _LCD_H_                      // Define header guard


#include <string.h>                  // String handling functions

#include "types.h"                  // User defined data types


// LCD data and control pins
#define DATA 8                       // LCD data pin starting position

#define RS 16                        // Register select pin

#define RW 18                        // Read/Write pin

#define EN 17                        // Enable pin


// LCD basic commands
#define LCD_CLR 0X01                 // Clear LCD display

#define RET_CUR_HOME 0X02            // Return cursor to home


// Display ON/OFF commands
#define DISP_OFF 0X08                // Display OFF

#define DISP_ON 0X0C                 // Display ON

#define DISP_ON_CUR_ON_BLK_ON 0X0F   // Display ON with cursor and blink

#define DISP_ON_CUR_ON 0X0E          // Display ON with cursor


// Entry mode set commands
#define DISP_SHIFT_OFF_INC 0X06      // Cursor increment without shift

#define DISP_SHIFT_INC 0X07          // Cursor increment with shift


// LCD function set commands
#define MODE_8BIT_LINE1 0X30         // 8-bit single line mode

#define MODE_8BIT_LINE2 0X38         // 8-bit dual line mode

#define MODE_4BIT_LINE1 0X20         // 4-bit single line mode

#define MODE_4BIT_LINE2 0X28         // 4-bit dual line mode


// Cursor position commands
#define GOTO_LINE1_POS_0 0X80        // Cursor line 1 position 0

#define GOTO_LINE2_POS_0 0XC0        // Cursor line 2 position 0

#define GOTO_LINE3_POS_0 0X94        // Cursor line 3 position 0

#define GOTO_LINE4_POS_0 0XD4        // Cursor line 4 position 0


// Cursor shift commands
#define SHIFT_CUR_LEFT  0X10         // Shift cursor left

#define SHIFT_CUR_RIGHT 0X14         // Shift cursor right


// CGRAM command
#define GOTO_CGRAM 0X40              // Select CGRAM address


// Function declarations
void write_lcd(u8);                  // Write data/command to LCD

void cmd_lcd(u8);                    // Send command to LCD

void init_lcd(void);                 // Initialize LCD

void char_lcd(u8);                   // Display single character

void str_lcd(u8*);                   // Display string

void u32_lcd(u32);                   // Display unsigned integer

void float_lcd(f32,s32);             // Display floating value

void s32_lcd(s32);                   // Display signed integer

void title(void);

void bulid_symbols(void);
#endif                               // End of conditional compilation
