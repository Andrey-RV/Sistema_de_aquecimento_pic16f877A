#include <xc.h>
#include <pic16f877a.h>
#include "keypad.h"


void keypad_init(void){
    OPTION_REGbits.nRBPU = 0;
    TRISB = 0b11110011;

    return;
}

unsigned char scan_keypad(void){

    while (1){
        row1 = 0;
        row2 = 1;

        if (PORTBbits.RB4 == 0){
            __delay_ms(150);
            if (PORTBbits.RB4 == 0){
                return 'A';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(150);
            if (PORTBbits.RB5 == 0){
                return 'D';
        }
        }

        row1 = 1;
        row2 = 0;

        if (PORTBbits.RB4 == 0){
            __delay_ms(150);
            if (PORTBbits.RB4 == 0){
                return 'E';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(150);
            if (PORTBbits.RB5 == 0){
                return 'C';
        }
        }
    }
}