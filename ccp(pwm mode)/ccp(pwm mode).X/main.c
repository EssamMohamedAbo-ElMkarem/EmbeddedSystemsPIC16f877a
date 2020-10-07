/* 
 * File:   main.c
 * Author: essam
 *
 * Created on August 10, 2020, 9:08 AM
 */

#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000
//-----[ Prototypes ]----
void PWM1_Init();
void PWM1_Set_Duty(uint16_t);
void ADC_Init();
uint16_t ADC_Read(uint8_t);
//====================================================
//----------[Main Routine]-------------
void main(void) 
{
    PWM1_Init();
    ADC_Init();
    while(1)
    {
        PWM1_Set_Duty(ADC_Read(0)); // Set PWM Duty Cycle To AN0_Result!
        __delay_ms(1);
    }
    return;
}
//----------[END OF MAIN]-------------
//====================================================
//------------[ CCP/PWM Routines ]--------------
void PWM1_Init()
{
  //--[ Configure The CCP Module For PWM Mode ]--
  CCP1M3 = 1;
  CCP1M2 = 1;
  TRISC2 = 0; // The CCP1 Output Pin (PWM)
  // Set The PWM Frequency (5kHz)
  PR2 = 124;
  // Set The PS For Timer2 (1:4 Ratio)
  T2CKPS0 = 1;
  T2CKPS1 = 0;
  // Start CCP1 PWM !
  TMR2ON = 1;
}
void PWM1_Set_Duty(uint16_t DC)
{
  // Check The DC Value To Make Sure it's Within 10-Bit Range
  if(DC<1024)
  {
    CCP1Y = DC & 1;
    CCP1X = DC & 2;
    CCPR1L = DC >> 2;
  }
}
//------------[ AD Converter Routines ]--------------
void ADC_Init()
{
    ADCON0 = 0x41;  // Turn ADC ON, Select AN0 Channel, ADC Clock = Fosc/8
    ADCON1 = 0x80;  // All 8 Channels Are Analog, Result is "Right-Justified"
                    // ADC Clock = Fosc/8
}
uint16_t ADC_Read(uint8_t ANC)
{
    if(ANC<0 || ANC>7)    // Check Channel Number Validity
    { return 0;}
    ADCON0 &= 0b11000101; // Clear The Channel Selection Bits
    ADCON0 |= ANC<<3;     // Select The Required Channel (ANC)
                          // Wait The Aquisition Time
    __delay_us(30);       // The Minimum Tacq = 20us, So That should be enough
    GO_DONE = 1;          // Start A/D Conversion
    while(ADCON0bits.GO_DONE); // Polling GO_DONE Bit
                               // Provides Delay Until Conversion Is Complete
    return ((ADRESH << 8) + ADRESL); // Return The Right-Justified 10-Bit Result
}
