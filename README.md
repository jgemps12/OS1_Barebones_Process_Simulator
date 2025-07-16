# OS1: Barebones Process Simulator

This project simulates the behavior of a basic operating system. It launches a specific number of child processes--a maximum number of which can run simultaneously--over a specific number of loop iterations.

## Key Features:
- Executes a user-inputted number of child processes.
- Enforces a maximum number of child processes that can be run simultaneously.
- Implements:
  - `getopt()` for command line argument parsing.
  - `fork()` for process creation.
  - `waitpid()` for process control.
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
./oss -n 6 -s 4 -t 3
```
The program runs:
- 6 processes **total**.
- 4 processes **simultaneously**.
- 3 **iterations** of each process (i.e., each child prints its PID and PPID three times).

#### Sample Output:
```bash
USER PID: 594836   PPID: 594834  Iteration: 1 ---before sleeping
USER PID: 594837   PPID: 594834  Iteration: 1 ---before sleeping
USER PID: 594835   PPID: 594834  Iteration: 1 ---before sleeping
USER PID: 594838   PPID: 594834  Iteration: 1 ---before sleeping
USER PID: 594836   PPID: 594834  Iteration: 1 ---after sleeping
...
...
USER PID: 594842   PPID: 594834  Iteration: 3 ---after sleeping
All 6 children have finished running. Now terminating program.
```

### Example 2:
Similarly, this command:
```bash
./oss -n 8 
```
The program runs:
- 8 processes **total**.
- 1 process **simultaneously**.
- 1 **iteration** of each process.
#### Sample Output:
```bash
USER PID: 595017   PPID: 595016  Iteration: 1 ---before sleeping
USER PID: 595017   PPID: 595016  Iteration: 1 ---after sleeping
USER PID: 595019   PPID: 595016  Iteration: 1 ---before sleeping
USER PID: 595019   PPID: 595016  Iteration: 1 ---after sleeping
...
...
USER PID: 595032   PPID: 595016  Iteration: 1 ---after sleeping
All 8 children have finished running. Now terminating program.
```

## Skills Learned:
- Created a simplified simulation for process management an operating system.
- Used `getopt()` for command-line parsing and input handling.
- Used `fork()` to create multiple child processes.
- Used `waitpid()` to synchronize between child and parent processes.

## Tested On:
- Ubuntu 20.04.6 (LTS)
- GCC 10.5.0
- Make 4.2.1

## License:
This project is licensed under the [MIT License](LICENSE).
