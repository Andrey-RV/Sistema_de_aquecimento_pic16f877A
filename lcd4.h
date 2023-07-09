#include <xc.h>
#include <pic16f877a.h>

#define EN PORTEbits.RE0
#define RS PORTEbits.RE1
#define data_bus PORTD
#define _XTAL_FREQ 8000000

void write_on_lcd_bus(char a);
void send_lcd_command(char a);
void clear_lcd(void);
void set_cursor(char a, char b);
void initialize_lcd();
void write_char(char a);
void write_string(const char* a);


void write_on_lcd_bus(char a)
{
    data_bus = a << 4;
}

void send_lcd_command(char a)
{
    RS = 0;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(1);
    EN = 0;
}

void clear_lcd(void)
{
    send_lcd_command(0x00);     // Clear display command part 1
    __delay_ms(2);
    send_lcd_command(0x01);      // Clear display command part 2
    __delay_ms(2);
    send_lcd_command(0x00);     // Return home command part 1
    __delay_ms(2);
    send_lcd_command(0x02);     // Return home command part 2
}

void set_cursor(char a, char b)
{
    char position, position_high, position_low;
    if (a == 1){
        position = 0x80 + b - 1;    // 0x80 command moves the cursor to the start of the first line
        position_high = position & 0xF0;
        position_low = position & 0x0F;
        send_lcd_command(position_high >> 4);
        send_lcd_command(position_low);      
    }  
    else if (a == 2){
        position = 0xC0 + b - 1;    // 0xC0 command moves the cursor to the start of the second line
        position_high = position & 0xF0;
        position_low = position & 0x0F;
        send_lcd_command(position_high >> 4);
        send_lcd_command(position_low);
    }
}

void initialize_lcd()
{
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1 = 0x06;
    PORTD = 0x00;

    __delay_ms(20);
    send_lcd_command(0x02);     // 4 bit mode command part 1
    __delay_ms(20);
    send_lcd_command(0x02);     // 4 bit mode command part 1
    __delay_ms(2);
    send_lcd_command(0x08);     // 4 bit mode command part 2
    __delay_ms(2);
    send_lcd_command(0x00);     // Display on, cursor blinking command part 1
    __delay_ms(2);
    send_lcd_command(0x0E);     // Display on, cursor blinking command part 2
    __delay_ms(2);
    send_lcd_command(0x00);     // Return home command part 1
    __delay_ms(2);
    send_lcd_command(0x02);     // Return home command part 2
    __delay_ms(2);
    send_lcd_command(0x00);     // Clear display command part 1
    __delay_ms(2);
    send_lcd_command(0x01);     // Clear display command part 2 
    __delay_ms(2);
    send_lcd_command(0x00);     // Increment cursor command part 1
    __delay_ms(2);
    send_lcd_command(0x06);     // Increment cursor command part 2
    __delay_ms(2);
}

void write_char(char a)
{
    char lower_nibble = a & 0x0F;
    char higher_nibble = a & 0xF0;

    RS = 1;
    write_on_lcd_bus(higher_nibble >> 4);
    EN = 1;
    __delay_us(1);
    EN = 0;

    write_on_lcd_bus(lower_nibble);
    EN = 1;
    __delay_us(1);
    EN = 0;
}

void write_string(const char* a)
{
    int i;
    for (i = 0; a[i] != '\0'; i++)
        write_char(a[i]);
}
