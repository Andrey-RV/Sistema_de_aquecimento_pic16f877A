#define row1 PORTBbits.RB2
#define row2 PORTBbits.RB3
#define _XTAL_FREQ 8000000


void keypad_init(void);
char scan_keypad(void);