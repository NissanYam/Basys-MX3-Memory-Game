
#include <xc.h>
#include <sys/attribs.h>
#include "RGB.h"

#define RED                 PORTDbits.RD2
#define GREEN               PORTDbits.RD12
#define BLUE                PORTDbits.RD3

void RGBLED_Init()
{
    RGBLED_ConfigurePins();
    lat_LED8_R = 0;
    lat_LED8_G = 0;
    lat_LED8_B = 0;
}

void RGBLED_ConfigurePins()
{
    rp_LED8_R = 0x0B; // LED8_R RPD2 is OC3 - for PWM usage
    rp_LED8_R = 0;      // no remapable
    tris_LED8_R = 0;    // output
  
    //RPD12R 1011 = OC5
//   rp_LED8_G = 0x0B; // LED8_G RPD12 is OC5 - for PWM usage
    rp_LED8_G = 0;      // no remapable
    tris_LED8_G = 0;    // output
 
//    rp_LED8_B = 0x0B; // LED8_B RPD3 is OC4 - for PWM usage
    rp_LED8_B = 0;      // no remapable
    tris_LED8_B = 0;    // output
    
    // disable analog (set pins as digital))
    ansel_LED8_R = 0;
    ansel_LED8_B = 0;
}

void RGBLED_SetValue(unsigned char bValR, unsigned char bValG, unsigned char bValB)
{
    RED = bValR;
    BLUE = bValB;
    GREEN = bValG;
}

void RGBLED_Close()
{
    lat_LED8_R = 0;
    lat_LED8_G = 0;
    lat_LED8_B = 0;
}