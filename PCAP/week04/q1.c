#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int sum(int *list, int size);
int factorial(int x);

int main() {
    MPI_Init(NULL, NULL);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_result = factorial(rank);
    printf("Process %d, local result: %d\n", rank, local_result);

    int aggregate = 0;
    int err = MPI_Reduce(
        &local_result,  // send_buf
        &aggregate,     // recv_buf
        1,              // count
        MPI_INT,        // datatype
        MPI_SUM,        // op
        0,              // root
        MPI_COMM_WORLD  // communicator
    );

    if (err != MPI_SUCCESS) {
        char *error_string = NULL;
        int size = 0;
        MPI_Error_string(err, error_string, &size);

        printf("%s\n", error_string);
        MPI_Abort(MPI_COMM_WORLD, err);
    }

    if (rank == 0) 
        printf("Process 0, aggregate: %d\n", aggregate);
    

    MPI_Finalize();
    return 0;
}

int factorial(int x) {
    int result = 1;

    for (int i = 1; i <= x; i++)
        result *= i;
    
    return result;
}

int sum(int *list, int size) {
    int result = 0;

    for (int i = 0; i < size; i++)
        result += list[i];
    
    return result;
}
