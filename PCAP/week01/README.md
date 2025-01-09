`np` stands for "number of processes."

To compile
`mpicc src.c -o src.out -lm`

To run
`mpicc -np 1 ./src.out`

Reference on `MPI_Send` and `MPI_Receive`
https://mpitutorial.com/tutorials/mpi-send-and-receive/

```c
MPI_Send(
    void* data,
    int count,
    MPI_Datatype datatype,
    int destination,
    int tag,
    MPI_Comm communicator
)

MPI_Recv(
    void* data,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm communicator,
    MPI_Status* status
)
```
