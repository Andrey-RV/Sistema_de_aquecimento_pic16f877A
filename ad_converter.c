#include <xc.h>
#include <pic16f877a.h>
#include "ad_converter.h"


void ad_init(void){
    ADCON0 = 0b11011001;          //* Seleção do oscilador RC, canal 3 escolhido para conversão, conversor ligado
    ADCON1 = 0b10000010;          //* Resultado justificado à esquerda, seleção de oscilador RC, AN7:AN5 digitais, AN4:AN0 analógicas
    TRISAbits.TRISA3 = 1;         //* RA3/AN3 como entrada
}

unsigned int read_ad(void){
    unsigned int adc_result = 0;
    unsigned int voltage = 0;
    unsigned int temperature = 0;

    __delay_ms(100);
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);

    adc_result = (ADRESH << 8) + ADRESL;
    voltage = adc_result * 5;                 //* Normalização dos valores convertidos para 5V 
    temperature = voltage / 10;               //* 1/1024 = 0.00097. Do datasheet, 1°C ≈ 10mV  => (valor do AD / 10) ≈ 1°C 
    return temperature;
}