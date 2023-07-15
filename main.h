#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF  

#define _XTAL_FREQ 8000000

void initial_setup(void);
unsigned char* get_aimed_temperature(void);
void display_aimed_temperature(const unsigned char* temperature);
unsigned char* get_heating_time(void);
void display_heating_time(const unsigned char* time);
void set_heating(const unsigned char* temperature);
void set_timer(const unsigned char* time);
void show_temp_and_time(void);
