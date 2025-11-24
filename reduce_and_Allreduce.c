// Demonstration of MPI_Reduce operations: SUM, MAX, MIN, PROD
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value, sum, max, min, prod;

    MPI_Init(&argc, &argv);  // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    value = rank + 1;  // Simple value for each process: 1, 2, 3, ...

    // Perform reduction operations with root process 0 collecting the results
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    // Print results on root process
    if (rank == 0) {
        printf("SUM = %d\n", sum);
        printf("MAX = %d\n", max);
        printf("MIN = %d\n", min);
        printf("PROD = %d\n", prod);
    }

    MPI_Finalize();  // Clean up MPI environment
    return 0;
}


// mpicc pg4a.c -o reduce
// mpirun -np 4 ./reduce

// SUM = 10
// MAX = 4
// MIN = 1
// PROD = 24
---------------------------------------------------------------------------------------------------------------------

// Demonstration of MPI_Allreduce (all processes receive the reduced result)
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value, sum;

    MPI_Init(&argc, &argv);  // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    value = rank + 1;  // Simple value for each process: 1, 2, 3, ...

    // Perform allreduce summation: all processes get the sum result
    MPI_Allreduce(&value, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d got SUM = %d\n", rank, sum);

    MPI_Finalize();  // Clean up MPI environment
    return 0;
}

// mpicc pg4b.c -o allreduce
// mpirun -np 4 ./allreduce

// Process 0 got SUM = 10
// Process 1 got SUM = 10
// Process 2 got SUM = 10
// Process 3 got SUM = 10
