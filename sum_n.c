#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 100;
    int sum = 0;

    #pragma omp parallel private(i) reduction(+:sum)
    {
        #pragma omp for
        for (i = 1; i <= N; i++) {
            sum += i;
        }
    }

    printf("Sum = %d\n", sum);
    return 0;
}


// gcc pg5.c -o pg5 -fopenmp
// ./pg5


// Sum = 5050
