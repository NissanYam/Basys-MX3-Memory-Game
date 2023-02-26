#include <proc/p32mx370f512l.h>

#include "Leds.h"

void StarterForLeds(){
    TRISA &= 0xff00;
    PORTA = 0;
}
void turnOnLights(int inHex){
    PORTA = inHex;
}
void closeLights(){
    PORTA = 0;
}