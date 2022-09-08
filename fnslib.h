/* file name: fnslib.h
 * last name: Kravitz
 * first name: Steven
 * LU email: swk324@lehigh.edu
 */

#ifndef FNSLIB_H
#define FNSLIB_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t Fork(void);
int Kill(pid_t, int);
pid_t Wait(int *);
pid_t Waitpid(pid_t, int *, int);
void Pause();
void signal_handler(int);
ssize_t sio_puts(char *);
ssize_t sio_putl(long);
void sio_error(char *);
ssize_t Sio_puts(char *);
ssize_t Sio_putl(long);
void Sio_error(char *);
#endif
