#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            int data = 10 * i;
            MPI_Send(
                &data,          // data
                1,              // count
                MPI_INT,        // datatype
                i,              // destination
                0,              // tag
                MPI_COMM_WORLD  // communicator
            );
        }
    } else {
        int number;

        MPI_Recv(
            &number,            // data
            1,                  // count
            MPI_INT,            // datatype
            MPI_ANY_SOURCE,     // source (0)
            MPI_ANY_TAG,        // tag (0)
            MPI_COMM_WORLD,     // communicator
            MPI_STATUS_IGNORE   // status, alternatively declare `MPI_Status status` and pass `&status`
        );

        printf("Process %d: %d\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}