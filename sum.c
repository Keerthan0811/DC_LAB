//Write an OpenMP program that computes the sum of the first N integers using a
//parallel for loop. Use the #pragma omp for directive along with the private and reduction
// clauses.

// parallel_sum.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n, i;
    long long sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize array with values 1..n
    for (i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    double start = omp_get_wtime();
    //pragma omp parallel for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += arr[i];
    }
    double end = omp_get_wtime();

    printf("\nParallel Sum = %lld", sum);
    printf("\nTime Taken = %f seconds\n", end - start);

    free(arr);
    return 0;
}
