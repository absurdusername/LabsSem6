#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int *read_list(char *prompt, int size);
int print_matrix(int *matrix);

int main() {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (16 % size != 0) {
        printf("16 not divisible by number of processes %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 0);
    }

    int m = 16 / size; // elements per processor

    int *matrix = NULL;

    if (rank == 0) {
        matrix = malloc(16 * sizeof(int));
        matrix = read_list("Enter 16 numbers: ", 16);
    }

    int *row = malloc(m * sizeof(int));
    MPI_Scatter(matrix, m , MPI_INT, row, m, MPI_INT, 0, MPI_COMM_WORLD);

    int *new_row = malloc(m * sizeof(int));
    MPI_Scan(row, new_row, m, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(new_row, m, MPI_INT, matrix, m, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
        print_matrix(matrix);

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

int print_matrix(int *matrix) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) 
            printf("%d ", matrix[4 * r + c]);
            
        printf("\n");
    }
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 