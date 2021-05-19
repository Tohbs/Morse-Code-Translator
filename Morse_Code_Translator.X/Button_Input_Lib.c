#include "xc.h"
#define dot 'S'
#define dash 'L'
#define none '0'
volatile int rollover = 0; //used for the T2 ISR in case of rollover
volatile char pulseArray[6] = {'0','0','0','0','0','0'};
volatile int tempArray = 0; //for using the array in ISR
//GENRAL DELAY CODE
void delay(int ms){ //delay in milliseconds
    int i;
    for(i=0; i<ms; i++){
        asm("repeat #15993"); //1 cycle to load and prep
        asm("nop"); //15993+1 cycles
    }
}


//BUTTON SETUP CODE
volatile unsigned long int prevEdge = 0;
volatile unsigned long int curEdge=0;
volatile unsigned int count=0;
void __attribute__((interrupt, auto_psv)) _IC1Interrupt(){

    
    _IC1IF = 0; //clear Input Capture 1 interrupt flag
    
    //We need this conditional so that the program doesn't mistakenly think the time in between pulses is a short pulse 
    if(!count){ //the edge that just occurred is a rising edge, set prevEdge
        prevEdge = IC1BUF + (rollover*62500);
        count++; //increment count, so the next edge will be a falling edge
    }
    else{ //falling edge just occurred, we can calculate pulse lengths
        count = 0; //reset count
        curEdge = IC1BUF + (rollover*62500); //current edge = most recent rising edge from the buffer, + any rollover times
        if((curEdge - prevEdge)<125){ // (1ms/(62.5ns*256))*2 gives us the desired value for 2ms
            //debouncing block, do  nothing
            
        }
        else if(curEdge - prevEdge <=20833){ //short pulse has occurred, between 2ms and 333ms 
            pulseArray[tempArray] = dot;
            tempArray++;
            TMR2=0;
            rollover=0;

        }
        else if(curEdge - prevEdge <=62500){ //long pulse has occurred, between 333ms and 1s)
            pulseArray[tempArray] = dash;
            tempArray++;
            TMR2=0;
            rollover=0;

        }
   
    }
    
    
}


//This function initializes Timer2 and the correct TRIS bits to work with the button
//a pull up resistor is incorporated into the button, so that when it is pressed, the signal is pulled low
void initPushButton(){
    AD1PCFG = 0xffff; //set all pins digital     
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 13;  // Use Pin RP8 = "8", for Input Capture 1 (Table 10-2)
     __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    TRISBbits.TRISB13 = 1; //set RB13 to input, this is the button input
    CNPU1bits.CN13PUE = 1; //set pull up resistor on RB13 (pin 24)
    
    T2CON = 0; //reset timer 2 configuration register
    T2CONbits.TCKPS = 0b11; //set prescaler to a value of 256 
    TMR2 = 0; //reset timer
    PR2 = 62500-1; //sets up the period to be 1s
    // 1s/(62.5ns*256)=PR2
    //62500 is the value we get by doing the calculation, then subtract 1 because of the cycle it takes for
    //the PIC24 to realize the change
    IEC0bits.T2IE = 1; //enable the timer 2 interrupt
    

    
    IC1CON = 0; //reset internal state of IC1
    IC1CONbits.ICTMR = 1; //use TMR2 for capture source
    IEC0bits.IC1IE = 1; //enable IC1 interrupt
    
    T2CONbits.TON = 1; //turn on timer
    IC1CONbits.ICM = 0b001; //Turn on and capture rising AND falling edge 
}

//Interrupt Service Routine for TMR2
void __attribute__((interrupt, auto_psv)) _T2Interrupt(){
    rollover++; //increment rollover, indicating a rollover has occurred
    _T2IF = 0; //clear TMR2 interrupt flag
}


