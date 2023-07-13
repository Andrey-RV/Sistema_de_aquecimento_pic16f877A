#include <pic16f877a.h>
#include <xc.h>
#include "i2c.h"

static void i2c_WaitForIdle();
static void i2c_Ack();
static void i2c_NoAck();


void I2C_Restart()
{
	RSEN = 1;
	while(RSEN);
}

void I2C_Init()
{
	SCL_Direction = 0x01;
	SDA_Direction = 0x01;

	SSPSTAT |= 0x80;  /* Slew rate disabled */
	SSPCON = 0x28;    /* SSPEN = 1, I2C Master mode, clock = FOSC/(4 * (SSPADD + 1)) */
	// SSPADD = 50;   /* 100Khz @ 20Mhz Fosc */
	SSPADD = 19;	  /* 8Mhz Fosc */
}

void I2C_Start()
{
	SEN = 1;
	while(SEN == 1);

}

void I2C_Stop(void)
{
	PEN = 1;
	while(PEN == 1);
}

void I2C_Write(unsigned char data)
{
    SSPBUF = data;
    while(BF==1);
    i2c_WaitForIdle();
}

unsigned char I2C_Read(unsigned char acknowledge)
{
	unsigned char  data=0x00;

	RCEN = 1;                   /* Enable data reception */
	while(BF==0);               /* wait for data to be received */
	data = SSPBUF;              /* copy the received data */
	i2c_WaitForIdle();          /* wait till current operation is complete*/
	      
	if(acknowledge==1)          /*Send the Ack/NoAck depending on the user option*/
	{
		i2c_Ack();
	}
	else
	{
		i2c_NoAck();
	}

	return data;       /* Finally return the received Byte */
}

static void i2c_WaitForIdle()
{
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    /* wait till I2C module completes previous operation and becomes idle */
}								

static void i2c_Ack()
{
	ACKDT = 0;            /* Acknowledge data bit, 0 = ACK */
	ACKEN = 1;            /* Ack data enabled */
	while(ACKEN == 1);    /* wait for ack data to send on bus */
}

static void i2c_NoAck()
{
	ACKDT = 1;            /* Acknowledge data bit, 1 = NAK/NoAK */
	ACKEN = 1;            /* Ack data enabled */
	while(ACKEN == 1);    /* wait for ack data to send on bus */
}
