/* 
 * File:   main.c
 * Author: essam
 *
 * Created on August 2, 2020, 3:19 PM
 */

#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 8000000

int main()
{
    TRISB = 0x00;
    PORTB = 0x00;
    while(1)
    {
        PORTB = PORTB + 1;
        __delay_ms(1000);
    }
    return 0;
}