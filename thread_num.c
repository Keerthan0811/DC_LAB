#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;

    #pragma omp parallel shared(sum)
    {
        int tid = omp_get_thread_num();

        #pragma omp critical
        {
            sum += tid;
            printf("Thread %d added its ID → Current sum = %d\n", tid, sum);
        }
    }

    printf("Final Sum = %d\n", sum);
    return 0;
}


// gcc pg8.c -o pg8 -fopenmp
// ./pg8


// Thread 0 added its ID → Current sum = 0
// Thread 1 added its ID → Current sum = 1
// Thread 2 added its ID → Current sum = 3
// Thread 3 added its ID → Current sum = 6
// ...
// Final Sum = 66
