#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }
    
    float averageTime = 0.0;

    int jobs[10];
    
    char* token = strtok(argv[2], ",");

    int size = 0;

    while(token != NULL){
        jobs[size] = atoi(token);
        size++;
        token = strtok(NULL, ",");
    }

    if(strcmp(argv[1], "FIFO"))
        averageTime = FIFO(jobs, size);
    else if(strcmp(argv[1], "SJF"))
        averageTime = SJF(jobs, size);
    else
        printf("Invalid scheduler. Expected FIFO or SJF.");

    printf("Average response time: %f seconds\n", averageTime);

    return 0;
}
