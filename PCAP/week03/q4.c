#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

char *read_string();

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *S1 = NULL, *S2 = NULL;
    int n = 0; // string length / number of processes

    if (rank == 0) {
        printf("Enter S1\n");
        S1 = read_string();

        int length = strlen(S1);

        if (length % size != 0) {
            printf("Length %d is not divisible by %d.\n", length, size);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        printf("Enter S2\n");
        S2 = read_string();

        if (strlen(S2) != length) {
            printf("Strings must be of the same length.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        n = length / size;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char *local_S1 = malloc(n * sizeof(char));
    MPI_Scatter(S1, n, MPI_CHAR, local_S1, n, MPI_CHAR, 0, MPI_COMM_WORLD);

    char *local_S2 = malloc(n * sizeof(char));
    MPI_Scatter(S2, n, MPI_CHAR, local_S2, n, MPI_CHAR, 0, MPI_COMM_WORLD);

    char *local_result = malloc(2 * n * sizeof(char));
    for (int i = 0; i < n; i++) {
        local_result[i] = local_S1[i];
        local_result[n + i] = local_S2[i];
    }

    printf("Process %d, local result: %s\n", rank, local_result);

    char *results = NULL;
    if (rank == 0)
        results = malloc((2 * n + 1) * sizeof(char));
    
    MPI_Gather(local_result, 2 * n, MPI_CHAR, results, 2 * n, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        results[2 * size * n] = '\0';
        printf("Process 0, aggregate result: %s\n", results);
    }

    MPI_Finalize();
    return 0;
}

char *read_string() {
    char buffer[1024];
    
    fflush(stdin);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strlen(buffer) - 1] = '\0';

    return strdup(buffer);
}
