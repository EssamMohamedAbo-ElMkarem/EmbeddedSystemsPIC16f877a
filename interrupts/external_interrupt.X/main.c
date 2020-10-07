/* 
 * File:   main.c
 * Author: essam
 *
 * Created on August 8, 2020, 9:59 AM
 */

#include<xc.h>
#include "config.h"
#define _XTAL_FREQ 8000000
#define LEDRED RC0
#define LEDYELLOW RC1

int main()
{
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISBbits.TRISB0 = 1;
    PORTC = 0x00;
    GIE = 1;
    INTE = 1;
    while(1)
    {
        LEDRED = 1;
        __delay_ms(2000);
        LEDRED = 0;
        __delay_ms(2000);
    }
    return 0;
}

void __interrupt() ISR(void)
{
    if(INTF == 1)
    {
        LEDYELLOW = 1;
        __delay_ms(500);
        LEDYELLOW = 0;
        INTF = 0;
    }
}