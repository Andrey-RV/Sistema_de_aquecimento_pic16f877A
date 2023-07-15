#define EN PORTEbits.RE1
#define RS PORTEbits.RE0
#define data_bus PORTD
#define _XTAL_FREQ 8000000

void write_on_lcd_bus(char a);
void send_lcd_command(char a);
void initialize_lcd();
void clear_lcd(void);
void set_cursor(char a, char b);
void write_char(char a);
void write_string(const char* a);