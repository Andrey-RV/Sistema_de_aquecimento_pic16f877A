#define EN PORTEbits.RE0
#include <xc.h>
#include <pic16f877a.h>

#define RS PORTEbits.RE1
#define data_bus PORTD
#define _XTAL_FREQ 8000000


void write_on_lcd_bus(char a);
void send_lcd_command(char a);
void clear_lcd();
void set_cursor(char a, char b);
void initialize_lcd();
void write_char(char a);
void write_string(char *a);


void write_on_lcd_bus(char a)
{
    data_bus = a;
}

void send_lcd_command(char a)
{
    RS = 0;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

void clear_lcd()
{
    send_lcd_command(0x01);     // Clear display command
    send_lcd_command(0x02);     // Return home command
}

void set_cursor(char a, char b)
{
    char temp;
    if (a == 1)
        temp = 0x80 + b - 1;    // 0x80 command moves the cursor to the start of the first line
    else if (a == 2)
        temp = 0xC0 + b - 1;    // 0xC0 command moves the cursor to the start of the second line
    send_lcd_command(temp);
}

void initialize_lcd()
{
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1 = 0x06;

    send_lcd_command(0x38);     // Set 2 lines and 5x7 matrix command
    __delay_ms(5);
    send_lcd_command(0x0E);     // Display on, cursor blinking command
    __delay_ms(5);
    send_lcd_command(0x01);     // Clear display command  
    __delay_ms(5);
    send_lcd_command(0x06);     // Increment cursor command
    __delay_ms(5);
}

void write_char(char a)
{
    RS = 1;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void write_string(char* a)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
        write_char(a[i]);
}
