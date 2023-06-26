#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#include <xc.h>
#include <pic16f877a.h>
#include "lcd.h"
#include "keypad.h"

#define _XTAL_FREQ 8000000


void __interrupt() isr(void) {

}

void main(void) {

    unsigned char temp = 0;


    initialize_lcd();
    keypad_init();
    
    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura:");
    __delay_ms(2000);

    do
    {
        unsigned char key_pressed = scan_keypad();
        clear_lcd();
        set_cursor(1, 1);
        __delay_ms(100);
        write_char(key_pressed);
        __delay_ms(100);
    } while (temp == 0);
    

    while (1);

    return;
}