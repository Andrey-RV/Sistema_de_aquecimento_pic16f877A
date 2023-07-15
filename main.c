#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f877a.h>
#include "lcd4.h"
#include "keypad.h"
#include "ad_converter.h"
#include "pwm.h"
#include "main.h"


long int timer_counter = 0;         // TMR1 is set to count up to 0.25s, so 4 interrupts are 1s


void __interrupt() isr(void){
    if (PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        timer_counter--;

        if (timer_counter % 4 == 0){
            show_temp_and_time();
            if (timer_counter == 0){
                PIE1bits.TMR1IE = 0;
            }
        }
    }
}

void main(void) {
    unsigned char* chosen_temperature;
    unsigned char* chosen_time;

    initial_setup();
    chosen_temperature = get_aimed_temperature();
    __delay_ms(1500);
    chosen_time = get_heating_time();
    __delay_ms(1500);
    set_heating(chosen_temperature);
    set_timer(chosen_time);

    while (1);

    return;
}

void initial_setup(void){
    initialize_lcd();
    keypad_init();
    ad_init();
    pwm_init();
}

unsigned char* get_aimed_temperature(void){
    const unsigned char* temperatures[] = {"10", "20", "30", "40" ,"50"};
    unsigned char n = 0;
    unsigned char key_pressed = 'n';

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
    display_aimed_temperature(temperatures[n]);
    return temperatures[n];
}

void display_aimed_temperature(const unsigned char* temperature){
    clear_lcd();
    write_string("Temperatura");
    set_cursor(2, 1);
    write_string("escolhida: ");
    write_string(temperature);
}

unsigned char* get_heating_time(void){
    const unsigned char* time_intervals[] = {"10", "15", "20", "25", "30", "35", "40", "45", "50", "55", "60"};
    unsigned char n = 4;
    unsigned char key_pressed = 'n';

    clear_lcd();
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
    display_heating_time(time_intervals[n]);
    return time_intervals[n];
}

void display_heating_time(const unsigned char* time){
    clear_lcd();
    write_string("Tempo");
    set_cursor(2, 1);
    write_string("escolhido: ");
    write_string(time);
}

void set_heating(const unsigned char* temperature){
    if (temperature == "10"){
        change_pwm_duty_cycle(10);
    }
    else if (temperature == "20"){
        change_pwm_duty_cycle(20);
    }
    else if (temperature == "30"){
        change_pwm_duty_cycle(30);
    }
    else if (temperature == "40"){
        change_pwm_duty_cycle(40);
    }
    else if (temperature == "50"){
        change_pwm_duty_cycle(50);
    }
    else if (temperature == "60"){
        change_pwm_duty_cycle(60);
    }
    else if (temperature == "70"){
        change_pwm_duty_cycle(70);
    }
    else if (temperature == "80"){
        change_pwm_duty_cycle(80);
    }
    else if (temperature == "90"){
        change_pwm_duty_cycle(90);
    }
    else if (temperature == "100"){
        change_pwm_duty_cycle(100);
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
    INTCONbits.GIE = 1;
}

void show_temp_and_time(void){
    unsigned char str_current_temp[3];
    unsigned char str_current_time[3];
    unsigned int int_current_temp = read_ad();

    sprintf(str_current_temp, "%d", int_current_temp);
    sprintf(str_current_time, "%ld", timer_counter / 4);
    clear_lcd();
    write_string(str_current_temp);
    write_string("C");
    set_cursor(2, 1);
    if (timer_counter == 0){
        clear_lcd();
        write_string("Aquecimento");
        set_cursor(2, 1);
        write_string("terminado!");
        return;
    }
    write_string(str_current_time);
    write_string("s");
}