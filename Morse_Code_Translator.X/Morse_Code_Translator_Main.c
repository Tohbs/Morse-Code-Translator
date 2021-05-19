/*
 * File:   hein0470_lab01_main_v001.c
 * Author: Henry
 *
 * Created on February 2, 2021, 1:44 AM
 */

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "string.h"
#include "Morse_Translation_Lib.h"
#include "Button_Input_Lib.h"
#include "ST7066_Disp_Lib.h"

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
// RS = RB12
//R/W = RB11
// D0->D7=RB2->RB10

#define CLRDISP      0b0000000001
#define RTNHOME    0b0000000010
#define EMS              0b0000000100 //Last two bits set the direction and display shift
#define DISPONOF    0b0000001000
#define DISPSHIFT    0b0000010000
#define FUNCSET      0b0000100000
#define WRITE           0b1000000000

//INTERPUT VARIABLES INITIALIZING 

//MORSE CODE TRANSLATOR CODE

//LCD CODE

void setup(void)
{
    //Executes Once
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISA = 0b0000000000011111;  //set port A to inputs,
    TRISB = 0b0010000000000011;  //and port B to outputs
    LATA = 0xffff;               //Set all of port A to HIGH

}
int main(void) {
    setup();
    initLCD();
    initPushButton();
// Variables are set up here for the button presses
    char first;
    char end=0;
    unsigned long int currentTime;
    while(1){
        currentTime=IC1BUF+(62499*rollover);
        if ((currentTime >= 187500 )&& (PORTBbits.RB13 != 0)){ //if it has been 3 seconds since the last button press
            //Get character from array
            char translation=translateMorseCode(pulseArray);
            if(translation==';'){
                end=1;
                send_CMD(DISPONOF|0b100);
                first=0;
            }
            else if(translation=='|'){
                send_CMD(CLRDISP);
                send_CMD(DISPONOF|0b111);
                send_CMD(RTNHOME);
                end=0;
                first=0;
            }
            else if(translation !='#'&& end!=1){
            send_Char(translation);
            }
            else if(first!=0 && end!=1){
                send_Char(' ');
                first=0;
            }

            else if(translation !='#'&& end!=1){
            send_Char(translation);
            first=0;
            }
            else{
                first++;
            }
            int i=0;
            for(i=0;i<6;i++){
                pulseArray[i]='0';

            //HERE, CALL THE CHAR TRANSLATE FUNCTION WITH THE CURRENT STATUS OF THE ARRAY, THEN CLEAR THE ARRAY AND RESET THE ARRAY POINTER
        }
            
         TMR2=0;
         rollover=0;
         tempArray=0;
        
    }        
    }
    return 0;
}
