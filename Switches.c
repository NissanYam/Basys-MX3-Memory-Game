#include "Switches.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void starterForSwitches()
{
    TRISE&=0xff00;
    TRISA&=0xff00;
    PORTA = 0;
    TRISFbits.TRISF3 = 1; // RF3 (SW0) configured as input
    TRISFbits.TRISF5 = 1; // RF5 (SW1) configured as input
    TRISFbits.TRISF4 = 1; // RF4 (SW2) configured as input
    TRISDbits.TRISD15 = 1; // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1; // RD14 (SW4) configured as input
    TRISBbits.TRISB11 = 1; // RB11 (SW5) configured as input
    ANSELBbits.ANSB11 = 0; // RB11 (SW5) disabled analog
    TRISBbits.TRISB10 = 1; // RB10 (SW6) configured as input
    ANSELBbits.ANSB10 = 0; // RB10 (SW6) disabled analog
    TRISBbits.TRISB9 = 1; // RB9 (SW7) configured as input
    ANSELBbits.ANSB9 = 0; // RB9 (SW7) disabled analog
}
int sw(int num) // to cheak if the swiche on
{
    switch(num) 
    {
      case 0:
        return PORTFbits.RF3;
        break;
      case 1:
        return PORTFbits.RF5;
        break;
      case 2:
        return PORTFbits.RF4;
        break;
      case 3:
        return PORTDbits.RD15;
        break;
      case 4:
        return PORTDbits.RD14;
        break;
      case 5:
        return PORTBbits.RB11;
        break;
      case 6:
        return PORTBbits.RB10;
        break;
      case 7:
        return PORTBbits.RB9;
        break;
      default:
          return 0;
        break;
    }
}