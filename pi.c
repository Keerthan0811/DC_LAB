#include <stdio.h>
#include <omp.h>

int main() {
    long int N = 10000000;
    double pi = 0.0;

    // Parallelize the loop with reduction to avoid loop-carried dependency
    #pragma omp parallel for reduction(+:pi)
    for (long int i = 0; i < N; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2.0 * i + 1.0);
        pi += term;
    }

    pi = 4.0 * pi;
    printf("Estimated PI = %lf\n", pi);

    return 0;
}


// gcc pg7.c -o pg7 -fopenmp
// ./pg7

// Estimated PI = 3.141593
