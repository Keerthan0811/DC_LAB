//Estimate the value of pi using:Parallelize the code by removing loop carried dependency.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long num_points = 100000000;  // 100 million
    long inside_circle = 0;
    double x, y;

    double start = omp_get_wtime();

    #pragma omp parallel for private(x, y) reduction(+:inside_circle)
    for (long i = 0; i < num_points; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1.0)
            inside_circle++;
    }

    double pi_estimate = 4.0 * inside_circle / num_points;
    double end = omp_get_wtime();

    printf("Parallel Pi Estimate: %f\n", pi_estimate);
    printf("Parallel Time: %f seconds\n", end - start);
    return 0;
}
