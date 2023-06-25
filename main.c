#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#include <xc.h>
#include <pic16f877a.h>
#include "lcd.h"

#define _XTAL_FREQ 8000000


void __interrupt() isr(void) {

}

void main(void) {
    initialize_lcd();
    write_string("Insira a temperatura (°):");

    return;
}