#include <xc.h>
#define wait(val) for (int j=0; j < val; j++);
#define timer 64000
#define SPEAKER PORTBbits.RB14
#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	EC
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_1
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

#include "LCD.h"
#include "Switches.h"
#include "Game.h"
#include "Keybord.h"
#include "RGB.h"
#include "Timer.h"
#include "Leds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define wait(val) for (int j=0; j < val; j++);
#define timer 64000
void starter();
void starter(){
    srand(time(0));
    starterForSwitches();
    starterForLcd();
    starterForKeybord();
    RGBLED_Init();
    StarterForLeds();
    setTimer1(7, 0, 0.1);
    INTCONbits.MVEC=1;//vector interrupt
    IPTMR=0;//INTERRUPT PROXIMITY TIMER REGISTER
    asm("ei");//on interrupt
}

int main(){
    starter();
    clean();
    LCDdisplay("Memory game",0,0);
    LCDdisplay(" Pick up SW0",1,0);
    while(!sw(0)){};
    Game* memoryGame = (Game*)malloc(sizeof(Game));
        if(!memoryGame)
            return 0;
    char* arrToRemember;
    while(1){
        clean();
        LCDdisplay("Enter level 1-9",0,0);
        int xy = 0xFF;
        char c;
        do{    
            xy = get_xy();
            c =getKeyChar(xy);
        }while(c < '1' || c > '9');
        int i;
        int numerOfGames = (c-0x30);
        initGame(memoryGame,4,4);
        for (i = 0; i < numerOfGames; i++) {
            arrToRemember = getRandomArr(memoryGame);
            if(!arrToRemember)
                return 0;
            clean();
            printDetails(memoryGame, arrToRemember);
            int res = TestUser(memoryGame,arrToRemember);
            if(res == 1){
                nextLevel(memoryGame);
                RGBLED_SetValue(0,1,0);//green
                wait(timer*2);
                RGBLED_Close();
            }
            else{
                gameOver();
                while(!sw(1)){
                    beep();
                    RGBLED_SetValue(1,0,0);///red
                    wait(timer);
                    RGBLED_Close();
                }
                i = -1;
                initGame(memoryGame,4,4);
            }
            clean();
        }
        clean();
        LCDdisplay("Yow Win!! :)", 0,0);
        LCDdisplay(" 1-Play Again",1,0);
        RGBLED_SetValue(0,0,1);///blue
        do{    
            xy = get_xy();
        }while(getKeyChar(xy) != '1');
        RGBLED_Close();
        wait(timer*5);
        free(memoryGame);
        free(arrToRemember);
    }
    
    
    return 0;
}
