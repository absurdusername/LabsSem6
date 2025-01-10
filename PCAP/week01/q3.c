#include <stdio.h>
#include "mpi.h"
#define A 5
#define B 10

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        printf("Rank %d: A + B = %d\n", rank, A + B);
    else if (rank == 1) 
        printf("Rank %d: A - B = %d\n", rank, A - B);
    else if (rank == 2) 
        printf("Rank %d: A * B = %d\n", rank, A * B);
    else if (rank == 3)
        printf("Rank %d: A / B = %d\n", rank, A / B);
    
    MPI_Finalize();
    return 0;
}