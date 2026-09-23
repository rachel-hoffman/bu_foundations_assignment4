#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"

// Shortest job first
float SJF(int* jobs, int size) {
   for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (jobs[j] < jobs[i]) {
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
    
    float responseTime = 0.0;
    float totalTime = 0.0;
    
    for (int i = 0; i < size; i++) {
        float jobTime = do_job(jobs[i], jobs[i], jobs[i], 0);
        
        responseTime += totalTime;
        totalTime += jobTime;
    }

    return responseTime / size;
}

// First in first out
float FIFO(int* jobs, int size) {
    float responseTime = 0.0;
    float totalTime = 0.0;
    
    for (int i = 0; i < size; i++) {
        float jobTime = do_job(jobs[i], jobs[i], jobs[i], 0);
        
        responseTime += totalTime;
        totalTime += jobTime;
        
    }

    return responseTime / size;
}
