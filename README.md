# CSE202-Forks and Signals-SP2022
fns: A programming exercise to learn about forking to create processes and sending/handling signals

# Learning Objectives
1) Apply learning of fork() to create a process
2) Apply learning of kill() to send signals
3) Apply learning of sigaction() to handle signals
4) Apply learning of linking to create a shared library and have it dynamically loaded
5) Learn or apply learning of makefiles to support modular programming

# Instructions
Write a C program named fns.c to create a variable number of child processes from which a random signal will be sent to the parent which will be caught and handled.

In the parent process, you will need to install the same signal handler to catch any/all catchable signals (except SIGCHLD, as we want the default behavior for reaping).

Then, in each child process, you will randomly select a signal to send to the parent process. (Do not send a signal that will not be caught.) Further, so signals are arriving at different times, you must randomly delay 1 to 5 seconds between sending signals. After sending a signal from the child, you will exit that child process.

Then, in the parent process, you will need to reap all child processes using wait() or waitpid(). The status of each child process, when reaped, must be printed.

A skeleton fns.c file is provided that contains the declaration of arrays to hold the signal names and their purposes as well as various printf statements. Use these as is, so you match the output of the sample program and pass the checking program.

REQUIRED...
1) Your main() function must be in the fns.c file.
2) You must put your name and email address in a comment at the top of EVERY file you write. Note, '#' starts a comment in a makefile.
```
   /* file name: ___________ 
    * last name: ___________
    * first name: __________
    * LU email: ____________
    */
```
3) Your signal handler function must be named signal\_handler(); and you must use sigaction() (signal() is not allowed).
4) All functions, except main(), must be in the fnslib.c file; so, you will need to create a separate fnslib.c file (and associated .h) to contain the signal handler function and any other functions you create. 
5) You must compile the fnslib.c as a dynamic/shared library that is to be loaded at runtime.
6) You must check the return code of every system call; if a system call fails, you must exit with return code of the errno value associated with the system call.
7) You must write and submit a makefile (with a clean section to remove all make-generated files); so, you need to submit fns.c, fnslib.c, fnslib.h, and makefile (or Makefile).
8) You must write an async-signal-safe signal handler. 
9) You must put comments in your signal handler function describing which rules from the textbook you followed to create an async-signal-handler; if you feel one or more rules do not need to be followed, explain your rationale. 
10) And, of course, you must WORK INDEPENDENTLY - DO NOT LOOK AT ANYONE ELSE'S CODE OR SHARE YOUR CODE WITH ANYONE.

STRONGLY SUGGESTED...
1) Leverage the textbook and the online resources listed below.
2) Use Stevens-style wrapping to encapsulate all your error checking and handling in a function whose name is the capitalized version of the system call. For example, create a Fork() function call that calls fork() and checks/handles any errors. 
3) Work on this assignment a little every day... try NOT to procrastinate!

# Helpful Notes
1) Start small by setting NUMCHILDREN to 1 or 2.
2) Add comments to your code; it will help you, your score, and the graders!
4) Push your code often!!! This will give you a backup, enable you to retrieve earlier versions, and demonstrate you actually wrote the code over time. If you only perform one or two pushes of your code, your submission will be THOROUGHLY evaluated to ensure it is original. You need 10 or more pushes to get the maximum points.
6) To submit your code for grading, simply perform a "git push"; which will upload your changes to GitHub Classroom and run the auto-grader. You may continue to push changes until you are informed "All tests passed" or the deadline published on Coursesite has passed.
6) Refer to the Programming Assignment Grading Rubric on Coursesite to maximize your score.
7) Post any questions to Piazza.

# Resources
[Shared libraries](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)

[Sigaction](https://www.youtube.com/watch?v=jF-1eFhyz1U)

[Syscalls](https://man7.org/linux/man-pages/man2/syscalls.2.html)

[Signal safety](https://man7.org/linux/man-pages/man7/signal-safety.7.html)

# Sample Output (for NUMCHILDREN equal to 8)
```
Parent process installing signal handlers
Child process 7919 sending SIGSYS to parent
Parent process caught SIGSYS (Bad system call)
Child process 7925 sending SIGUSR1 to parent
Parent process caught SIGUSR1 (User-defined signal 1 (POSIX))
Child process 7931 sending SIGPWR to parent
Parent process caught SIGPWR (Power failure restart (System V))
Child process 7936 sending SIGUSR2 to parent
Parent process caught SIGUSR2 (User-defined signal 2 (POSIX))
Child process 7940 sending SIGPROF to parent
Parent process caught SIGPROF (Profiling alarm clock (4.2 BSD))
Child process 7945 sending SIGTSTP to parent
Parent process caught SIGTSTP (Keyboard stop (POSIX))
Child process 7953 sending SIGUSR1 to parent
Parent process caught SIGUSR1 (User-defined signal 1 (POSIX))
Child process 7919 terminated normally with exit status 0
Child process 7925 terminated normally with exit status 0
Child process 7931 terminated normally with exit status 0
Child process 7936 terminated normally with exit status 0
Child process 7940 terminated normally with exit status 0
Child process 7955 sending SIGPWR to parent
Child process 7945 terminated normally with exit status 0
Child process 7953 terminated normally with exit status 0
Parent process caught SIGPWR (Power failure restart (System V))
Child process 7955 terminated normally with exit status 0
```
