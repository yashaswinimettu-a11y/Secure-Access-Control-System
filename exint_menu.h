#include "types.h"
#ifndef _EXINT_MENU_H_                 // Start of conditional compilation
#define _EXINT_MEMU_H_                 // Define header guard


#define EINT2_INPUT_PIN 0x0000C000    // External interrupt input pin
#define EINT2_VIC_CHNO 16             // VIC channel number


void init_eint2(void);                // Initialize external interrupt

void eint2_isr(void) __irq;           // External interrupt ISR

s8 is_user_id_in_db(char *id1);
s8 is_id_in_db(char);

void enroll_id(void);                 // Enroll new user

void menu(void);                      // Menu function

s8 check_admin(void);                 // Verify admin

void login(void);                     // User login

void forget_password(void);           // Forgot password function

void finger_edit(void);               // Fingerprint edit function

void password_edit(void);             // Password edit function

void init_ids(void);                  // Initialize IDs

void disable(void);                   // Disable system

void enable(void);                    // Enable system

void edit(void);                      // Edit menu function

void delete_id(void);                 // Delete user ID

void title(void);

#endif                                // End of conditional compilation
