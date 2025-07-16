#include "functions.h"
#include <sys/wait.h>
#include <stdio.h>


/************************************************USER INPUT VALIDATION*************************************************/
// Displays error message if user uses correct arguments, but inputs negative numbers.
// Also enforces a maximum of 10 for '-n [proc]' argument. This ensures the opsys server's efficient execution of './oss'.
void checkForOptargEntryError(int value, char getoptArgument[]) {
   if ((value <= 0 || value > 10)  && (strcmp(getoptArgument, "-n [proc]") == 0)) {
      printf("ERROR in oss.c: User must enter an integer between 1 and 10 for argument %s.\n\n", getoptArgument);

      exit(-1);
   }
   if (value <= 0 && (strcmp(getoptArgument, "-n [proc]") != 0)) {
      printf("ERROR in oss.c: User must enter a positive integer for argument %s.\n\n", getoptArgument);

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

/***************************************************USER GUIDANCE******************************************************/
// Displays a help message if user enters './oss -h'.
void printHelpMessage() {
   printf("\n\n\nThis program displays information about child and parent processes, including:\n");
   printf("\t1.) Process IDs (or PIDs).\n");
   printf("\t2.) Parent process IDs (or PPIDs).\n");
   printf("\t3.) The iteration of a loop that displays PIDs and PPIDs.\n\n");

   printf("\n\nTo execute this program, type './oss', then type in any combination of options:\n");
   printf("Option:           What to enter after option:              Required (yes/no):             Description:\n");
   printf("  -h                nothing.                                 no                             Displays this help menu.\n");
   printf("  -n [proc]         an integer between 1 and 10.             no; defaults to 1.             Runs a total # of processes.\n");
   printf("  -s [simul]        an integer smaller than '-n [proc]'.     no; defaults to 1.             Runs a max # of processes simultaneously.\n");
   printf("  -t [iter]         an integer of at least 1.                no; defaults to 1.             Iterates through all processes a total # of times.\n\n");

   printf("For example, typing './oss -n 6 -s 4 -t 2' will run:\n");
   printf("\t1.) a total of 6 processes.\n");
   printf("\t2.) a maximum of 4 processes simultaneously.\n");
   printf("\t3.) a total of 2 iterations (i.e., 6 processes will begin and terminate twice, with up to 4 running simultaneously).\n\n\n");

   exit(0);
}
