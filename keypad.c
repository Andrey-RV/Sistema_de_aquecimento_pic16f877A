#include <xc.h>
#include <pic16f877a.h>
#include "keypad.h"


void keypad_init(void){
    OPTION_REGbits.nRBPU = 0;           //* Pull-ups internos habilitados
    TRISB = 0b11110011;                 //* RB3:RB2 como saída, restante como entrada
    return;
}

unsigned char scan_keypad(void){
    while (1){
        row1 = 0;
        row2 = 1;

        if (PORTBbits.RB4 == 0){
            __delay_ms(150);            //* Debounce
            if (PORTBbits.RB4 == 0){
                return INCREASE_BUTTON;
        }
        }

        if (PORTBbits.RB5 == 0){        
            __delay_ms(150);            //* Debounce
            if (PORTBbits.RB5 == 0){
                return DECREASE_BUTTON;
        }
        }

        row1 = 1;
        row2 = 0;

        if (PORTBbits.RB4 == 0){
            __delay_ms(150);            //* Debounce
            if (PORTBbits.RB4 == 0){
                return ENTER_BUTTON;
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(150);            //* Debounce
            if (PORTBbits.RB5 == 0){
                return CANCEL_BUTTON;
        }
        }
    }
}