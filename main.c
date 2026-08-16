#include "lcd.h"                     // LCD driver header
#include "kpm.h"                     // Keypad driver header
#include "i2c.h"                     // I2C driver header
#include "i2c_eeprom.h"              // EEPROM driver header
#include "uart.h"                    // UART driver header
#include "r305.h"                    // Fingerprint sensor header
#include "delay.h"                   // Delay functions
#include "exint_menu.h"              // External interrupt header
//#include "i2c_eeprom.h"              // EEPROM header
#include "types.h"                   // User defined data types
#include "l293d.h"                   // Motor driver header

extern u8 menu_flag,ids;                 // External menu flag variable

char usr_id[][4]={"1111","2222","3333","4444"}; // default user id's
char usr_pass[][4]={"1234","4321","5678","8765"}; // default user password's

int main()
{
	int i;
	//char ch;
        init_lcd();                  // Initialize LCD

        init_kpm();                  // Initialize keypad

        init_uart0();                // Initialize UART0

        init_i2c();                   // Initialize I2C

        init_eint2();                // Initialize external interrupt

       //init_ids();                  // Initialize stored IDs

	   bulid_symbols();

       init_l293d();                // Initialize motor driver
	
	   ids=i2c_eeprom_read_byte(0x50,0x0070);

       title();                     // Display first project title
	   for(i=0;i<4;i++)
	   {
	   	i2c_eeprom_write_page(0x50,USER_ID_ADDR+(i*5),(s8 *)usr_id[i],4);	//storing user id's into EEPROM
		delay_ms(100);
	   }
	   /*for(i=0;i<4;i++)
	   {
	   	i2c_eeprom_write_page(0x50,USER_PASS_ADDR+(i*5),(s8 *)usr_pass[i],4);	//storing user password's into EEPROM
		delay_ms(100);
	   } */
       delay_ms(1000);  	// Delay
		while(1)
        {
			 if(menu_flag==1)      // Check menu interrupt flag
             {
			 	menu_flag=0;
             	menu();       // Open menu
					//	menu_flag=0;
             }				
        	 login();              // Perform login operation		
        }
}
