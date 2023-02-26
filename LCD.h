
#ifndef _LCD
#define _LCD
void starterForLcd();
void busy(void);
void refresh();
void clean();
void linebreak();
void writeText(char* str, int len);

void LCDdisplay(char* str, int row, int indexToStart);
void cleanBuffer();
void copyStrToBuffer(char* str1,int indexToStart);
#endif