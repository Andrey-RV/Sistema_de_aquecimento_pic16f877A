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


void main(void) {
    const unsigned char* temperatures[] = {"10", "20", "30", "40" ,"50"};
    unsigned char n = 0;
    unsigned char key_pressed = 'n';


    initialize_lcd();
    keypad_init();
    
    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura: 10 ");

    while (1) {
        key_pressed = scan_keypad();

        if (key_pressed == 'A') {
            n++;
            if (n > 4) {
                n = 0;
            }
        }
        else if (key_pressed == 'D') {
            n--;
            if (n < 0) {
                n = 0;
            }
        }

        set_cursor(2, 14);
        write_string(temperatures[n]);
        __delay_ms(100);

        if (key_pressed == 'E') {
            break;
        }   
        // else if (key_pressed == 'C'){
            
        // }
    }
    
    clear_lcd();
    set_cursor(1, 1);
    write_string("Temperatura");
    set_cursor(2, 1);
    write_string("escolhida: ");
    write_string(temperatures[n]);
    
    while (1);

    return;
}