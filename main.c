/* 
TODO: FIXME: Though it shouldn't, pressing RB0 while selecting temperature or time is causing the program to freeze. Calling keypad_init() again fixes it, but it's not a good solution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <xc.h>
#include <pic16f877a.h>
#include "lcd4.h"
#include "keypad.h"
#include "ad_converter.h"
#include "pwm.h"
#include "main.h"


unsigned int timer_counter = 0;
unsigned char* chosen_temperature = NULL;
bool heating_was_cancelled = false;
bool is_heating = false;


void __interrupt() isr(void){
    if (PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        timer_counter--;

        if (timer_counter % 4 == 0){
            show_temp_and_time();
        }
    }

    if (INTCONbits.INTF){
        INTCONbits.INTF = 0;
        T1CONbits.TMR1ON = 0;
        change_pwm_duty_cycle(0);
        set_cursor(2, 8);
        write_string(" Parado! ");

        unsigned char key_pressed = scan_keypad();
        switch (key_pressed){
            case 'E':
                T1CONbits.TMR1ON = 1;
                set_heating(chosen_temperature);
                break;
            case 'C':
                heating_was_cancelled = true;
                break;
            default:
                break;
        }
    }
}

void main(void) {
    unsigned char* chosen_time = NULL;
    initial_setup();

    while (true){
        chosen_temperature = get_aimed_temperature();
        chosen_time = get_heating_time();
        set_heating(chosen_temperature);
        set_timer(chosen_time);

        is_heating = true;
        INTCONbits.INTE = 1;
        INTCONbits.GIE = 1;

        while (is_heating){
            adjust_pwm_duty_cycle(chosen_temperature);
            if (timer_counter == 0 || heating_was_cancelled){
                end_heating();
            }
        }
    }
    return;
}

void initial_setup(void){
    initialize_lcd();
    keypad_init();
    ad_init();
    pwm_init();
    OPTION_REGbits.INTEDG = 0;      // Interrupt on falling edge of RB0/INT pin
}

unsigned char* get_aimed_temperature(void){
    const unsigned char* temperatures[] = {"30", "34", "38", "42", "46", "50", "54", "58", "62", "66", "70"};
    unsigned char n = 0;
    unsigned char key_pressed = 'n';

    clear_lcd();
    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura: ");
    set_cursor(2, 14);
    write_string(temperatures[0]);
    write_string("C");

    while (true) {
        key_pressed = scan_keypad();

        switch (key_pressed){
            case 'A':
                n = n == 10 ? 10 : n + 1;         // Make sure the index doesn't go out of bounds
                set_cursor(2, 14);
                write_string(temperatures[n]);
                write_string("C");
                break;
            case 'D':
                n = n == 0 ? 0 : n - 1;
                set_cursor(2, 14);
                write_string(temperatures[n]);
                write_string("C");
                break;
            default:
                break;
        }
        if (key_pressed == 'E') {
            break;
        }
    }
    display_aimed_temperature(temperatures[n]);
    __delay_ms(1500);
    return temperatures[n];
}

void display_aimed_temperature(const unsigned char* temperature){
    clear_lcd();
    write_string("Temperatura");
    set_cursor(2, 1);
    write_string("escolhida: ");
    write_string(temperature);
    write_string("C");
}

unsigned char* get_heating_time(void){
    const unsigned char* time_intervals[] = {"30", "60", "90", "120", "150", "180", "210", "240", "270", "300"};
    unsigned char n = 0;
    unsigned char key_pressed = 'n';
    unsigned char* formatted_time = NULL;

    clear_lcd();
    write_string("Aquecer por:");
    set_cursor(2, 1);
    write_string(format_time(time_intervals[0]));

    while (1) {
        key_pressed = scan_keypad();

        switch (key_pressed){
            case 'A':
                n = n == 9 ? 9 : n + 1;           // Make sure the index doesn't go out of bounds
                set_cursor(2, 1);
                write_string(format_time(time_intervals[n]));
                break;
            case 'D':
                n = n == 0 ? 0 : n - 1;
                set_cursor(2, 1);
                write_string(format_time(time_intervals[n]));
                break;
            default:
                break;
        }
        if (key_pressed == 'E') {
            break;
        }
    }
    display_heating_time(time_intervals[n]);
    __delay_ms(1500);
    return time_intervals[n];
}

void display_heating_time(const unsigned char* time){
    clear_lcd();
    write_string("Tempo");
    set_cursor(2, 1);
    write_string("escolhido: ");
    set_cursor(2, 12);
    write_string(format_time(time));
}

unsigned char* format_time(const unsigned char* seconds){
    unsigned char formatted_time[5];
    unsigned int int_seconds = strtol(seconds, NULL, 10);
    unsigned int int_minutes = int_seconds / 60;
    unsigned int int_seconds_left = int_seconds % 60;
    sprintf(formatted_time, "%d:%d", int_minutes, int_seconds_left);
    return formatted_time;
}

void set_heating(const unsigned char* temperature){
    unsigned int current_temperature = read_ad();

    if (current_temperature < strtol(temperature, NULL, 10)){
        change_pwm_duty_cycle(70);
    }
    else {
        change_pwm_duty_cycle(0);
    }
}

void set_timer(const unsigned char* time){
    timer_counter = 4 * strtol(time, NULL, 10);

    T1CON = 0b00110001;                 // 1:8 prescaler, 16-bit timer, internal clock, no sync
    TMR1 = 62500;                       // 0.25s

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
}

void show_temp_and_time(void){
    unsigned char str_current_temp[17];
    unsigned char str_current_time[4];
    unsigned int int_current_temp = read_ad();

    sprintf(str_current_temp, "Temperatura: %dC", int_current_temp);
    sprintf(str_current_time, "%d", timer_counter / 4);

    clear_lcd();
    write_string(str_current_temp);
    set_cursor(2, 1);
    if (timer_counter == 0){
        clear_lcd();
        write_string("Aquecimento");
        set_cursor(2, 1);
        write_string("terminado!");
        return;
    }
    write_string(format_time(str_current_time));
    set_cursor(2, 8);
    write_string("Aquecendo");
}

void end_heating(void){
    is_heating = false;
    PIE1bits.TMR1IE = 0;
    INTCONbits.INTE = 0;
    change_pwm_duty_cycle(0);
    clear_lcd();
    write_string("Aquecimento");
    set_cursor(2, 1);
    write_string("terminado!");
    __delay_ms(2000);
}
