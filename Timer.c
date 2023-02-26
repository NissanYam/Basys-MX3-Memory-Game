
#include "timer.h"
#include "Action.h"
#include <xc.h>  
#include <sys/attribs.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int calcPR(float time)
{
    float pr = time * 8 * pow(10,7);
    pr /= 2560;
    return (int)pr;
}

void __ISR(_TIMER_1_VECTOR, ipl7auto) Timer1SR(void);
void __ISR(_TIMER_23_VECTOR, ipl7auto) Timer23SR(void);
void __ISR(_TIMER_4_VECTOR, ipl7auto) Timer4SR(void);


void setTimer1(int priority, int subpriority, float time)
{
    PR1 = calcPR(time) & 0xFFFF;                        //              set period register
    TMR1 = 0;                           //             initialize count to 0
    T1CONbits.TCKPS0 = 1;                //            1:256 prescale value
    T1CONbits.TCKPS1 = 1; 
    T1CONbits.TSYNC = 1;
    T1CONbits.TGATE = 0;                //             not gated input (the default)
    T1CONbits.TCS = 0;                  //             PCBLK input (the default)
    T1CONbits.ON = 1;                   //             turn on Timer1
    IPC1bits.T1IP = priority;           //             priority
    IPC1bits.T1IS = subpriority;         //             subpriority
    IFS0bits.T1IF = 0;                  //             clear interrupt flag
    IEC0bits.T1IE = 1;
}

void setTimer23(int priority, int subpriority, float time)
{
    T2CONbits.TGATE=0;
    T2CONbits.TCS=0;
    T2CONbits.T32=1;//mode 32bit
    T2CONbits.TCKPS0=1;//????? 256
    T2CONbits.TCKPS1=1;
    T2CONbits.TCKPS2=1;
    T3CONbits.ON=0;
    TMR3=0;//TMRy
    TMR2=0;//TMRx
    int n_time = calcPR(time);
    PR2= n_time & 0xFFFF; //PR2x time register first 16 bits
    PR3= n_time >> 16; //PR2y - time register last 16 bits
    T2CONbits.ON=1;//start timer
    IFS0bits.T3IF=0;//
    IPC3bits.T3IP = priority;                  //             priority
    IPC3bits.T3IS = subpriority;                  //             subpriority
    IFS0bits.T3IF = 0;                  //             clear interrupt flag
    IEC0bits.T3IE = 1;
}

void setTimer4(int priority, int subpriority, float time)
{
    PR4 = calcPR(time) & 0xFFFF;                        //              set period register
    TMR4 = 0;                           //             initialize count to 0
    T4CONbits.TCKPS0 = 1;                //            1:256 prescale value
    T4CONbits.TCKPS1 = 1; 
    T4CONbits.TCKPS2 = 1;
    T4CONbits.TGATE = 0;                //             not gated input (the default)
    T4CONbits.TCS = 0;                  //             PCBLK input (the default)
    T4CONbits.ON = 1;                   //             turn on Timer1
    IPC4bits.T4IP = priority;           //             priority
    IPC4bits.T4IS = subpriority;          //             subpriority
    IFS0bits.T4IF = 0;                  //             clear interrupt flag
    IEC0bits.T4IE = 1;
}

void __ISR(_TIMER_1_VECTOR, ipl7) Timer1SR(void) 
{            
    actionTimer1();
    IFS0bits.T1IF = 0;
}

void __ISR(_TIMER_23_VECTOR, ipl7) Timer23SR(void) 
{            
    actionTimer23();
    IFS0bits.T2IF = 0;
    IFS0bits.T3IF = 0;
}

void __ISR(_TIMER_4_VECTOR, ipl7) Timer4SR(void) 
{            
    actionTimer4();
    IFS0bits.T4IF = 0;
}