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


void get_aimed_temperature();
void get_heating_time();
void set_heating(char* temperature);
void set_timer(char* time);


void main() {
    initialize_lcd();
    keypad_init();
    get_aimed_temperature();
    __delay_ms(2000);
    get_heating_time();
    
    while (1);

    return;
}

void get_aimed_temperature(){
    const unsigned char* temperatures[] = {"10", "20", "30", "40" ,"50"};
    char n = 0;
    unsigned char key_pressed = 'n';

    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura: 10 ");

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
            default:
                break;
        }
        if (key_pressed == 'E') {
            break;
        }
    }
    clear_lcd();
    set_cursor(1, 1);
    write_string("Temperatura");
    set_cursor(2, 1);
    write_string("escolhida: ");
    write_string(temperatures[n]);
}

void get_heating_time(){
    const unsigned char* time_intervals[] = {"10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60"};
    char n = 4;
    unsigned char key_pressed = 'n';

    clear_lcd();
    set_cursor(1, 1);
    write_string("Tempo de");
    set_cursor(2, 1);
    write_string("aquecimento: ");
    set_cursor(2, 14);
    write_string(time_intervals[4]);

    while (1) {
        key_pressed = scan_keypad();

        switch (key_pressed){
            case 'A':
                n = n == 10 ? 10 : n + 1;
                set_cursor(2, 14);
                write_string(time_intervals[n]);
                break;
            case 'D':
                n = n == 0 ? 0 : n - 1;
                set_cursor(2, 14);
                write_string(time_intervals[n]);
                break;
            default:
                break;
        }
        if (key_pressed == 'E') {
            break;
        }
    }
    clear_lcd();
    set_cursor(1, 1);
    write_string("Tempo");
    set_cursor(2, 1);
    write_string("escolhido: ");
    write_string(time_intervals[n]);
}