# Leader-Election-in-Ring-Topology
by: Dallas McGroarty

program simulates leader election in a ring topology using MPI programming and C

Programmed and run on linux. 

To run in terminal: $mpiexec -n <number of processes> ./mpi_ring
  
Run the program and enter the number of processes you want to run in parallel (only tested with up to 8 processes)
The leader election works by having each process send a message to the process next to it in a directed ring. Each process compares its own ID and rank with the ID and rank in the message it received. If the ID or rank of the process is higher than the ID or rank in the message then the process updates the values with its own and sends the message to the next process. Otherwise, if the message contains higher values then the process just sends the original message. If a process receives its own message then we know it is the leader. It declares itself the leader and aborts the program.

Language: 
  program made using C along with MPI programming
 
