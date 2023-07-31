#include <xc.h>
#include <pic16f877a.h>
#include "lcd4.h"


void write_on_lcd_bus(unsigned char a)
{
    data_bus = a << 4;        //* Os pinos conectados ao barramento de dados do LCD são os 4 mais significativos de data_bus
}

void send_lcd_command(unsigned char a){
    RS = 0;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(2);
}

void send_data(unsigned char a){
    RS = 1;
    write_on_lcd_bus(a);
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(2);
}

void initialize_lcd(void){
    data_bus_direction = 0x00;            //* Barramento de dados como saída
    control_bus_direction = 0x00;         //* Barramento de controle como saída
    ADCON1 = 0x06;              //* Todos os pinos como digitais
    data_bus = 0x00;            //* Inicializa o barramento de dados com 0

    __delay_ms(20);
    send_lcd_command(0x02);     //* Comando de modo 4 bits
    __delay_ms(20);
    send_lcd_command(0x02);     //* Reenvio para garantir que o comando foi recebido
    send_lcd_command(0x08);     //* Segunda parte do comando de modo 4 bits
    send_lcd_command(0x00);     //* Primeira parte do comando de ligar display com cursor desligado
    send_lcd_command(0x0C);     //* Segunda parte do comando de ligar display com cursor desligado
    clear_lcd();
}

void clear_lcd(void){
    send_lcd_command(0x00);     //* Primeira parte do comando de limpar display
    send_lcd_command(0x01);     //* Segunda parte do comando de limpar display
    send_lcd_command(0x00);     //* Primeira parte do comando de retorno do cursor para o início
    send_lcd_command(0x02);     //* Segunda parte do comando de retorno do cursor para o início
    set_cursor(1, 1);
}

void set_cursor(unsigned char a, unsigned char b){
    unsigned char position, position_high, position_low;
    if (a == 1){
        position = 0x80 + b - 1;            //* o Comando 0x80 move o cursor para o início da primeira linha
        position_high = position & 0xF0;
        position_low = position & 0x0F;
        send_lcd_command(position_high >> 4);
        send_lcd_command(position_low);      
    }  
    else if (a == 2){
        position = 0xC0 + b - 1;            //* o Comando 0xC0 move o cursor para o início da segunda linha
        position_high = position & 0xF0;
        position_low = position & 0x0F;

        //* A parte alta deve ser deslocada para a esquerda pois write_on_lcd_bus() espera que os dados estejam no nibble baixo    
        send_lcd_command(position_high >> 4); 
        send_lcd_command(position_low);
    }
}

void write_char(unsigned char a){
    unsigned char lower_nibble = a & 0x0F;
    unsigned char higher_nibble = a & 0xF0;

    //* A parte alta deve ser deslocada para a direita pois send_data() espera que os dados estejam no nibble baixo
    send_data(higher_nibble >> 4);
    send_data(lower_nibble);
}

void write_string(const unsigned char* a){
    unsigned char i;
    for (i = 0; a[i] != '\0'; i++)
        write_char(a[i]);
}
