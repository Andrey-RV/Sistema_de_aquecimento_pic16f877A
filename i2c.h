#include <pic16f877a.h>
#include <xc.h>


#define SCL RC3
#define SDA RC4
#define SCL_Direction TRISC3
#define SDA_Direction TRISC4
#define _XTAL_FREQ 8000000


void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(unsigned char );
unsigned char I2C_Read(unsigned char);