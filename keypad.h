#include <xc.h>
#include <pic16f877a.h>

#define row1 PORTBbits.RB0
#define row2 PORTBbits.RB1
#define row3 PORTBbits.RB2
#define row4 PORTBbits.RB3


void keypad_init(void){
    OPTION_REGbits.nRBPU = 0;
    TRISB = 0xf0;
    PORTB = 0b11110000;

    return;
}

unsigned char scan_keypad(void){

    while (1){
        row1 = 0;
        row2 = 1;
        row3 = 1;
        row4 = 1;

        if (PORTBbits.RB4 == 0){
            __delay_ms(100);
            if (PORTBbits.RB4 == 0){
                return '1';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(100);
            if (PORTBbits.RB5 == 0){
                return '2';
        }
        }

        if (PORTBbits.RB6 == 0){
            __delay_ms(100);
            if (PORTBbits.RB6 == 0){
                return '3';
        }
        }

        if (PORTBbits.RB7 == 0){
            __delay_ms(100);
            if (PORTBbits.RB7 == 0){
                return 'A';
        }
        }

        row1 = 1;
        row2 = 0;
        row3 = 1;
        row4 = 1;

        if (PORTBbits.RB4 == 0){
            __delay_ms(100);
            if (PORTBbits.RB4 == 0){
                return '4';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(100);
            if (PORTBbits.RB5 == 0){
                return '5';
        }
        }

        if (PORTBbits.RB6 == 0){
            __delay_ms(100);
            if (PORTBbits.RB6 == 0){
                return '6';
        }
        }

        if (PORTBbits.RB7 == 0){
            __delay_ms(100);
            if (PORTBbits.RB7 == 0){
                return 'B';
        }
        }

        row1 = 1;
        row2 = 1;
        row3 = 0;
        row4 = 1;

        if (PORTBbits.RB4 == 0){
            __delay_ms(100);
            if (PORTBbits.RB4 == 0){
                return '7';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(100);
            if (PORTBbits.RB5 == 0){
                return '8';
        }
        }

        if (PORTBbits.RB6 == 0){
            __delay_ms(100);
            if (PORTBbits.RB6 == 0){
                return '9';
        }
        }

        if (PORTBbits.RB7 == 0){
            __delay_ms(100);
            if (PORTBbits.RB7 == 0){
                return 'C';
        }
        }

        row1 = 1;
        row2 = 1;
        row3 = 1;
        row4 = 0;

        if (PORTBbits.RB4 == 0){
            __delay_ms(100);
            if (PORTBbits.RB4 == 0){
                return '*';
        }
        }

        if (PORTBbits.RB5 == 0){
            __delay_ms(100);
            if (PORTBbits.RB5 == 0){
                return '0';
        }
        }

        if (PORTBbits.RB6 == 0){
            __delay_ms(100);
            if (PORTBbits.RB6 == 0){
                return '#';
        }
        }

        if (PORTBbits.RB7 == 0){
            __delay_ms(100);
            if (PORTBbits.RB7 == 0){
                return 'D';
        }
        }

    }
}