#include "sched_cnf.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>  

#define OS_READY 0
#define OS_RUNNING 1

typedef struct {
    unsigned char OS_State_u8;  
    int duration;               
    int remaining_time;   
}OS_TASK;

void base_timer(OS_TASK *tasks, int num_tasks) {
    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].OS_State_u8 == OS_READY) {
            if (tasks[i].remaining_time > 0) {
                tasks[i].remaining_time--;  
            }

            if (tasks[i].remaining_time == 0 && tasks[i].OS_State_u8 == OS_READY) {
                tasks[i].OS_State_u8 = OS_RUNNING;  
            }
        }
    }
}

void task_scheduler(OS_TASK *tasks, int num_tasks) {
    tasks[0].duration = 2;  
    tasks[1].duration = 3;  
    tasks[2].duration = 5;  
    tasks[3].duration = 7;  

    for (int i = 0; i < num_tasks; i++) {
        tasks[i].OS_State_u8 = OS_READY;
        tasks[i].remaining_time = tasks[i].duration;  
    }
}

void execute_task(int task_id) {
    switch (task_id) {
        case 0:
            printf("Task 1 completed.\n");
            break;
        case 1:
            printf("Task 2 completed.\n");
            break;
        case 2:
            printf("Task 3 completed.\n");
            break;
        case 3:
            printf("Task 4 completed.\n");
            break;
        default:
            printf("Unknown task.\n");
    }
}

int main() {
    OS_TASK tasks[3];

    task_scheduler(tasks, 3);

    printf("Starting scheduler...\n");

    int num_tasks = 8;
    int tasks_completed = 0;

    while (tasks_completed < num_tasks) {
        base_timer(tasks, num_tasks);

        for (int i = 0; i < 3; i++) {
            switch (tasks[i].OS_State_u8) {
                case OS_READY:
                    break;

                case OS_RUNNING:
                    execute_task(i);  

                    tasks[i].OS_State_u8 = OS_READY;  
                    tasks_completed++;               
                    break;

                default:
                    printf("Unknown state for task %d\n", i + 1);
                    break;
            }
        }

        sleep(1); 
    }
    
    return 0;
}
