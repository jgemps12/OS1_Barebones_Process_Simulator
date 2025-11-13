# OS1: Barebones Process Simulator

This project simulates the behavior of a basic operating system. It launches a specific number of child processes--a maximum number of which can run simultaneously--over a specific number of loop iterations.

## Key Features:
- Executes a user-inputted number of child processes.
- Enforces a maximum number of child processes that can be run simultaneously.
- Implements:
  - `getopt()` for command line argument parsing.
  - `fork()` for process creation.
  - `waitpid()` for process control.
  - `sleep()` for printing messages every **1 second**.
- Prints out information about each child process, including its:
  - Process ID (PID).
  - Parent's process ID (PPID).
  - Status of child (i.e., before sleeping or after sleeping).
- Ensures a clean termination of all processes to avoid zombie processes.

## How to Compile and Run:

1.) To *compile* the program, type:
```bash
make
```
2.) To *run* the program, type:
```bash
./oss -n <process_count> -s <max_simultaneous_process_count> -t <iterations>
```
### Command-Line Options:

| Option | Argument Format              | Required (yes/no)  | Description                                                |
|--------|------------------------------|--------------------|------------------------------------------------------------|
|  `-h`  | *(none)*                     | No                 | Displays help menu, then terminates program.               |
|  `-n`  | an integer between 1 and 10. | No (default=1)     | Sets a total number of processes to run.                   |
|  `-s`  | an integer <= value of `-n`. | No (default=1)     | Sets a maximum number of processes to run simultaneously.  |
|  `-t`  | an integer >= 1.             | No (default=1)     | Sets number of times each process prints its information.  |

## Examples:
### Example 1:
Upon typing this command into the terminal:
```bash
./oss -n 2 -s 2 -t 4
```
The program runs:
- 2 processes **total**.
- 2 processes **simultaneously**.
- 4 **iterations** of each process (i.e., each child prints its PID and PPID three times).

#### Sample Output:
The program begins by launching 2 child processes (i.e., PIDs **3986223** and **3986224**) simultaneously. For each iteration, user.c calls **sleep()**, forcing each child to sleep for exactly 1 second before waking up. 
```bash
USER PID: 3986223   PPID: 3986222  Iteration: 1 ---before sleeping
USER PID: 3986224   PPID: 3986222  Iteration: 1 ---before sleeping
USER PID: 3986223   PPID: 3986222  Iteration: 1 ---after sleeping
USER PID: 3986223   PPID: 3986222  Iteration: 2 ---before sleeping
USER PID: 3986224   PPID: 3986222  Iteration: 1 ---after sleeping
USER PID: 3986224   PPID: 3986222  Iteration: 2 ---before sleeping
...
...
```
Once all 4 iterations are completed for each child, both processes will terminate before the program ends. Child termination is conducted by using a call to **waitpid()**.
```bash
...
...
USER PID: 3986223   PPID: 3986222  Iteration: 4 ---after sleeping
USER PID: 3986224   PPID: 3986222  Iteration: 4 ---after sleeping
All 2 children have finished running. Now terminating program.
```

### Example 2:
Similarly, if the user inputs this command:
```bash
./oss -n 8 
```
The program will run:
- 8 processes **total**.
- 1 process **simultaneously**.
- 1 **iteration** of each process.
#### Sample Output:
Since -s and -t values were not inputted prior to program execution, all 8 processes will sleep for a single iteration *one at a time*. **waitpid()** then terminates each child before the next one can launch.
```bash
USER PID: 3986788   PPID: 3986787  Iteration: 1 ---before sleeping
USER PID: 3986788   PPID: 3986787  Iteration: 1 ---after sleeping
USER PID: 3986789   PPID: 3986787  Iteration: 1 ---before sleeping
USER PID: 3986789   PPID: 3986787  Iteration: 1 ---after sleeping
USER PID: 3986790   PPID: 3986787  Iteration: 1 ---before sleeping
USER PID: 3986790   PPID: 3986787  Iteration: 1 ---after sleeping
...
...
```
Once the 8 child processes all sleep for 1 second *one time*, the program terminates.
```bash
...
...
USER PID: 3986795   PPID: 3986787  Iteration: 1 ---after sleeping
All 8 children have finished running. Now terminating program.
```

## Skills Learned:
- Created a simplified simulation for process management an operating system.
- Used `getopt()` for command-line parsing and input handling.
- Used `fork()` to create multiple child processes.
- Used `sleep()` for segueing the runtimes of each process.
- Used `waitpid()` to synchronize between child and parent processes.

## Tested On:
- Ubuntu 20.04.6 (LTS)
- GCC 10.5.0
- Make 4.2.1

## License:
This project is licensed under the [MIT License](LICENSE).
