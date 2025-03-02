/*
 * File:   timer.c
 * Author: EmbeddedG2
 *
 * Created on February 28, 2025, 11:04 AM
 */


#include "xc.h"
#include "timer.h"
#define FCY 72000000UL

void tmr_setup_period(int timer, int ms) {
    unsigned int prescaler, period;
    if (ms > 200){
        ms = 200;
    }
    if (ms > 50){
        prescaler = 256;
    } else if (ms > 10){
        prescaler = 64;
    } else if (ms > 2){
        prescaler = 8;
    } else{  // Note: also counts for negative ms, set PS to default 1
        prescaler = 1;
    } 
    
    period  = (FCY / (prescaler * 1000)) * ms;
    
    switch(timer){
        case TIMER1:
            T1CONbits.TON = 0;
            T1CONbits.TCKPS =   (prescaler == 256)?3:
                                (prescaler == 64)?2:
                                (prescaler == 8)?1:0;
            PR1 = period;
            TMR1 = 0;
            T1CONbits.TON = 1;
            break;
        case TIMER2:
            T2CONbits.TON = 0;
            T2CONbits.TCKPS =   (prescaler == 256)?3:
                                (prescaler == 64)?2:
                                (prescaler == 8)?1:0;
            PR2 = period;
            TMR2 = 0;
            T2CONbits.TON = 1;
            break;
    }
}

void tmr_wait_period(int timer){
    switch (timer){
        case TIMER1:
            IFS0bits.T1IF = 0;
            while (IFS0bits.T1IF == 0);
            IFS0bits.T1IF = 0;
            break;
        case TIMER2:
            IFS0bits.T2IF = 0;
            while (IFS0bits.T2IF == 0);
            IFS0bits.T2IF = 0;
            break;
    }
}

void tmr_wait_ms(int timer, int ms){
    tmr_setup_period(timer, ms);
    tmr_wait_period(timer);
    if (timer == TIMER1){
        T1CONbits.TON = 0;
    } else if (timer == TIMER2){
        T2CONbits.TON = 0;
    }
}

int tmr_wait_period_3(int timer){
    int expired = 0;
    switch(timer) {
        case TIMER1:
            expired = IFS0bits.T1IF;
            if (expired) {
                IFS0bits.T1IF = 0; // Clear flag after detecting it
            }
            break;
        case TIMER2:
            expired = IFS0bits.T2IF;
            if (expired) {
                IFS0bits.T2IF = 0; // Clear flag after detecting it
            }
            break;
    }
    return expired;
}


//        int num_times = ms/200;
//        for (int i = 0; i < num_times; i++) {
//            tmr_setup_period(timer, 200);
//        }
//        tmr_setup_period(timer, ms - num_times*200);
        
void tmr_wait_ms_3(int timer, int ms){
    int expired;

    while (ms > 0) {
        int wait_time = (ms > 200) ? 200 : ms; 
        tmr_setup_period(timer, wait_time);
        
        // Clear the interrupt flag before waiting
        if (timer == TIMER1) {
            IFS0bits.T1IF = 0;
        } else if (timer == TIMER2) {
            IFS0bits.T2IF = 0;
        }
        
        // Wait until timer expires
        do {
            expired = tmr_wait_period_3(timer);
        } while (expired == 0);

        // Stop the timer after waiting
        if (timer == TIMER1){
            T1CONbits.TON = 0;
        } else if (timer == TIMER2){
            T2CONbits.TON = 0;
        }

        ms -= wait_time;
    }
}

