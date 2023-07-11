#include <xc.h>
#include <pic16f877a.h>

void pwm_setup(void);


void pwm_setup(void){
    TRISCbits.TRISC2 = 0; // RC2 as output
    PR2 = 0b11111111; // Period register
    CCPR1L = 0b00000000; // Duty cycle register
    CCP1CONbits.CCP1M = 0b00001100; // PWM mode
    T2CONbits.T2CKPS = 0b11; // Prescaler 1:16
    T2CONbits.TMR2ON = 1; // Timer 2 on
}