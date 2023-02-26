#ifndef _RGB
#define _RGB


#define tris_LED8_R         TRISDbits.TRISD2
#define rp_LED8_R           RPD2R
#define lat_LED8_R          LATDbits.LATD2
#define ansel_LED8_R        ANSELDbits.ANSD2

#define tris_LED8_G         TRISDbits.TRISD12
#define rp_LED8_G           RPD12R
#define lat_LED8_G          LATDbits.LATD12


#define tris_LED8_B         TRISDbits.TRISD3
#define rp_LED8_B           RPD3R
#define lat_LED8_B          LATDbits.LATD3
#define ansel_LED8_B        ANSELDbits.ANSD3

void RGBLED_Init();
void RGBLED_SetValue(unsigned char bValR, unsigned char bValG, unsigned char bValB);
void RGBLED_Close();
void RGBLED_ConfigurePins();

#endif