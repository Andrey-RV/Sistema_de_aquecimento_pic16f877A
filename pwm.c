#include <xc.h>
#include <pic16f877a.h>
#include "pwm.h"


void pwm_init(void) {
    TRISCbits.TRISC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;      // PWM mode
    CCPR2L = 0b00000000;             // PWM duty cycle = CCPR2L : CCP2X : CCP2Y
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    PR2 = 199;                       // 2.5kHz PWM frequency (for a 8MHz Fosc) 
    T2CON = 0b00000101;              // Timer 2 prescaler 1:4
}

void change_pwm_duty_cycle(unsigned int temperature) {
    switch (temperature){
        case 30:
            CCPR2L = 0b00000000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 34:
            CCPR2L = 0b00010100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 38:
            CCPR2L = 0b00101000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 42:
            CCPR2L = 0b00111100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 46:
            CCPR2L = 0b01010000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 50:
            CCPR2L = 0b01100100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 54:
            CCPR2L = 0b01111000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 58:
            CCPR2L = 0b10001100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 62:
            CCPR2L = 0b10100000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 66:
            CCPR2L = 0b10110100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
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