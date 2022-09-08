/*
 * chkLinks Supporting Functions
 * Program 3 assignment
 * CSE109 Fall 2021
 * student ID: swk324
 * student Last name: Kravitz
 * student First name: Steven
 * githubID: 78743146
 */
#ifndef SYSCALLS
#define SYSCALLS
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void *Malloc(size_t);								/*in: bytes to allocate; return: ptr of type void to allocated memory*/
FILE *Fopen(const char *, const char *);			/*in: oath/file, mode; return: file ptr*/
void Fclose(FILE *);								/*in: file ptr*/
size_t Fread(void *, size_t, size_t, FILE *);		/*in: buffer ptr, buffer size, num buffers, input file ptr; return: bytes read*/
size_t Fwrite(const void *, size_t, size_t, FILE *);/*in: buffer ptr, buffer size, numb buffers, output file ptr, return: bytes written*/
int Pipe(int []);									/*in: filedes[0] is for the read end and filedes[1] is for the write end, return: 0 on success*/
pid_t Fork(void);									/*out: negative if creation unsuccessful, 0 if returned to newly created process, positive is id of new child process*/
pid_t Wait(int *);									/*in: *wstatus is a signal from the OS whose default action is to terminate, returns an process*/
int Open(const char *, int, mode_t);
int Close(int);
ssize_t Write(int, const void *, size_t);
ssize_t Read(int, void *, size_t);
int Socketpair(int, int, int, int [2]);				/*in: domain specifies where to make socketpair, type specifies type of socket, socket_vector for file descriptors)*/
int Fseek(FILE *, long, int);
long Ftell(FILE *);
int Unlink(const char *);
#endif
