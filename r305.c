
#include "lcd.h"                     // LCD driver header
#include "uart.h"                    // UART driver header
#include "delay.h"                   // Delay functions

u8 snd_buf[20],rec_buf[25],j=0,i=0,frame_ready=0; // Global buffers and flags


void send_packet(u8 *ptr,u8 n)
{
        for(j=0;j<n;j++)             // Send all packet bytes
        {
                u0_Tx_byte(ptr[j]);  // Transmit one byte through UART
        }
}


s8 Genimg(void)
{
        u16 timeout = 0;             // Timeout counter

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<12;j++)            // Clear transmit buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x03;           // Packet length low byte

        snd_buf[9] = 0x01;           // Fingerprint capture command

        snd_buf[10] = 0x00;          // Checksum high byte

        snd_buf[11] = 0x05;          // Checksum low byte

        send_packet(snd_buf,12);     // Send packet to sensor

        delay_ms(10);                // Small delay

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        if(rec_buf[9] == 0x00)       // Check response status
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}

s8 img2tp1(void)
{
        u16 timeout = 0;             // Timeout counter

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<13;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x04;           // Packet length low byte

        snd_buf[9] = 0x02;           // Image to template command

        snd_buf[10] = 0x01;          // Store template in buffer 1

        snd_buf[11] = 0x00;          // Checksum high byte

        snd_buf[12] = 0x08;          // Checksum low byte

        frame_ready = 0;             // Reset frame flag

        send_packet(snd_buf,13);     // Send packet to fingerprint sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        if(rec_buf[9] == 0x00)       // Check sensor response
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}


s8 img2tp2(void)
{
        u16 timeout = 0;             // Timeout counter

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<13;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x04;           // Packet length low byte

        snd_buf[9] = 0x02;           // Image to template command

        snd_buf[10] = 0x02;          // Store template in buffer 2

        snd_buf[11] = 0x00;          // Checksum high byte

        snd_buf[12] = 0x09;          // Checksum low byte

        send_packet(snd_buf,13);     // Send packet to sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        if(rec_buf[9] == 0x00)       // Check sensor response
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}

s8 regmodel(void)
{
        u16 timeout = 0;             // Timeout counter

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<12;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x03;           // Packet length low byte

        snd_buf[9] = 0x05;           // Generate model command

        snd_buf[10] = 0x00;          // Checksum high byte

        snd_buf[11] = 0x09;          // Checksum low byte

        send_packet(snd_buf,12);     // Send packet to sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        if(rec_buf[9] == 0x00)       // Check sensor response
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}

s8 store(s8 id)
{
        u16 sum,timeout = 0;         // Variables for checksum and timeout

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<15;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x06;           // Packet length low byte

        snd_buf[9] = 0x06;           // Store template command

        snd_buf[10] = 0x01;          // Select buffer 1

        snd_buf[11] = 0x00;          // Page ID high byte

        snd_buf[12] = id;            // Page ID low byte

        sum = 0x01 + 0x00 + 0x06 + 0x06 + 0x01 + 0x00 + id; // Calculate checksum

        snd_buf[13] = sum>>8;        // Store checksum high byte

        snd_buf[14] = sum&0xff;      // Store checksum low byte

        send_packet(snd_buf,15);     // Send packet to sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        if(rec_buf[9] == 0x00)       // Check sensor response
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}

s8 load_char(s8 id)
{
        u16 sum,timeout = 0;         // Variables for checksum and timeout

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<15;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x06;           // Packet length low byte

        snd_buf[9] = 0x07;           // LoadChar command

        snd_buf[10] = 0x02;          // Select Char Buffer 2

        snd_buf[11] = 0x00;          // Page ID high byte

        snd_buf[12] = id;            // Page ID low byte

        sum = 0x01 + 0x00 + 0x06 + 0x07 + 0x02 + 0x00 + id; // Calculate checksum

        snd_buf[13] = (sum >> 8);    // Store checksum high byte

        snd_buf[14] = (sum & 0xFF);  // Store checksum low byte

        send_packet(snd_buf,15);     // Send packet to sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        return (rec_buf[9] == 0x00) ? 0 : 1; // Return status
}


s8 match(void)
{
    u16 timeout = 0;                 // Timeout counter

    frame_ready = 0;                 // Clear frame ready flag

    i = 0;                           // Reset receive buffer index

    for(j=0;j<25;j++)                // Clear receive buffer
    {
        rec_buf[j] = 0;
    }

    for(j=0;j<12;j++)                // Clear send buffer
    {
        snd_buf[j] = 0;
    }

    snd_buf[0] = 0xEF;               // Packet header byte 1

    snd_buf[1] = 0x01;               // Packet header byte 2

    snd_buf[2] = 0xFF;               // Device address byte 1

    snd_buf[3] = 0xFF;               // Device address byte 2

    snd_buf[4] = 0xFF;               // Device address byte 3

    snd_buf[5] = 0xFF;               // Device address byte 4

    snd_buf[6] = 0x01;               // Command packet identifier

    snd_buf[7] = 0x00;               // Packet length high byte

    snd_buf[8] = 0x03;               // Packet length low byte

    snd_buf[9] = 0x03;               // Match command

    snd_buf[10] = 0x00;              // Checksum high byte

    snd_buf[11] = 0x07;              // Checksum low byte

    send_packet(snd_buf,12);         // Send packet to sensor

    while(frame_ready == 0)          // Wait for response frame
    {
        delay_ms(1);                 // Small delay

        timeout++;                   // Increment timeout counter

        if(timeout > 100)            // Timeout condition
        {
                return 1;            // Return failure
        }
    }

    return (rec_buf[9] == 0x00) ? 0 : 1; // Return match status
}

s8 delete(s8 id)
{
        u16 sum,timeout = 0;         // Variables for checksum and timeout

        frame_ready = 0;             // Clear frame ready flag

        i = 0;                       // Reset receive buffer index

        for(j=0;j<25;j++)            // Clear receive buffer
        {
                rec_buf[j] = 0;
        }

        for(j=0;j<15;j++)            // Clear send buffer
        {
                snd_buf[j] = 0;
        }

        snd_buf[0] = 0xEF;           // Packet header byte 1

        snd_buf[1] = 0x01;           // Packet header byte 2

        snd_buf[2] = 0xFF;           // Device address byte 1

        snd_buf[3] = 0xFF;           // Device address byte 2

        snd_buf[4] = 0xFF;           // Device address byte 3

        snd_buf[5] = 0xFF;           // Device address byte 4

        snd_buf[6] = 0x01;           // Command packet identifier

        snd_buf[7] = 0x00;           // Packet length high byte

        snd_buf[8] = 0x07;           // Packet length low byte

        snd_buf[9] = 0x0C;           // Delete template command

        snd_buf[10] = 0x00;          // Page ID high byte

        snd_buf[11] = id;            // Page ID low byte

        snd_buf[12] = 0x00;          // Number of templates high byte

        snd_buf[13] = 0x01;          // Number of templates low byte

        sum = 0x01 + 0x00 + 0x07 + 0x0c + 0x00 + id + 0x00 + 0x01; // Calculate checksum

        snd_buf[14] = (sum >> 8)&0xff; // Store checksum high byte

        snd_buf[15] = (sum & 0xFF);  // Store checksum low byte

        send_packet(snd_buf,16);     // Send packet to sensor

        while(frame_ready == 0)      // Wait for response frame
        {
                delay_ms(1);         // Small delay

                timeout++;           // Increment timeout counter

                if(timeout > 1000)   // Timeout condition
                {
                        return 1;    // Return failure
                }
        }

        return (rec_buf[9] == 0x00) ? 0 : 1; // Return delete status
}


s8 enroll(s8 id)
{
        s8 ret,retry=0;              // Variables for return status and retry count

        cmd_lcd(0x01);               // Clear LCD screen

        str_lcd("PLACE FINGER ");    // Display message

        char_lcd(2);                 // Display finger symbol

        // WAIT FOR FINGER
        while(Genimg() != 0)         // Wait until finger is detected
        {
                delay_ms(50);        // Small delay

                retry++;             // Increment retry counter

                if(retry > 100)      // Timeout condition
                {
                        cmd_lcd(0x01); // Clear LCD

                        str_lcd("Timeout"); // Display timeout message

                        delay_ms(500); // Delay

                        return 1;    // Return failure
                }
        }

        // FIRST CAPTURE
        ret = Genimg();              // Capture fingerprint image

        if(ret != 0)                 // Check capture status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("GenImg Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        ret = img2tp1();             // Convert image into template buffer 1

        if(ret != 0)                 // Check conversion status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Tz1 Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        cmd_lcd(0x01);               // Clear LCD

        str_lcd("Remove Finger");    // Ask user to remove finger

        // WAIT UNTIL FINGER REMOVED
        while(Genimg() == 0)         // Wait while finger remains on sensor
        {
                delay_ms(50);        // Small delay
        }

        delay_ms(1000);              // Delay after finger removal

        cmd_lcd(0x01);               // Clear LCD

        str_lcd("PLACE AGAIN ");     // Ask user to place finger again

        char_lcd(2);                 // Display finger symbol

        // WAIT AGAIN FOR FINGER
        while(Genimg() != 0)         // Wait until finger detected again
        {
                delay_ms(50);        // Small delay
        }

        // SECOND CAPTURE
        ret = Genimg();              // Capture second fingerprint image

        if(ret != 0)                 // Check capture status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("GenImg2 Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        ret = img2tp2();             // Convert image into template buffer 2

        if(ret != 0)                 // Check conversion status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Tz2 Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        // CREATE TEMPLATE
        ret = regmodel();            // Generate fingerprint model

        if(ret != 0)                 // Check model generation status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Reg Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        // STORE TEMPLATE
        ret = store(id);             // Store fingerprint into database

        if(ret != 0)                 // Check store status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Store Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        cmd_lcd(0x01);               // Clear LCD

        str_lcd("ENROLL DONE ");     // Display success message

        char_lcd(1);                 // Display success symbol

        delay_ms(500);               // Delay

        return 0;                    // Return success
}

s8 verify(s8 id)
{
        s8 ret;                      // Variable for return status

        cmd_lcd(0x01);               // Clear LCD screen

        str_lcd("PLACE FINGER ");    // Display message

        char_lcd(2);                 // Display finger symbol

        // WAIT FOR FINGER
        while(Genimg() != 0)         // Wait until finger detected
        {
                delay_ms(50);        // Small delay
        }

        // CAPTURE FINGERPRINT
        ret = Genimg();              // Capture fingerprint image

        if(ret != 0)                 // Check capture status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Gen Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        // CONVERT IMAGE INTO TEMPLATE BUFFER1
        ret = img2tp1();             // Convert image into template

        if(ret != 0)                 // Check conversion status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Tz Fail");  // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        // LOAD STORED TEMPLATE INTO BUFFER2
        ret = load_char(id);         // Load stored fingerprint template

        if(ret != 0)                 // Check load status
        {
                cmd_lcd(0x01);       // Clear LCD

                str_lcd("Load Fail"); // Display error message

                delay_ms(500);       // Delay

                return 1;            // Return failure
        }

        // MATCH BOTH TEMPLATES
        ret = match();               // Compare fingerprint templates

        if(ret == 0)                 // Check match status
        {
                return 0;            // Return success
        }

        else
        {
                return 1;            // Return failure
        }
}

