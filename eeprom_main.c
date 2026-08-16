#include<lpc21xx.h>
#include"i2c.h"
#include"i2c_eeprom.h"
#include"lcd.h"
#include"delay.h"

char usr_id[][5]={"1111","2222","3333","4444"};
char usr_pass[][5]={"5555","6666","7777","8888"};
char rd_usr_id[5];

int main()
{
	int i;
	init_lcd();
	init_i2c();
	str_lcd("USER ID'S:");
	for(i=0;i<4;i++)
	{
		i2c_eeprom_write_page(0x50,0x0000+(i*5),usr_id[i],4);
		delay_ms(100);
	}
	for(i=0;i<4;i++)
	{
		i2c_eeprom_seq_read(0x50,0x0000+(i*5),rd_usr_id,4);
		cmd_lcd(0xC0);
		str_lcd((u8 *)rd_usr_id);
		delay_ms(1000);
	}
	cmd_lcd(0x01);
	str_lcd("USER PASS:");
	for(i=0;i<4;i++)
	{
		i2c_eeprom_write_page(0x50,0x0020+(i*5),usr_pass[i],4);
		delay_ms(100);
	}
	for(i=0;i<4;i++)
	{
		i2c_eeprom_seq_read(0x50,0x0020+(i*5),rd_usr_id,4);
		cmd_lcd(0xC0);
		str_lcd((u8 *)rd_usr_id);
		delay_ms(1000);
	}
	while(1);
}