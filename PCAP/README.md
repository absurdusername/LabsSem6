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

### Send modes
https://iamsorush.com/posts/mpi-send-types/

* [`MPI_Send()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-send-function) -- returns when it is safe to reuse the buffer (might be before the message is received)
* [`MPI_Ssend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-ssend-function) -- returns only after the message is received
* [`MPI_Bsend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-bsend-function) -- returns immediately, no blocking, data copied immediately to local buffer

[Notes on MPI_Bsend](https://www.open-mpi.org/doc/v3.0/man3/MPI_Bsend.3.php#toc8) by the OpenMPI docs.

### Unresolved questions

Buffer is only used for reading, then why wait for it to be freed?