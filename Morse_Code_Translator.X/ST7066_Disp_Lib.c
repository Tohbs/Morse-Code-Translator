#include "xc.h"

#define CLRDISP      0b0000000001
#define RTNHOME    0b0000000010
#define EMS              0b0000000100 //Last two bits set the direction and display shift
#define DISPONOF    0b0000001000
#define DISPSHIFT    0b0000010000
#define FUNCSET      0b0000100000
#define WRITE           0b1000000000

void send_CMD(int CMD){
    int command = CMD*4;
    LATB= LATB | (command);
    delay(1);
    LATB = LATB|0b1000000000000000;
    delay(1);
    LATB= LATB & 0b0110000000000011;
} 
void send_Char(char myChar){
    int letter = myChar;
    letter = WRITE | letter;
    send_CMD(letter);
}
void initLCD(void){
    TRISB = TRISB & 0b0111000000000011;
    delay(100);
    int currCom;
    currCom=CLRDISP;
    send_CMD( DISPONOF|0b111);
    send_CMD(CLRDISP);
    send_CMD(RTNHOME);
    delay(2);
    
}
