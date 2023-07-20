#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF  

#define _XTAL_FREQ 8000000
#define INCREASE_BUTTON 'A'
#define DECREASE_BUTTON 'D'
#define ENTER_BUTTON 'E'
#define CANCEL_BUTTON 'C'


void initial_setup(void);
unsigned char* get_aimed_temperature(void);
void display_aimed_temperature(const unsigned char* temperature);
unsigned char* get_heating_time(void);
void display_heating_time(const unsigned char* time);
unsigned char* format_time(const unsigned char* seconds);
void set_heating(const unsigned char* temperature);
void set_timer(const unsigned char* time);
void show_temp_and_time(void);
void end_heating(void);
void turn_on_fan(void);
void turn_off_fan(void);
