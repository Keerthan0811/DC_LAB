// Demonstration of MPI_Send and MPI_Recv
#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Initialize MPI environment

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    // Check if at least 2 processes are available
    if (size < 2) {
        if (rank == 0)
            printf("Run with at least 2 processes\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        int x = 10;
        // Send data to process 1
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 sent %d\n", x);
    }
    else if (rank == 1) {
        int y;
        // Receive data from process 0
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1 received %d\n", y);
    }

    MPI_Finalize();  // Clean up the MPI environment
    return 0;
}



// mpicc pg1.c -o pg1
// mpirun -np 2 ./pg1

// Rank 0 sent 10
// Rank 1 received 10
