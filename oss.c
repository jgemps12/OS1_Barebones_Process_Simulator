/* Jesse Gempel
 * 2/6/2025
 * Professor Mark Hauschild
 * CMP SCI 4760-001
*/


// The oss.c file works with PARENT processes.
// It 


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


// Displays error message if user uses correct arguments, but inputs negative numbers or those greater than 10.
// A maximum of 10 ensures that the opsys server can handle execution of the './oss' operation.
void checkForOptargError(int value, char getoptArgument[]) {
   if (value <= 0 || value > 10) {
      printf("ERROR in oss.c: User must enter a number between 1 and 10 for argument %s.\n\n", getoptArgument);
 
      exit(-1);
      
   }
}


// Displays error message if # of simlataneous processes exceeds the total process count.
void checkForSimulExceedsProcError(int simulProcesses, int totalProcesses) {
   if (simulProcesses > totalProcesses) {
      printf("ERROR in oss.c: The -s [simul] value '%d' cannot be greater than the -n [proc] value '%d'.\n\n", simulProcesses, totalProcesses);

      exit(-1);
   }
}


int main(int argc, char** argv) {
   
   int opt; 

   // If user does not use -n [proc], -s [simul], or -t [iter] arguments, assign default values.
   int proc = 1;
   int simul = 1;
   int iter = 1;


   // If user puts invalid values for opt arguments, one of these strings will be passed into 'checkForOptargError()'.
   // This will tell the user where the error occurred when trying to execute './oss'.
   char procName[] = "-n [proc]";
   char simulName[] = "-s [simul]";
   char iterName[] = "-t [iter]";


   while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
      switch (opt) {
         case 'h':
            printf("help\n");
	    exit(0);

	    break;

         case 'n':
            proc = atoi(optarg);
	    checkForOptargError(proc, procName);

            break;

         case 's':
            simul = atoi(optarg);
            checkForOptargError(simul, simulName);
	    checkForSimulExceedsProcError(simul, proc);

            break;

         case 't':
            iter = atoi(optarg);
            checkForOptargError(iter, iterName);

            break;

         default:
	    printf("ERROR in oss.c: Arguments are invalid or you forgot to input a value for them.\n");
	    printf("Please type './oss -h' for help.\n\n");

            exit(-1);

 	    break;
      }
   }

   printf("proc = %d \t simul = %d \t iter = %d\n", proc, simul, iter);


   // Split a child process from a parent.
   pid_t childPid = fork();

   

   return EXIT_SUCCESS;
}


