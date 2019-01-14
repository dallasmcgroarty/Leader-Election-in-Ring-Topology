/*
Dallas McGroarty
Project 2
CPSC 474-01
12/7/18
*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lead_msg[3] = {0,0,0}; //small array message to hold ID and rank and message counter
int elected = 0; //to tell if a process was elected leader and exit loop
int hops = 0; // hold number of hops
int main(int argc, char** argv) {

  MPI_Init(NULL, NULL);

  // Get the number of processes
  int comm_size;
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  // Get the rank of the process
  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  //process ID
  int proc_ID;

    //create random id for each process
  srand(time(NULL) + my_rank);
    //ID is in proportion to the comm size
  if (hops == 0) {
    proc_ID = rand() % comm_size;
    lead_msg[0] = proc_ID;
    lead_msg[1] = my_rank;
    }
    //send the message
    MPI_Send(&lead_msg, 3, MPI_INT, (my_rank + 1) % comm_size, 0, MPI_COMM_WORLD);
    printf("Process %d with ID %d, sending message to process %d\n", my_rank, proc_ID, my_rank+1);
  
  //loop until a leader is elected
  while (elected != 1){
  //if rank = 0 receive from the last process, comm_size - 1
  if (my_rank == 0){
    MPI_Recv(&lead_msg, 3, MPI_INT, comm_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d with ID %d, receiving message from process %d\n", my_rank, proc_ID, comm_size-1);
    }
  //if rank not 0 then receive from previous process
  if (my_rank != 0) {
    MPI_Recv(&lead_msg, 3, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d with ID %d, receiving message from process %d\n", my_rank, proc_ID, my_rank-1);
    }
  //
  if (lead_msg[0] < proc_ID){
        lead_msg[0] = proc_ID;
        lead_msg[1] = my_rank; 

    }
  else if (lead_msg[0] == proc_ID && lead_msg[1] < my_rank){
        lead_msg[0] = proc_ID;
        lead_msg[1] = my_rank;

    }
    hops += 1;
    lead_msg[2] = hops;
  
  //if a process recieves its own message and hops = comm_size, then it is the leader
  if (lead_msg[0] == proc_ID && lead_msg[1] == my_rank && lead_msg[2] == comm_size){
    printf("Process %d with ID %d has been elected leader\n", my_rank, proc_ID);
    elected = 1;
    MPI_Abort(MPI_COMM_WORLD,-1); //MPI Abort to close all processes
    }

    MPI_Send(&lead_msg, 3, MPI_INT, (my_rank + 1) % comm_size, 0, MPI_COMM_WORLD);
    printf("Process %d with ID %d, sending message to process %d\n", my_rank, proc_ID, my_rank+1);
   }

};
