#include <xc.h>
#include <pic16f877a.h>
#include <stdlib.h>
#include "pwm.h"
#include "ad_converter.h"
#include "main.h"


void pwm_init(void) {
    TRISCbits.TRISC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;      //* Modo PWM
    CCPR2L = 0b00000000;             //* Duty cycle do PWM = CCPR2L:CCP2X:CCP2Y
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    PR2 = 199;                       //* Frequência de 2.5kHz para um oscilador de 8MHz 
    T2CON = 0b00000101;              //* Prescaler de 4 para o timer 2
}

void adjust_pwm_duty_cycle(char* temperature){
    unsigned int chosen_temperature = strtol(temperature, NULL, 10);
    unsigned int current_temperature = read_ad();

    if (current_temperature < chosen_temperature && CCPR2L < 255){
        CCPR2L++;
        turn_off_fan();
    } else if (current_temperature > chosen_temperature && CCPR2L > 0){
        CCPR2L--;
        turn_on_fan();
    }
    else if (current_temperature == chosen_temperature){
        turn_off_fan();
    }
}

void change_pwm_duty_cycle(unsigned int percentage) {
    switch (percentage){
        case 100:
            CCPR2L = 0b11001000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        default:
            CCPR2L = 0b00000000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
    }    
}