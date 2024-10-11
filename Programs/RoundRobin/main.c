#include <stdio.h>
#include "sched_cfg.h"  
#include "RR1.c"
#include "RR2.c"
#include "RR3.c"

int main() {
    int cur = 0,end=0;

    while (end<3) {
        void (*rr_functions[])() = RR_LIST;
        // to calculate the num of functions in the list
        int num_functions = sizeof(rr_functions) / sizeof(rr_functions[0]);

        for (int i = 0; i < num_functions; i++) {
            rr_functions[i]();
        }
        end++;
    }

    return 0;
}
