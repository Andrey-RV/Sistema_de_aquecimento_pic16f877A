#define EN PORTEbits.RE1
#define RS PORTEbits.RE0
#define data_bus PORTD
#define control_bus PORTE
#define data_bus_direction TRISD
#define control_bus_direction TRISE
#define _XTAL_FREQ 8000000

void write_on_lcd_bus(unsigned char a);
void send_lcd_command(unsigned char a);
void send_data(unsigned char a);
void initialize_lcd(void);
void clear_lcd(void);
void set_cursor(unsigned char a, unsigned char b);
void write_char(unsigned char a);
void write_string(const unsigned char* a);
