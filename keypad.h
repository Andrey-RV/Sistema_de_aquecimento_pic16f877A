#define row1 PORTBbits.RB2
#define row2 PORTBbits.RB3
#define _XTAL_FREQ 8000000
#define INCREASE_BUTTON 'A'
#define DECREASE_BUTTON 'D'
#define ENTER_BUTTON 'E'
#define CANCEL_BUTTON 'C'


void keypad_init(void);
unsigned char scan_keypad(void);