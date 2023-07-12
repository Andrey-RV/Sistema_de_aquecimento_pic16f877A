#include <xc.h>
#include <pic16f877a.h>

void pwn_init(void);
void change_pwm_duty_cycle(unsigned char new_percentage);


void pwm_init(void) {
    TRISCbits.TRISC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;     // PWM mode
    CCPR2L = 0b00000000;           // PWM duty cycle = CCPR2L : CCP2X : CCP2Y
    CCP2CONbits.CCP2X = 0;
    CCP2CONbits.CCP2Y = 0;

    PR2 = 199;                       // 2.5kHz PWM frequency (for a 8MHz Fosc) 
    T2CON = 0b00000101;             // Timer 2 prescaler 1:4
}

void change_pwm_duty_cycle(unsigned char new_percentage) {
    switch (new_percentage){
        case 0:
            CCPR2L = 0b00000000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 10:
            CCPR2L = 0b00010100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 20:
            CCPR2L = 0b00101000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 30:
            CCPR2L = 0b00111100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 40:
            CCPR2L = 0b01010000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 50:
            CCPR2L = 0b01100100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 60:
            CCPR2L = 0b01111000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 70:
            CCPR2L = 0b10001100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 80:
            CCPR2L = 0b10100000;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
        case 90:
            CCPR2L = 0b10110100;
            CCP2CONbits.CCP2X = 0;
            CCP2CONbits.CCP2Y = 0;
            break;
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