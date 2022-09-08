/* file name: fnslib.c
 * last name: Kravitz
 * first name: Steven
 * LU email: swk324@lehigh.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "fnslib.h"

extern volatile char signame[32][10];
extern volatile char sigpurp[32][10];

//Steven's style wrapper for fork
pid_t Fork(void){
	pid_t pid;
	if((pid = fork()) == -1){
		fprintf(stderr, "fork error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pid;
}

//Steven's style wrapper for kill
int Kill(pid_t pid, int sig){
	int rc;
	if((rc = kill(pid, sig)) == -1){
		fprintf(stderr, "kill error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return rc;
}

//Steven's style wraper for Wait
pid_t Wait(int *wstatus){
	pid_t pid;
	if((pid = wait(wstatus)) == -1){
		fprintf(stderr, "wait error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pid;
}

//Steven's style wrapper for Waitpid
pid_t Waitpid(pid_t pid, int *wstatus, int options){
	pid_t retpid;
	if((retpid = waitpid(pid, wstatus, options)) == -1){
		fprintf(stderr, "waitpid error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pid;
}

//Steven's style wrapper for pause
void Pause(){
	(void)pause();
	return;
}

//Signal handler
/* G0: The function is very simple. It does not have extranious details
 * G1: The function does not use printf(), rather it uses the aysnc safe Sio_puts() function
 * G2: The function saves errno as olderrno and restores it at the end
 * G3: The function blocks all signals to protect the shared data
 * G4: global flags are stored as volatile
 * G5: there are no global flags but I would declare them as volatile sig_atomic_t if there were any.
 */
void signal_handler(int signum){
	int olderrno = errno;
	sigset_t mask, prevMask;
	sigfillset(&mask);
	sigprocmask(SIG_SETMASK, &mask, &prevMask);
	Sio_puts("Parent process caught ");
	Sio_puts(signame[signum]);
	Sio_puts(" ");
	Sio_puts(sigpurp[signum]);
	Sio_puts("\n");
	sigprocmask(SIG_SETMASK, &prevMask, NULL);
	errno = olderrno;
}

/*csapp safe I/O libary functions*/

//SIO func for reversing strings
static void sio_reverse(char *s){
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

//SIO func for converting a long into a string
static void sio_ltoa(long v, char *s, int b){
	int c, i = 0;
	int neg = v < 0;
	if(neg){
		v = -v;
	}
	do{
		s[i++] = ((c = (v % b)) < 10)  ?  c + '0' : c - 10 + 'a';
	}while ((v /= b) > 0);
	if(neg){
		s[i++] = '-';
	}
	s[i] = '\0';
	sio_reverse(s);
}

//SIO func for getting strlen
static size_t sio_strlen(char *s){
	int i = 0;
	while(s[i] != '\0'){
		++i;
	}
	return i;
}

//SIO func for printing strings
ssize_t sio_puts(char *s){
	return write(STDOUT_FILENO, s, sio_strlen(s));
}

//SIO func for printing longs
ssize_t sio_putl(long v){
	char s[128];
	sio_ltoa(v, s, 10);
	return sio_puts(s);
}

//SIO func for printing an error
void sio_error(char *s){
	sio_puts(s);
	_exit(1);
}

/*Wrappers for safe I/O library functions*/

//wrapper for sio_puts
ssize_t Sio_puts(char *s){
	ssize_t n;
	if((n = sio_puts(s)) < 0){
		sio_error("Sio_puts error");
	}
	return n;
}

//wrapper for sio_putl
ssize_t Sio_putl(long v){
	ssize_t n;
	if((n = sio_putl(v)) < 0){
		sio_error("Sio_putl error");
	}
	return n;
}

//wrapper for sio_error
void Sio_error(char *s){
	sio_error(s);
}


