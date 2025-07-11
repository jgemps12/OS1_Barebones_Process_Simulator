#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdlib.h>
#include <string.h>
#include <signal.h>


/*************************FUNCTiION PROTOTYPES********************************/

// For user input validation.
void checkForOptargEntryError(int, char []);
void checkForSimulExceedsProcError(int, int);

// For guiding the user.
void printHelpMessage();



#endif
