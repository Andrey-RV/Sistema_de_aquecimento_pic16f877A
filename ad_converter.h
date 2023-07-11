#include <xc.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 8000000

void ad_init(void);
unsigned int read_ad(void);


void ad_init(void){
    ADCON0 = 0b11000001;
    ADCON1 = 0b10000010;
    TRISAbits.TRISA0 = 1;
}

unsigned int read_ad(void){
    unsigned int adc_result = 0;
    unsigned int voltage = 0;
    unsigned int temperature = 0;

    __delay_ms(1000);
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);

    adc_result = (ADRESH << 8) + ADRESL;
    voltage = adc_result * 5;
    temperature = voltage / 10;
    return temperature;
}