#define EN PORTEbits.RE1
#define RS PORTEbits.RE0
#define data_bus PORTD
#define _XTAL_FREQ 8000000

void write_on_lcd_bus(unsigned char a);
void send_lcd_command(unsigned char a);
void initialize_lcd(void);
void clear_lcd(void);
void set_cursor(unsigned char a, unsigned char b);
void write_char(unsigned char a);
void write_string(const unsigned char* a);
