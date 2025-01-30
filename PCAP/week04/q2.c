#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 9

int *read_list(char *prompt, int size);
int count(int *list, int size, int element);

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (9 % size != 0) {
        printf("9 not divisible by number of processes %d\n");
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    int *matrix = NULL, element = 0;

    if (rank == 0) {
        matrix = malloc(MATRIX_SIZE * sizeof(int));
        matrix = read_list("Enter 9 numbers: ", 9);

        printf("Enter the element to be searched: ");
        scanf("%d", &element);
    }

    MPI_Bcast(&element, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *local_data = malloc((9 / size) * sizeof(int));
    MPI_Scatter(matrix, 9 / size , MPI_INT, local_data, 9 / size, MPI_INT, 0, MPI_COMM_WORLD);

    int local_result = count(local_data, 9 / size, element);
    printf("Process %d, local result: %d\n", rank, local_result);

    int global_result = 0;
    MPI_Reduce(&local_result, &global_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) 
        printf("Process 0, global result: %d\n", global_result);

    MPI_Finalize();
    return 0;
}

int *read_list(char *prompt, int size) {
    printf("%s", prompt);

    int *list = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) 
        scanf("%d", list + i);
    
    return list;
}

int count(int *list, int size, int element) {
    int result = 0;

    for (int i = 0; i < size; i++) {
        if (list[i] == element)
            result += 1;
    }

    return result;
}
