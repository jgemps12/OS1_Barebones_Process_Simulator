/* Jesse Gempel
 * 2/6/2025
 * Professor Mark Hauschild
 * CMP SCI 4760-001
*/


// The user,c file works with CHILD processes.
// It prints out child and parent process IDs to the user for a user-specified number of iterations.


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char** argv) {
   int iter;

   // If executing ./user [iter], user must enter an integer after ./user.
   // Otherwise, present error and terminate program.
   if (argc != 2) {
      printf("ERROR in 'user.c': You must enter ./user followed by a single integer.\n");
      printf("\tExample: ./user 5\n");

      exit(-1);
   }


   // Store user input that determines how many times the for-loop below will iterate.
   if (argc == 2) { 
      iter = atoi(argv[1]);
   }


   // Output each child's Process ID and its parents Process ID [iter] number of times.
   // Perform sleep operation during an iteration.
   int i;
   for (i = 0; i < iter; i++) {
      printf("USER PID: %d   PPID: %d  Iteration: %d ---before sleeping\n", getpid(), getppid(), i + 1);
      sleep(1);

      printf("USER PID: %d   PPID: %d  Iteration: %d ---after sleeping\n\n", getpid(), getppid(), i + 1);
   }


   return EXIT_SUCCESS;

}

