`np` stands for "number of processes."

To compile
`mpicc src.c -o src.out -lm`

To run
`mpicc -np 1 ./src.out`

## Send and Receive

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

### Send modes
https://iamsorush.com/posts/mpi-send-types/

* [`MPI_Send()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-send-function) -- returns when it is safe to reuse the buffer (might be before the message is received)
* [`MPI_Ssend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-ssend-function) -- returns only after the message is received
* [`MPI_Bsend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-bsend-function) -- returns immediately, no blocking, data copied immediately to local buffer

[Notes on MPI_Bsend](https://www.open-mpi.org/doc/v3.0/man3/MPI_Bsend.3.php#toc8) by the OpenMPI docs.

## Collective communication

```c
MPI_Barrier(MPI_Comm communicator)

MPI_Bcast(
    void* data,
    int count,
    MPI_Datatype datatype,
    int root,
    MPI_Comm communicator
)

MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator
)

MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator
)

MPI_Allgather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    MPI_Comm communicator
)
```

## Unresolved

Do I use `MPI_Barrier()` for lab03-q4?