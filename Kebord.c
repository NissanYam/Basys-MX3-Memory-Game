#include <p32xxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "Keybord.h"

void starterForKeybord(){
    TRISCbits.TRISC2=0;//RC2
    TRISCbits.TRISC1=0;//RC1
    TRISCbits.TRISC4=0;//RC4            
    TRISGbits.TRISG6=0;//RG6
    ANSELGbits.ANSG6=0;//???????
    TRISCbits.TRISC3 =1;//RC3
    CNPUCbits.CNPUC3;               
    TRISGbits.TRISG7=1;//RG7
    ANSELGbits.ANSG7=0;
    CNPUGbits.CNPUG7;                  
    TRISGbits.TRISG8=1;//RG8
    ANSELGbits.ANSG8=0;//???????
    CNPUGbits.CNPUG8;//???
    TRISGbits.TRISG9=1;//RG9
    ANSELGbits.ANSG9=0;//???????
    CNPUGbits.CNPUG9;//?????
}
int get_xy()
{
    int i=1;
    int xy = 0Xff;
    PORTCbits.RC2=1;
    PORTCbits.RC1=1;
    PORTCbits.RC4=1;
    PORTGbits.RG6=1;
    i=1;
    PORTCbits.RC2=0; /// to check if click on  A\B\C\D
    xy=in_y(1);
    if (xy!=0xff)
        return xy;
    PORTCbits.RC2=1;
    i=2;
    PORTCbits.RC1=0; /// to check if click on  3\6\9\E
    xy=in_y(2);
    if (xy!=0xff)
       return xy;
    PORTCbits.RC1=1;
    i=3;
    PORTCbits.RC4=0; /// to check if click on  2\5\8\F
    xy=in_y(3);
    if (xy!=0xff)
       return xy;
    PORTCbits.RC4=1;
    i=4;
    PORTGbits.RG6=0; /// to check if click on  1\4\7\0
    xy=in_y(4);
    if (xy!=0xff)
       return xy;
    PORTGbits.RG6=1;
    return xy;
}
int in_y( int a)
{ 
    int j=1,flag=0;

    if(!PORTCbits.RC3)  /// if click on  D\E\F\0
    { flag=1;
        j=1;
    }
   else if (!PORTGbits.RG7)/// if click on  C\9\8\7
   { flag=1;
        j=2;
   }
   else  if(!PORTGbits.RG8)/// if click on  B\6\5\4
        { flag=1;
        j=3;
        }
   else if(!PORTGbits.RG9) /// if click on  A\3\2\1
      { flag=1; 
        j=4;
   }
    if(flag==0) /// dont click
        return(0xff);
    else
       return(j|(a<<4)); /// calc row and col ; j = row ; a = col
}
