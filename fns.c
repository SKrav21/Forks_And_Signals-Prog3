/* file name: fns.c
 * last name: Kravitz
 * first name: Steven
 * LU email: swk324@lehigh.edu
 */

#include "fnslib.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "fnslib.h"
#include <time.h>

#ifndef NUMCHILDREN
#define NUMCHILDREN 8
#endif

char signame[32][10];  /* array to hold signal names */
char sigpurp[32][60];  /* array to hold signal purposes */

int main() {

  strcpy(signame[0],  "UNUSED");     strcpy(sigpurp[0],  "Unused");
  strcpy(signame[1],  "SIGHUP");     strcpy(sigpurp[1],  "Hangup (POSIX)");
  strcpy(signame[2],  "SIGINT");     strcpy(sigpurp[2],  "Interrupt (ANSI)");
  strcpy(signame[3],  "SIGQUIT");    strcpy(sigpurp[3],  "Quit (POSIX)");
  strcpy(signame[4],  "SIGILL");     strcpy(sigpurp[4],  "Illegal instruction (ANSI)");
  strcpy(signame[5],  "SIGTRAP");    strcpy(sigpurp[5],  "Trace trap (POSIX)");
  strcpy(signame[6],  "SIGIOT");     strcpy(sigpurp[6],  "IO trap (4.2 BSD); SIGABRT - Abort (ANSI)");
  strcpy(signame[7],  "SIGBUS");     strcpy(sigpurp[7],  "BUS error");
  strcpy(signame[8],  "SIGFPE");     strcpy(sigpurp[8],  "Floating-point exception (ANSI)");
  strcpy(signame[9],  "SIGKILL");    strcpy(sigpurp[9],  "Kill, unblockable (POSIX)");
  strcpy(signame[10], "SIGUSR1");    strcpy(sigpurp[10], "User-defined signal 1 (POSIX)");
  strcpy(signame[11], "SIGSEGV");    strcpy(sigpurp[11], "Segmentation violation (ANSI)");
  strcpy(signame[12], "SIGUSR2");    strcpy(sigpurp[12], "User-defined signal 2 (POSIX)");
  strcpy(signame[13], "SIGPIPE");    strcpy(sigpurp[13], "Broken pipe (POSIX)");
  strcpy(signame[14], "SIGALRM");    strcpy(sigpurp[14], "Alarm clock (POSIX)");
  strcpy(signame[15], "SIGTERM");    strcpy(sigpurp[15], "Termination (ANSI)");
  strcpy(signame[16], "SIGSTKFLT");  strcpy(sigpurp[16], "Stack fault");
  strcpy(signame[17], "SIGCHLD");    strcpy(sigpurp[17], "Child status changed (POSIX); SIGCLD (System V)");
  strcpy(signame[18], "SIGCONT");    strcpy(sigpurp[18], "Continue (POSIX)");
  strcpy(signame[19], "SIGSTOP");    strcpy(sigpurp[19], "Stop, unblockable (POSIX)");
  strcpy(signame[20], "SIGTSTP");    strcpy(sigpurp[20], "Keyboard stop (POSIX)");
  strcpy(signame[21], "SIGTTIN");    strcpy(sigpurp[21], "Background read from tty (POSIX)");
  strcpy(signame[22], "SIGTTOU");    strcpy(sigpurp[22], "Background write to tty (POSIX)");
  strcpy(signame[23], "SIGURG");     strcpy(sigpurp[23], "Urgent condition on socket (4.2 BSD)");
  strcpy(signame[24], "SIGCPU");     strcpy(sigpurp[24], "CPU limit exceeded (4.2 BSD)");
  strcpy(signame[25], "SIGXFSZ");    strcpy(sigpurp[25], "File size limit exceeded (4.2 BSD)");
  strcpy(signame[26], "SIGVTALRM");  strcpy(sigpurp[26], "Virtual alarm clock (4.2 BSD)");
  strcpy(signame[27], "SIGPROF");    strcpy(sigpurp[27], "Profiling alarm clock (4.2 BSD)");
  strcpy(signame[28], "SIGWINCH");   strcpy(sigpurp[28], "Window size change (4.3 BSD, Sun)");
  strcpy(signame[29], "SIGIO");      strcpy(sigpurp[29], "I/O possible (4.2 BSD); Pollable event (System V)");
  strcpy(signame[30], "SIGPWR");     strcpy(sigpurp[30], "Power failure restart (System V)");
  strcpy(signame[31], "SIGSYS");     strcpy(sigpurp[31], "Bad system call");

  /* Reference print statements; use these as is (you can change the variable names):
   * "Parent process installing signal handlers\n"
   * "Child process %d sending %s to parent\n", childpid, signame
   * "Child process %d terminated normally with exit status %d\n", childpid, status
   * "Child process %d terminated abnormally\n", childpid
   * Look at the sample output to see the output from the signal handler and match that exactly (sans the signal name and purpose, which will vary).
   */

  	//This section installs the signal handlers
  	pid_t parentPid = getpid();
	pid_t childPid[NUMCHILDREN];
	sigset_t mask, prevMask;
	sigfillset(&mask);//blocks other signals
	sigprocmask(SIG_SETMASK, &mask, &prevMask);
	printf("Parent process installing signal handlers\n");
	struct sigaction sa;
	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	for(int i = 1; i <= 31; i++){//loops to create signal handler for all signals
		sigaction(i, &sa, NULL);
	}
	sigprocmask(SIG_SETMASK, &prevMask, NULL);
	

	//Section for creating the child processes and killing the signals
	for (int i = 0; i < NUMCHILDREN; i++){
		int sigNum = 0;
		if((childPid[i] = Fork()) == 0){
			do{//for getting a signal that isn't one of the ones that cannot be handled
				time_t t;
				srand((unsigned) time(&t));
				sigNum = rand() % 32;
			}while(sigNum == 9 || sigNum == 17 || sigNum == 19);
			printf("child process %d sending %s to parent\n", getpid(), signame[sigNum]);
			Kill(parentPid, sigNum);
			sleep((unsigned)(rand() % 6));
			exit(0);
		}
	}
	
	//This section  terminates the child processes
	int childStatus;
	for(int i = 0; i < NUMCHILDREN; i++){
		childPid[i] = wait(&childStatus);
		if(WIFEXITED(childStatus)){//if the process exits properly
			printf("Child process %d terminated normally with exit status %d\n", childPid[i], WEXITSTATUS(childStatus));
		}
		else{//if the process does not exit properly
			printf("Child process %d terminated abnormally\n", childPid[i]);
		}
	}
  return 0;
}













