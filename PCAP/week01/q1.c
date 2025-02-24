#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define x 5

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Process %d, x^rank: %f\n", rank, pow(x, rank));

    MPI_Finalize();
    return 0;
}