#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char string[] = "HELLO";
    string[rank] = string[rank] ^ ('a' - 'A'); // toggle
    printf("Rank %d: %s\n", rank, string);
    
    MPI_Finalize();
    return 0;
}