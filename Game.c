#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Game.h"
#include "LCD.h"
#include "Keybord.h"
#include "RGB.h"

const int numOfRowsAndCols = 4;
const char Keys [4][4]= {{'D','E','F','0'}
                         ,{'C','9','8','7'}
                         ,{'B','6','5','4'}
                         ,{'A','3','2','1'}};

void initGame(Game* g ,int time_left, int amountOfItems)
{
    g->level = 0;
    g->TimeLeft = time_left;///sec
    g->amountOfItems = amountOfItems;
}
int getRandomNum(int Max)
{
    int random = (int)(rand() % Max);
    return random;
}
void getRamdomRowAndCol(int* row, int* col)
{
    int i;
    (*row) = getRandomNum(numOfRowsAndCols);
    wait(timer);
    (*col) = getRandomNum(numOfRowsAndCols);
}
char* printDetails(Game* g, char* arr)
{
    ///for first row
    char details[25] = "Level:";
    char l[1];
    char level = intToChar(g->level);
    details[6] = level;
    strcat(details," left:");
    char secRow[25]= " ";
    strcat(secRow,arr);
    ///print first row and second row
    int i;
    for ( i = 0 ; i < g->TimeLeft ; i++){
        details[13] = intToChar(g->TimeLeft-i);
        LCDdisplay(details, 0, 0);
        LCDdisplay(secRow, 1,0);
        wait(timer*20);
        clean();
    }
}
char* getRandomArr(Game* g)
{
    char *arr = (char*) malloc(sizeof(char)*(g->amountOfItems));
    if(!arr)
        return NULL;
    int i,row,col;
    for (i = 0 ; i < g->amountOfItems ; i++){
        getRamdomRowAndCol(&row, &col);
        arr[i] = Keys[row][col];
    }
    return arr;
}
void nextLevel(Game* g){
    g->level+=1;
    if(g->level%3 == 0){
        g->TimeLeft--;
    }
    g->amountOfItems++;
}

char getKeyChar(int xy) // get ASCII Char
{
    if( xy == 0xff)
        return ' ';
    return Keys[(xy & 0xf) - 1][((xy & 0xf0) >> 4) -1];
}
int TestUser(Game* g, char* arr){
    char firstRow[16] = "left: ";
    char secRow [16] = " ";
    int i;
    for (i = 1 ; i < g->amountOfItems+1 ; i++)
        secRow[i] = 'X';
    int xy = 0Xff;
    int j = 0;
    char *arrToComper  = (char*) malloc (sizeof(char)*g->amountOfItems);
    int left = g->TimeLeft*2;
    for (left ; left > 0; left--){
        for(i = 1; i < 600; i++){
            xy = get_xy();
            if (xy == 0xff ){ /// I dont know why the xy!=0xff dont work
            }
            else{
                char c = getKeyChar(xy);
                secRow[j+1] = c;
                arrToComper[j] = c;
                j++;
                wait(timer*5);
            }
            if(j == g->amountOfItems)
                return comparArrays(g,arr,arrToComper);
            char* leftStr = getStrFromNum(left);
            strcat(firstRow,leftStr);
            clean();
            LCDdisplay(firstRow,0,0);
            LCDdisplay(secRow,1,0);
            free(leftStr);
            xy = 0Xff;
            strcpy(firstRow,"left: ");
        }
    }
    return 0;
}
int comparArrays(Game* g, char* arr,char* arrTocomper){
    int i;
    for (i = 0; i < g->amountOfItems ; i++){
        if (arr[i] != arrTocomper[i])
            return 0;
    }
    return 1;
}

char* getStrFromNum(int num){ // num can be >= 10
    char* str = (char*)malloc(sizeof(char)*10);
    itoa(str ,num , 10);
    return str;
}
char intToChar(int n){ /// numbers between 0-9
    char zero = 0x30;
    return zero+n;
}
void gameOver()
{
    clean();
    LCDdisplay("Game over :(",0,0);
    LCDdisplay(" pick up SW1",1,0);
}
void beep()
{
    for (int j = 0 ; j < 100 ; j++)
    {
        SPEAKER = 1;
        wait(440);
        SPEAKER = 0;
    }
}