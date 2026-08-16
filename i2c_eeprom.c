//i2c_eeprom.c
#include"delay.h"
#include"types.h"
#include"i2c.h"
void i2c_eeprom_write_byte(u8 slaveAddr,u16 wBuffAddr,u8 dat)
{
	//issue start condition to begin this frame
	i2c_start();
	//issue 7bit SA+W option
	i2c_write(slaveAddr<<1);
	//issue buffer address for writing
	i2c_write(wBuffAddr>>8);
	i2c_write(wBuffAddr);
	//issue data for that write buffer
	i2c_write(dat);
	//issue stop condition to end this frame
	i2c_stop();
	//delay period between consecutive writes
	delay_ms(10);
}
u8 i2c_eeprom_read_byte(u8 slaveAddr,u16 rBuffAddr)
{
	u8 dat;
	//issue start condition 
	i2c_start();
	//issue SA+W option 
	i2c_write(slaveAddr<<1);
	//issue Address of buffer to be read
	i2c_write(rBuffAddr>>8);
	i2c_write(rBuffAddr);
	//issue re start condition
	i2c_restart();
	//issue SA+R option
	i2c_write((slaveAddr<<1)|1);
	//give not of ack after reading only/last byte
	dat=i2c_nack();
	//issue stop condition
	i2c_stop();
	//return read byte
	return dat;
}
void i2c_eeprom_write_page(u8 slaveAddr,u16 wBuffStartAddr,s8 *p,u8 nBytes)
{
	int i;
	i2c_start();
	i2c_write(slaveAddr<<1);
	i2c_write(wBuffStartAddr>>8);
	i2c_write(wBuffStartAddr);
	for(i=0;i<nBytes;i++)
	{
		i2c_write(p[i]);
	}
	i2c_stop();
	delay_ms(10);
}
void i2c_eeprom_seq_read(u8 slaveAddr,u16 rBuffStartAddr, s8 *p,u8 nBytes)
{
	u8 i;
	i2c_start();
	i2c_write(slaveAddr<<1);
	i2c_write(rBuffStartAddr>>8);
	i2c_write(rBuffStartAddr);
	i2c_restart();
	i2c_write(slaveAddr<<1|1);
	for(i=0;i<(nBytes-1);i++)
	{
		p[i]=i2c_mack();
	}
	p[i]=i2c_nack();
	p[i+1]='\0';
	i2c_stop();
}
