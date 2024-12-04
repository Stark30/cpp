//Prioritise based on tasks - keep the 

#include "sched_cnf.h"
#include "RR.c"
#include <stdio.h>
#include <time.h>

#define OS_READY 0
#define OS_RUNNING 1

typedef struct {
    unsigned char OS_State_u8; 
    int duration;              
} OS_STATE;

void checktimer(OS_STATE *timers, int num_timers, void (*Rnd_rbn[])(void)) {
    int runindex = -1;
    int comp = 0; 

    while (comp < num_timers) {
        for (int i = 0; i < num_timers; i++) {
            switch (timers[i].OS_State_u8) {
                case OS_READY:
                    if (runindex == -1) {
                        printf("Timer %d RUNNING for %d ms.\n", i + 1, timers[i].duration);
                        timers[i].OS_State_u8 = OS_RUNNING;
                        runindex = i;

                        clock_t start_time = clock();
                        while (((clock() - start_time) * 1000 / CLOCKS_PER_SEC) < timers[i].duration) {
                        }

                        Rnd_rbn[i]();  

                        timers[i].OS_State_u8 = OS_READY; 
                        runindex = -1;         
                        comp++;              
                    }
                    break;

                case OS_RUNNING:
                    break;

                default:
                    printf("Unknown state for timer %d\n", i + 1);
                    break;
            }
        }
    }
}

int main() {
    OS_STATE timers[] = {
        {OS_READY, 2000}, 
        {OS_READY, 3000}, 
        {OS_READY, 5000}, 
    };

    void (*Rnd_rbn[])(void) = {R1, R2, R3, R4};

    int num_timers = sizeof(timers) / sizeof(timers[0]);

    checktimer(timers, num_timers, Rnd_rbn);

    return 0;
}
