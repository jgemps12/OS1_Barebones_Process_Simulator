// The oss.c file works with PARENT processes.
// It launches a specific number of user processes with user input gathered from the 'getopt()' switch statement. 
#include "functions.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char** argv) {
	int opt; 
	
	// If user does not use -n [proc], -s [simul], or -t [iter] arguments, assign default values.
	int proc = 1;
	int simul = 1;
	int iter = 1;
	
	// If user puts invalid values for opt arguments, one of these strings will be passed into 'checkForOptargError()'.
	// This will help state the option in which the error occurred while trying to execute './oss'.
	char procName[] = "-n [proc]";
	char simulName[] = "-s [simul]";
	char iterName[] = "-t [iter]";
	
	while ((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
		switch (opt) {
			case 'h':
				printHelpMessage();
				break;
			
			case 'n':
				proc = atoi(optarg);
				checkForOptargEntryError(proc, procName);
				break;
			
			case 's':
				simul = atoi(optarg);
				checkForOptargEntryError(simul, simulName);
				checkForSimulExceedsProcError(simul, proc);
				break;
			
			case 't':
				iter = atoi(optarg);
				checkForOptargEntryError(iter, iterName);
				break;
			
			default:
				printf("ERROR in oss.c: Arguments are invalid or you forgot to input a value for them.\n");
				printf("Please type './oss -h' for help.\n\n");
				exit(-1);
				
				break;
		}
	}
	
	bool processesFinished = false;
	int childrenActive = 0;                                          // # of children running simultaneously (not to be confused with 'proc').
	int totalChildrenLaunched = 0;                                   // # of children launched so far (not to be confused with 'simul').
	
	// Stores the total iteration count into string to facilatate execl()'s operation.
	char iteration_count[50];                                     
	sprintf(iteration_count, "%d", iter);
	
	while (processesFinished == false) {
		// If not all possible children are run yet AND the # of simultaneous children is less than maximum, continue running processes.
		
		if (childrenActive < simul && totalChildrenLaunched < proc) {
			// Split a child process from a parent.
			pid_t childPid = fork();
			
			// Work with child process. Send [iter] to user.c to execute the child process.
			if (childPid == 0) {
				execl("./user", "user", iteration_count, NULL);
				
				printf("ERROR in oss.c: the execl() function has failed. Terminating program.\n\n");
				exit(-1);
			}
			
			// Work with parent process. Increment the current # of total children and those running simultaneously.
			else if (childPid > 0) {
				childrenActive++;
				totalChildrenLaunched++;
			}
			
			else {
				printf("ERROR in oss.c: the fork() function has failed. Terminating program.\n\n");
				exit(-1);
			}
		}  
		
		// If no more children are running and the maximum # of total children have been launched, end loop/program.
		if (childrenActive == 0 && totalChildrenLaunched == proc) {
			printf("All %d children have finished running. Now terminating program.\n", proc);
			processesFinished = true;
		}
		
		// If the limit of simultaneous children has been reached, but more still need to be launched, wait for them to terminate.
		if (childrenActive == simul && totalChildrenLaunched < proc) {
			waitpid(-1, NULL, 0);
			childrenActive--;
		}
		
		// If all available children have launched, but not all of them finished, wait for them to terminate.
		if (childrenActive > 0 && totalChildrenLaunched == proc) {
			waitpid(-1, NULL, 0);
			childrenActive--; 
		}
	}
	
	return EXIT_SUCCESS;
}
