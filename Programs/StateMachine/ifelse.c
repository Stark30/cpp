#include <stdio.h>
#define OFF 0
#define ON 1

int main() {
    int cur_state = OFF;  
    char button='y';
    printf("Initial State RED LED is OFF\n\n");

    while (button=='y') {
        if(cur_state==OFF) {
            cur_state = ON;
            printf("Button Pressed. RED LED is ON\n");
        }
        else if(cur_state==ON){
            cur_state = OFF;
            printf("Button Pressed. RED LED is OFF\n");
        }

        printf("\nInput: (y: to toggle switch. /n: to stop): ");
        scanf(" %c", &button);
    }

    return 0;
}
