#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#include <stdio.h>
#include <xc.h>
#include <pic16f877a.h>
#include "lcd4.h"
#include "keypad.h"
#include "pwm.h"
#include "ad_converter.h"
#include "rtc.h"

#define _XTAL_FREQ 8000000

void get_aimed_temperature(void);
void get_heating_time(void);
void set_heating(char temperature);
void set_timer(char time);


void main(void) {
    char str_temperature[3];
    char seconds[3];
    unsigned int int_temperature = 0;
    rtc real_time_clock;

    initialize_lcd();
    keypad_init();
    ad_init();
    pwm_init();
    change_pwm_duty_cycle(100);
    
    get_aimed_temperature();
    __delay_ms(2000);
    get_heating_time();

    // RTC_Init();
    // real_time_clock.hour = 0x21;
    // real_time_clock.min = 0x25;
    // real_time_clock.sec = 0x00;
    // real_time_clock.date = 0x12;
    // real_time_clock.month = 0x07;
    // real_time_clock.year = 0x23;
    // real_time_clock.weekDay = 0x03;
    // RTC_SetDateTime(&real_time_clock);

    // while (1){
    //     RTC_GetDateTime(&real_time_clock);
    //     sprintf(seconds, "%d", real_time_clock.sec);
    //     clear_lcd();
    //     write_string(seconds);
    //     __delay_ms(5000);
    // }

    while (1){
        __delay_ms(1000);
        int_temperature = read_ad();
        sprintf(str_temperature, "%d", int_temperature);
        clear_lcd();
        write_string(str_temperature);
        write_string("C");
    }

    return;
}

void get_aimed_temperature(void){
    const char* temperatures[] = {"10", "20", "30", "40" ,"50"};
    char n = 0;
    char key_pressed = 'n';

    write_string("Escolha a");
    set_cursor(2, 1);
    write_string("temperatura: 10 ");

    while (1) {
        key_pressed = scan_keypad();

        switch (key_pressed){
            case 'A':
                n = n == 4 ? 4 : n + 1;         // Make sure the index doesn't go out of bounds
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

void get_heating_time(void){
    const char* time_intervals[] = {"10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60"};
    char n = 4;
    char key_pressed = 'n';

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
                n = n == 10 ? 10 : n + 1;           // Make sure the index doesn't go out of bounds
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