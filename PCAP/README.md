`np` stands for "number of processes."

To compile
`mpicc src.c -o src.out -lm`

To run
`mpirun -np 1 ./src.out`

## Send and Receive

See [week02q2](week02/q2.c) for `MPI_Send()` and `MPI_Recv()`.

```c
MPI_Send(
    &data,          // data
    1,              // count
    MPI_INT,        // datatype

    i,              // destination
    0,              // tag
    MPI_COMM_WORLD  // communicator
)

MPI_Recv(
    &number,            // data
    1,                  // count
    MPI_INT,            // datatype

    MPI_ANY_SOURCE,     // source (can also give a number!)
    MPI_ANY_TAG,        // tag (can also give a number!)
    MPI_COMM_WORLD,     // communicator
    
    MPI_STATUS_IGNORE   // alternatively declare `MPI_Status status` and pass `&status`
)
```

For `MPI_Bsend()` and its adjoining functions, revisit [week02q3](week02/q3.c).

```c
int buffer_size = (size - 1) * sizeof(int) + MPI_BSEND_OVERHEAD; 
void *buffer = malloc(buffer_size);

MPI_Buffer_attach(buffer, buffer_size);

// using MPI_Bsend ...

MPI_Buffer_detach(&buffer, &buffer_size);
free(buffer);
```

"The MPI_Buffer_detach will not complete until all buffered messages are delivered." -- [Notes on MPI_Bsend](https://www.open-mpi.org/doc/v3.0/man3/MPI_Bsend.3.php#toc8) by the OpenMPI docs. 

### Send modes
https://iamsorush.com/posts/mpi-send-types/

* [`MPI_Send()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-send-function) -- returns when it is safe to reuse the buffer (might be before the message is received)
* [`MPI_Ssend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-ssend-function) -- returns only after the message is received
* [`MPI_Bsend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-bsend-function) -- returns immediately, no blocking, data copied immediately to local buffer

## Collective communication

```c
MPI_Barrier(MPI_COMM_WORLD)

MPI_Bcast(
    &x,             // data
    1,              // count
    MPI_INT,        // datatype

    0,              // root
    MPI_COMM_WORLD  // communicator
)

MPI_Scatter(
    ten_numbers,    // send_data
    2,              // send_count (elements per processsor)
    MPI_INT,        // send_datatype

    two_numbers,    // recv_data
    2,              // recv_count (same as before)
    MPI_INT,        // recv_datatype (same as before)

    0,              // root
    MPI_COMM_WORLD
)

MPI_Gather(
    &local_result,  // send_data
    1,              // send_count (for a single send)
    MPI_INT,        // send_datatype 

    total_results,  // recv_data
    1,              // recv_count (same as before)
    MPI_INT,        // recv_datatype (same as before)

    0,              // root
    MPI_COMM_WORLD
);

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

Do I use `MPI_Barrier()` for lab03-q4?`np` stands for "number of processes."

To compile
`mpicc src.c -o src.out -lm`

To run
`mpirun -np 1 ./src.out`

## Send and Receive

See [week02q2](week02/q2.c) for `MPI_Send()` and `MPI_Recv()`.

```c
MPI_Send(
    &data,          // data
    1,              // count
    MPI_INT,        // datatype

    i,              // destination
    0,              // tag
    MPI_COMM_WORLD  // communicator
)

MPI_Recv(
    &number,            // data
    1,                  // count
    MPI_INT,            // datatype

    MPI_ANY_SOURCE,     // source (can also give a number!)
    MPI_ANY_TAG,        // tag (can also give a number!)
    MPI_COMM_WORLD,     // communicator
    
    MPI_STATUS_IGNORE   // alternatively declare `MPI_Status status` and pass `&status`
)
```

For `MPI_Bsend()` and its adjoining functions, revisit [week02q3](week02/q3.c).

```c
int buffer_size = (size - 1) * sizeof(int) + MPI_BSEND_OVERHEAD; 
void *buffer = malloc(buffer_size);

MPI_Buffer_attach(buffer, buffer_size);

// using MPI_Bsend ...

MPI_Buffer_detach(&buffer, &buffer_size);
free(buffer);
```

"The MPI_Buffer_detach will not complete until all buffered messages are delivered." -- [Notes on MPI_Bsend](https://www.open-mpi.org/doc/v3.0/man3/MPI_Bsend.3.php#toc8) by the OpenMPI docs. 

### Send modes
https://iamsorush.com/posts/mpi-send-types/

* [`MPI_Send()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-send-function) -- returns when it is safe to reuse the buffer (might be before the message is received)
* [`MPI_Ssend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-ssend-function) -- returns only after the message is received
* [`MPI_Bsend()`](https://learn.microsoft.com/en-us/message-passing-interface/mpi-bsend-function) -- returns immediately, no blocking, data copied immediately to local buffer

## Collective communication

```c
MPI_Barrier(MPI_COMM_WORLD)

MPI_Bcast(
    &x,             // data
    1,              // count
    MPI_INT,        // datatype

    0,              // root
    MPI_COMM_WORLD  // communicator
)

MPI_Scatter(
    ten_numbers,    // send_data
    2,              // send_count (elements per processsor)
    MPI_INT,        // send_datatype

    two_numbers,    // recv_data
    2,              // recv_count (same as before)
    MPI_INT,        // recv_datatype (same as before)

    0,              // root
    MPI_COMM_WORLD
)

MPI_Gather(
    &local_result,  // send_data
    1,              // send_count (for a single send)
    MPI_INT,        // send_datatype 

    total_results,  // recv_data
    1,              // recv_count (same as before)
    MPI_INT,        // recv_datatype (same as before)

    0,              // root
    MPI_COMM_WORLD
);

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
