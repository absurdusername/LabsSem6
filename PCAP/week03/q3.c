#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

char *read_string();
int count_vowels(char *string, int length);
int sum(int *list, int size);

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc; // string length / size
    char *string = NULL;

    if (rank == 0) {
        printf("Enter a string\n");
        string = read_string();
        int length = strlen(string);

        if (length % size != 0) {
            printf("String length %d not divisible by %d.\n", length, size);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        elements_per_proc = length / size;
    }

    MPI_Bcast(&elements_per_proc, 1, MPI_INT, 0, MPI_COMM_WORLD);

    char *local_data = malloc(elements_per_proc * sizeof(char));
    MPI_Scatter(
        string, 
        elements_per_proc, 
        MPI_CHAR, 
        local_data, 
        elements_per_proc,
        MPI_CHAR,
        0,
        MPI_COMM_WORLD
    );

    int local_result = count_vowels(local_data, elements_per_proc);
    printf("Process %d, local result: %d\n", rank, local_result);

    int *results;
    if (rank == 0) 
        results = malloc(size * sizeof(int));
    MPI_Gather(&local_result, 1, MPI_INT, results, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int aggregate = sum(results, size);
        printf("Process 0, aggregate: %d\n", aggregate);
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

int count_vowels(char *string, int length) {
    int result = 0;

    for (int i = 0; i < length; i++) {
        char ch = string[i];

        // lowercase letters have the 6th LSB as 1
        if (ch & 32)
            ch -= 32;

        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
            result += 1;
    }

    return result;
}

int sum(int *list, int size) {
    int result = 0;
    for (int i = 0; i < size; i++)
        result += list[i];
    return result;
}
