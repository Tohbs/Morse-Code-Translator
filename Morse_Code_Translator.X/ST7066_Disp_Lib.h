/* 
 * File:   ST7066_Disp_Lib.h
 * Author: Henry
 *
 * Created on May 3, 2021, 1:36 AM
 */

#ifndef ST7066_DISP_LIB_H
#define	ST7066_DISP_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif

    void send_CMD(int CMD);
    void send_Char(char myChar);
    void initLCD(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ST7066_DISP_LIB_H */

