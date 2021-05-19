/* 
 * File:   Button_Input_Lib.h
 * Author: Henry
 *
 * Created on May 3, 2021, 1:21 AM
 */

#ifndef BUTTON_INPUT_LIB_H
#define	BUTTON_INPUT_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    extern volatile int rollover;
    extern volatile char pulseArray[6] ;
    extern volatile int tempArray;
void delay(int ms);
void __attribute__((interrupt, auto_psv)) _IC1Interrupt();
void initPushButton();
void __attribute__((interrupt, auto_psv)) _T2Interrupt();


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_INPUT_LIB_H */

