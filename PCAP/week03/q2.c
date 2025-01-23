#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float *read_list(int size);
float average(float *list, int size);

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int M;
    float *numbers;
    if (rank == 0) {
        printf("Enter M: \n");
        scanf("%d", &M);
        numbers = read_list(M * size);
    }
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);

    float *local_data = malloc(M * sizeof(float));
    MPI_Scatter(numbers, M , MPI_FLOAT, local_data, M, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float local_result = average(local_data, M);
    printf("Process %d, local result: %.2f\n", rank, local_result);

    float *results;
    if (rank == 0)
        results = malloc(size * sizeof(float));
    MPI_Gather(&local_result, 1, MPI_FLOAT, results, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        float aggregate = average(results, size);
        printf("Process 0, aggregate: %.2f\n", aggregate);
    }

    MPI_Finalize();
    return 0;
}

float *read_list(int size) {
    float *list = malloc(size * sizeof(float));

    printf("Enter %d numbers: \n", size);
    for (int i = 0; i < size; i++) 
        scanf("%f", list + i);
    
    return list;
}

float average(float *list, int size) {
    float result = 0;

    for (int i = 0; i < size; i++)
        result += list[i];
    
    return result / size;
}
