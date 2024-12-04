#include "sched_cnf.h"
#include "RR.c"
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>  

#define OS_READY 0
#define OS_RUNNING 1

typedef struct {
    unsigned char OS_State_u8;
    int duration;
} OS_STATE;

volatile int interrupt_flag = 0;

void InterruptHandler(int sig) {
    printf("INTERRUPT CALLED\n");
    interrupt_flag = 1;
    sleep(2); 
    //interrupt_flag = 0;
    printf("INTERRUPT FINISH\n");
}

void TimerProcess(OS_STATE *timers, int num_timers) {
    static clock_t last_check_time = 0;
    clock_t current_time = clock();
    
    if (((current_time - last_check_time) * 1000 / CLOCKS_PER_SEC) >= 10) {
        last_check_time = current_time;

        for (int i = 0; i < num_timers; i++) {
            if (timers[i].OS_State_u8 == OS_RUNNING) {
                clock_t start_time = current_time;
                if (((current_time - start_time) * 1000 / CLOCKS_PER_SEC) >= timers[i].duration) {
                    timers[i].OS_State_u8 = OS_READY;  // Move back to READY state
                }
            }
        }
    }
}

void checktimer(OS_STATE *timers, int num_timers, void (*Rnd_rbn[])(void)) {
    int runindex = -1;
    int comp = 0;

    while (comp < num_timers && !interrupt_flag) { 
        for (int i = 0; i < num_timers; i++) {
            if (timers[i].OS_State_u8 == OS_READY && runindex == -1) {
                printf("Timer %d RUNNING for %d ms.\n", i + 1, timers[i].duration);
                timers[i].OS_State_u8 = OS_RUNNING;
                runindex = i;

                clock_t start_time = clock();
                while (((clock() - start_time) * 1000 / CLOCKS_PER_SEC) < timers[i].duration) {
                    if (interrupt_flag) return;  
                }

                Rnd_rbn[i]();  

                timers[i].OS_State_u8 = OS_READY;  
                runindex = -1;  
                comp++;  
            }
        }
    }
}

int main() {
    signal(SIGALRM, InterruptHandler);
    alarm(6);  // Set an interrupt every 6 seconds

    OS_STATE timers[] = {
        {OS_READY, 2000},  
        {OS_READY, 3000},  
        {OS_READY, 5000},  
    };

    void (*Rnd_rbn[])(void) = {R1, R2, R3, R4};

    int num_timers = sizeof(timers) / sizeof(timers[0]);
    int cnt=2;

    while (cnt>0) {
        checktimer(timers, num_timers, Rnd_rbn);  // RR processes

        TimerProcess(timers, num_timers);

        //ISR triggering every 6 seconds
        if (interrupt_flag) {
            while (interrupt_flag) {
            }
            alarm(6);  // Reset ISR alarm 
        }
        cnt-=1;
    }

    return 0;
}
