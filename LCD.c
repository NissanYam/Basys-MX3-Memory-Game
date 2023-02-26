#include "LCD.h"
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char Buffer[25];
const int SizeOfRow = 25;

void starterForLcd()
{
    TRISE&=0xff00;
    // set CGRAM=0x40
    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS) set as an output
    ANSELBbits.ANSB15 = 0; // disable analog functionality on RB15 (DISP_RS)
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW) set as an output
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN) set as an output
    TRISE&=0xff00;
    ANSELEbits.ANSE2 = 0;
    ANSELEbits.ANSE4 = 0;
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    ANSELEbits.ANSE7 = 0;
    char control[]={0x38,0x38,0x38,0xe,0x6,0x1,0xc0};
    int len = 6;
    int i;
    PORTBbits.RB15=0;//rs=0
    PORTDbits.RD5=0;//w=0
    for(i=0;i<len;i++)
    {
        PORTE=control[i];
        PORTDbits.RD4=1;
        PORTDbits.RD4=0;
        //for(j=0;j<32000;j++);
        busy();
    }
}
void busy(void)
{
    char RD,RS;
    int STATUS_TRISE;
    int portMap;
    RD=PORTDbits.RD5;
    RS=PORTBbits.RB15;
    STATUS_TRISE=TRISE;
    PORTDbits.RD5 = 1;//w/r
    PORTBbits.RB15 = 0;//rs 
    portMap = TRISE;
    portMap |= 0x80;
    TRISE = portMap;
    do
    {
        PORTDbits.RD4=1;//enable=1
        PORTDbits.RD4=0;//enable=0
    }
    while(PORTEbits.RE7); // BF ?????
    PORTDbits.RD5=RD; 
    PORTBbits.RB15=RS;
    TRISE=STATUS_TRISE;   
}
void refresh()
{
    PORTDbits.RD4=1;
    PORTDbits.RD4=0;
}
void clean()
{
    PORTBbits.RB15=0;//rs=0
    PORTDbits.RD5=0;//w=0
    PORTE = 0x1;
    refresh();
    busy();
}
void linebreak()
{
    PORTBbits.RB15=0;//rs=0
    PORTDbits.RD5=0;//w=0
    PORTE = 0xc0;// linebreak
    refresh();
}
void writeText(char* str, int len)
{
    int i;
    PORTBbits.RB15=1;//rs=0
    PORTDbits.RD5=0;//w=0
    for(i=0;i<len;i++)
    {
        PORTE=str[i];
        refresh();
        busy();
    }
}
void LCDdisplay(char* str, int row, int indexToStart)
{
    cleanBuffer();
    copyStrToBuffer(str,indexToStart);
    if(row == 1)
    {
        linebreak();
    }
    writeText(Buffer, SizeOfRow);
}
void cleanBuffer()
{
    int i;
    for (i = 0 ; i < 25 ; i ++)
            Buffer[i] = 0x20;
}
void copyStrToBuffer(char* str1,int indexToStart)
{
    int i;
    for(i = 0; i < strlen(str1); i++){
        int index = (i+indexToStart)%SizeOfRow;
        Buffer[index] = str1[index];
    }
}