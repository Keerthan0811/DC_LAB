// Demonstration of MPI_Bcast (broadcast operation)
#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, data;

    MPI_Init(&argc, &argv);  // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    if (rank == 0) {
        data = 100;  // Value to broadcast from root process
        printf("Root process sending: %d\n", data);
    }

    // Broadcast the value of 'data' from root (rank 0) to all processes
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data = %d\n", rank, data);

    MPI_Finalize();  // Finalize MPI environment
    return 0;
}


mpicc pg3.c -o broadcast
mpirun -np 4 ./broadcast


Root process sending: 100
Process 0 received data = 100
Process 1 received data = 100
Process 2 received data = 100
Process 3 received data = 100
