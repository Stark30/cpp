#include <stdio.h>
#define OFF 0
#define ON 1

int main() {
    int cur_state = OFF;  
    char button='y';
    printf("Initial State RED LED is OFF\n\n");

    while (button=='y') {
        switch (cur_state) {
            case OFF:
                cur_state = ON;
                printf("Button Pressed. RED LED is ON\n");
                break;

            case ON:
                cur_state = OFF;
                printf("Button Pressed. RED LED is OFF\n");
                break;

            default:
                printf("Unknown state\n");
                break;
        }
        printf("\nInput: (y: to toggle switch. /n: to stop): ");
        scanf(" %c", &button);
    }

    return 0;
}
