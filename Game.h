
#ifndef _GAME
#define _GAME
#define wait(val) for (int j=0; j < val; j++);
#define timer 64000
#define SPEAKER PORTBbits.RB14

typedef struct Game
{
    int level;
    int TimeLeft;
    int amountOfItems;
} Game;

void initGame(Game* g ,int time_left, int amountOfItems);
int getRandomNum(int Max);
void getRamdomRowAndCol(int* row, int* col);
char* printDetails(Game* g, char* arr);
char* getRandomArr(Game* g);
char intToChar(int n);
char getKeyChar(int xy);
void nextLevel(Game* g);
int TestUser(Game* g, char* arr);
int comparArrays(Game* g, char* arr,char* arrTocomper);
char* getStrFromNum(int num);
void beep();
void gameOver();
#endif