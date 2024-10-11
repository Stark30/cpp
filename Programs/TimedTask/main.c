#include<stdio.h>
#include<time.h>
#include <unistd.h>
#include "TT1.c"
#include "TT2.c"
#include "TT3.c"

void delay_ms(int milliseconds) {
    usleep(milliseconds * 1000); 
}

int main() {
    clock_t start_time = clock();
    int elapsed_time = 0;
    int end=3;

    while (end>0) {
        // Calculate elapse time in milliseconds
        elapsed_time = (clock() - start_time) * 1000 / CLOCKS_PER_SEC;

        // Execute TT1 every 10ms
        if (elapsed_time % 10 == 0) {
            TT1();
        }

        // Execute TT2 every 20ms
        if (elapsed_time % 20 == 0) {
            TT2();
        }

        // Execute TT3 every 30ms
        if (elapsed_time % 30 == 0) {
            TT3();
        }

        // Delay to simulate the 1ms clock tick
        delay_ms(1); // 1ms delay
        
        end--;
    }
   

    return 0;
}