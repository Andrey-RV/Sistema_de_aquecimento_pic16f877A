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


unsigned char* get_aimed_temperature();


void main() {
    initialize_lcd();
    keypad_init();

    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura: 10 ");
    unsigned char* chosen_temperature = get_aimed_temperature();

    clear_lcd();
    set_cursor(1, 1);
    write_string("Temperatura");
    set_cursor(2, 1);
    write_string("escolhida: ");
    write_string(chosen_temperature);
    
    while (1);

    return;
}

unsigned char* get_aimed_temperature(){
    const unsigned char* temperatures[] = {"10", "20", "30", "40" ,"50"};
    char n = 0;
    unsigned char key_pressed = 'n';

    while (1) {
        key_pressed = scan_keypad();

        switch (key_pressed){
            case 'A':
                n = n == 4 ? 4 : n + 1;
                set_cursor(2, 14);
                write_string(temperatures[n]);
                break;
            case 'D':
                n = n == 0 ? 0 : n - 1;
                set_cursor(2, 14);
                write_string(temperatures[n]);
                break;
            case 'E':
                return temperatures[n];
                break;
        }
    }
}
