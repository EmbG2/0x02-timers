/*
 * File:   newmainXC16.c
 * Author: EmbeddedG2
 *
 * Created on February 28, 2025, 11:01 AM
 */


#include "xc.h"
#include "timer.h"

int main(void) {
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    TRISAbits.TRISA0 = 0;
    
    // ASSIGNMENT PART 1
//    tmr_setup_period(TIMER1, 20);
//    while(1){
//        LATAbits.LATA0 ^= 1;
//        tmr_wait_period(TIMER1);
//    }
    
    // ASSIGNMENT PART 2
//    while(1){
//        LATAbits.LATA0 = 1;
//        tmr_wait_ms(TIMER1, 20);
//        LATAbits.LATA0 = 0;
//        tmr_wait_ms(TIMER1, 200);  
//    }
    
    // ASSIGNMENT PART 3
//    while (1){
//        LATAbits.LATA0 = 1;
//        tmr_wait_ms_milad(TIMER1, 2000);
//        LATAbits.LATA0 = 0;
//        tmr_wait_ms_milad(TIMER1, 200);  
//    }
    return 0;
}
