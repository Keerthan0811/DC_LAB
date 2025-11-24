// Demonstration of MPI_Scatter and MPI_Gather
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);  // Initialize MPI environment

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get current process rank
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Get total number of processes

    int send[100], recv, gather[100];

    // Initialize data to be scattered by rank 0
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            send[i] = i + 1;  // 1, 2, 3, ...
        }
    }

    // Scatter one integer to each process
    MPI_Scatter(send, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d received %d\n", rank, recv);

    // Each process modifies its received data
    recv = recv * 10;

    // Gather the modified data back to rank 0
    MPI_Gather(&recv, 1, MPI_INT, gather, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Gathered: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", gather[i]);
        }
        printf("\n");
    }

    MPI_Finalize();  // Finalize MPI environment
    return 0;
}


// mpicc pg2.c -o sg
// mpirun -np 4 ./sg

// Rank 1 received 2
// Rank 2 received 3
// Rank 3 received 4
// Rank 0 received 1
// Gathered: 10 20 30 40
