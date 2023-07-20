#include <xc.h>
#include <pic16f877a.h>
#include "lcd4.h"


void write_on_lcd_bus(unsigned char a)
{
    data_bus = a << 4;
}

void send_lcd_command(unsigned char a){
    RS = 0;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(2);
}

void send_data(unsigned char a){
    RS = 1;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(2);
}

void initialize_lcd(void){
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1 = 0x06;
    PORTD = 0x00;

    __delay_ms(20);
    send_lcd_command(0x02);     // 4 bit mode command part 1
    __delay_ms(20);
    send_lcd_command(0x02);     // Sent twice to ensure command is received
    send_lcd_command(0x08);     // 4 bit mode command part 2
    send_lcd_command(0x00);     // Display on, cursor off command part 1
    send_lcd_command(0x0C);     // Display on, cursor off command part 2
    clear_lcd();
}

void clear_lcd(void){
    send_lcd_command(0x00);     // Clear display command part 1
    send_lcd_command(0x01);     // Clear display command part 2
    send_lcd_command(0x00);     // Return home command part 1
    send_lcd_command(0x02);     // Return home command part 2
    set_cursor(1, 1);
}

void set_cursor(unsigned char a, unsigned char b){
    unsigned char position, position_high, position_low;
    if (a == 1){
        position = 0x80 + b - 1;            // 0x80 command moves the cursor to the start of the first line
        position_high = position & 0xF0;
        position_low = position & 0x0F;
        send_lcd_command(position_high >> 4);
        send_lcd_command(position_low);      
    }  
    else if (a == 2){
        position = 0xC0 + b - 1;            // 0xC0 command moves the cursor to the start of the second line
        position_high = position & 0xF0;
        position_low = position & 0x0F;
        //Data is shifted to the left in write_on_lcd_bus() because it expects the data to be in the lower nibble, thus, higher nibble needs to be shifted to the right before being sent
        send_lcd_command(position_high >> 4);
        send_lcd_command(position_low);
    }
}

void write_char(unsigned char a){
    unsigned char lower_nibble = a & 0x0F;
    unsigned char higher_nibble = a & 0xF0;

    //Data is shifted to the left in write_on_lcd_bus() because it expects the data to be in the lower nibble, thus, higher nibble needs to be shifted to the right before being sent
    send_data(higher_nibble >> 4);
    send_data(lower_nibble);
}

void write_string(const unsigned char* a){
    unsigned char i;
    for (i = 0; a[i] != '\0'; i++)
        write_char(a[i]);
}
