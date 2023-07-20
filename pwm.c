#include <xc.h>
#include <pic16f877a.h>
#include <stdlib.h>
#include "pwm.h"
#include "ad_converter.h"
#include "main.h"


void pwm_init(void) {
    TRISCbits.TRISC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;      // PWM mode
    CCPR2L = 0b00000000;             // PWM duty cycle = CCPR2L : CCP2X : CCP2Y
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    PR2 = 199;                       // 2.5kHz PWM frequency (for a 8MHz Fosc) 
    T2CON = 0b00000101;              // Timer 2 prescaler 1:4
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
    else{
        turn_off_fan();
    }
}

void change_pwm_duty_cycle(unsigned int temperature) {
    switch (temperature){
        case 70:
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