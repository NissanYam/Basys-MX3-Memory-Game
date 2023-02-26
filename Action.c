
#include "Action.h"
#include <xc.h>  
#include <sys/attribs.h>
#include <string.h>
#include <stdlib.h>
#include "Leds.h"
#include "Switches.h"

void actionTimer1(void)
{
    if(sw(0)){
        if(sw(1))
            turnOnLights(0x3);
        else
            turnOnLights(0x1);
    }
    else if(sw(1))
        turnOnLights(0x2);
    else
        closeLights();
    
}

void actionTimer23(void)
{
}

void actionTimer4(void)
{
}

