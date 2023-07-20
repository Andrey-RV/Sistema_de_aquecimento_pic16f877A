#include <xc.h>
#include <pic16f877a.h>
#include "ad_converter.h"


void ad_init(void){
    ADCON0 = 0b11011001;
    ADCON1 = 0b10000010;
    TRISAbits.TRISA3 = 1;
}

unsigned int read_ad(void){
    unsigned int adc_result = 0;
    unsigned int voltage = 0;
    unsigned int temperature = 0;

    __delay_ms(100);
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);

    adc_result = (ADRESH << 8) + ADRESL;      // Left justified
    voltage = adc_result * 5;                 // 5V reference  
    temperature = voltage / 10;               // 10mV per degree Celsius
    return temperature;
}