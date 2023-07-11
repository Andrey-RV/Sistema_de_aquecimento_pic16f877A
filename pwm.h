#include <xc.h>
#include <pic16f877a.h>

void turn_on_pwm(void);


void turn_on_pwm(void) {
    TRISCbits.TRISC1 = 0;
    CCP2CONbits.CCP2M = 0b1100;     // PWM mode
    CCPR2L = 0b00111110;            // PWM duty cycle = CCPR2L : CCP2X : CCP2Y
    CCP2CONbits.CCP2X = 1;
    CCP2CONbits.CCP2Y = 0;

    PR2 = 124;                      // 1kHz PWM frequency (for a 8MHz Fosc) 
    T2CON = 0b00000111;             // Timer 2 prescaler 1:16
}