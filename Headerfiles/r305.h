#ifndef _R305_H_                     // Start of conditional compilation
#define _R305_H_                     // Define header guard


#include "types.h"                  // User defined data types


void send_packet(u8 *ptr,u8 n);     // Send packet to fingerprint sensor

s8 Genimg(void);                    // Capture fingerprint image

s8 img2tp1(void);                   // Convert image to template buffer1

s8 img2tp2(void);                   // Convert image to template buffer2

s8 regmodel(void);                  // Generate fingerprint model

s8 store(s8 id);                    // Store fingerprint template

s8 delete(s8 id);                   // Delete fingerprint template

s8 match(void);                     // Match fingerprint templates

s8 load_char(s8 id);                // Load stored template

s8 enroll(s8 id);                   // Enroll new fingerprint

s8 verify(s8 id);                   // Verify fingerprint


#endif                               // End of conditional compilation
