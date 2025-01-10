#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int *read_list(int size) {
    int *list = malloc(size * sizeof(int));

    printf("Enter the numbers: \n");
    for (int i = 0; i < size; i++) 
        scanf("%d", list + i);
    
    return list;
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

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *numbers = NULL;
    if (rank == 0) 
        numbers = read_list(size);
    
    int local_number;
    MPI_Scatter(
        numbers, // sendbuf
        1, // sendcount
        MPI_INT, // sendtype
        &local_number, // recvbuf
        1, // recvcount, same as sendcount
        MPI_INT, // recvtype, same as sendtype
        0, // root
        MPI_COMM_WORLD
    );

    int local_result = factorial(local_number);
    printf("Process %d, local result: %d\n", rank, local_result);

    int *results = NULL;
    if (rank == 0)
        results = malloc(size * sizeof(int));
    
    MPI_Gather(
        &local_result, // sendbuf
        1, // sendcount
        MPI_INT, // sendtype
        results, // recvbuf
        1, // recvcount (for a single receive)
        MPI_INT, // recvtype
        0, // root
        MPI_COMM_WORLD
    );

    if (rank == 0) {
        int aggregate = sum(results, size);
        printf("Process 0, aggregate: %d\n", aggregate);
    }

    MPI_Finalize();
    return 0;
}