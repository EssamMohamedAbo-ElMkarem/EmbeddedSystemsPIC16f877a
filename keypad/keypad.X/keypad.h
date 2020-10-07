#include <xc.h>

#define _XTAL_FREQ 800000000 //Crystal Frequency, used in delay
#define X_1    RB0
#define X_2    RB1
#define X_3    RB2
#define X_4    RB3
#define Y_1    RB4
#define Y_2    RB5
#define Y_3    RB6
#define Y_4    RB7
#define Keypad_PORT          PORTB
#define Keypad_PORT_Direction     TRISB   

void InitKeypad(void);
char switch_press_scan(void);
char keypad_scanner(void);