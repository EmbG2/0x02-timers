/*
 * File:   newmainXC16.c
 * Author: EmbeddedG2
 *
 * Created on February 28, 2025, 11:01 AM
 */


#include "xc.h"
#include "timer.h"
#define ASSIGNMENT_N 3
int main(void) {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    TRISAbits.TRISA0 = 0;
    // ASSIGNMENT PART 1
    tmr_setup_period(TIMER1, 20);
    while(ASSIGNMENT_N == 1){
        LATAbits.LATA0 ^= 1;
        tmr_wait_period(TIMER1);
    }
    
    // ASSIGNMENT PART 2
    while(ASSIGNMENT_N == 2){
        LATAbits.LATA0 = 1;
        tmr_wait_ms(TIMER1, 20);
        LATAbits.LATA0 = 0;
        tmr_wait_ms(TIMER1, 200);  
    }
    
    // ASSIGNMENT PART 3
    TRISGbits.TRISG9 = 0;
    tmr_setup_period(TIMER1, 200);
    int delay = 1000;
    int blink = 100;
    int ret;
    while (ASSIGNMENT_N == 3){
        tmr_wait_ms_3(TIMER2, delay);
        LATAbits.LATA0 = 1;
        tmr_wait_ms_3(TIMER2, blink);
        LATAbits.LATA0 = 0;
        ret = tmr_wait_period_3(TIMER1);
        if (ret){
            LATGbits.LATG9 = 1;
            T1CONbits.TON = 0;
        } else{
            LATGbits.LATG9 = 0;
            T1CONbits.TON = 0;
            TMR1 =0;
            T1CONbits.TON = 1;
        }
    }
    return 0;
}
