#include <stdio.h>
#include "mpi.h"

int factorial(int x);
int fibonacci(int x);

int main(int argc, char *argv[]) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank & 1) // Odd 
        printf("%d\n", fibonacci(rank));
    else
        printf("%d\n", factorial(rank));
    
    MPI_Finalize();
    return 0;
}

int factorial(int x) {
    int result = 1;

    for (int i = 2; i <= x; i++) 
        result *= i;

    return result;
}

int fibonacci(int x) {
    int a = 0, b = 1;

    for (int i = 1; i <= x - 1; i++) {
        int tmp = a;
        a = b;
        b = b + tmp;
    }

    return b;
}