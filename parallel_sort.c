#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int a[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *temp = malloc((r - l + 1) * sizeof(int));
    while (i <= m && j <= r)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];
    for (i = l, k = 0; i <= r; i++, k++)
        a[i] = temp[k];
    free(temp);
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void parallelMergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(a, l, m);
            #pragma omp section
            mergeSort(a, m + 1, r);
        }
        merge(a, l, m, r);
    }
}

int main() {
    int n = 100000;
    int *a1 = malloc(n * sizeof(int));
    int *a2 = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        a1[i] = a2[i] = rand() % 1000;
    }

    double t1 = omp_get_wtime();
    mergeSort(a1, 0, n - 1);
    t1 = omp_get_wtime() - t1;

    double t2 = omp_get_wtime();
    parallelMergeSort(a2, 0, n - 1);
    t2 = omp_get_wtime() - t2;

    printf("Sequential Time = %lf sec\n", t1);
    printf("Parallel Time = %lf sec\n", t2);

    free(a1);
    free(a2);
    return 0;
}



// gcc pg9.c -o pg9 -fopenmp
// ./pg9


// Sequential Time = 0.024102 sec
// Parallel Time = 0.027413 sec

