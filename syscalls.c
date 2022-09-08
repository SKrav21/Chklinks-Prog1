/*
 *hashTab Supporting Functions
 * Program 2 assignment
 * CSE109 Fall 2021
 * student ID: swk324
 * student Last name: Kravitz
 * student First name: Steven
 * github ID: 78743146
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "syscalls.h"
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

//Wrapper function for malloc that will throw an error in the case that the output of the call to malloc is null
void *Malloc(size_t bytes) {
	void *pointer = malloc(bytes);
	if(pointer == NULL) {
		fprintf(stderr, "malloc error(%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pointer;
}

//wrapper for fread that throws an erorr if the output of the fread is equal to 0, if there is an end-of-file indicator, or if there is an error indicator not equal to 0
size_t Fread(void *ptr, size_t size, size_t numbuff, FILE *stream) {
	size_t elements = fread(ptr, size, numbuff, stream);
	if(elements == 0 && !feof(stream) && ferror(stream)) {
		fprintf(stderr, "fread error(%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return elements;
}

//wrapper for fwrite that throws an error if the output of the fwrite is equal to 0
size_t Fwrite(const void *ptr, size_t size, size_t numbuff, FILE *stream) {
	size_t elements = fwrite(ptr, size, numbuff, stream);
	if(elements == 0) {
		if(ferror(stream)) {
			fprintf(stderr, "fwrite error(%d): %s\n", errno, strerror(errno));
			exit(errno);
		}
	}
	return elements;
}

//wrapper for fopen that will throw an error if the file is not able to be opened, otherwise the space is freed
FILE *Fopen(const char *filename, const char *mode) {
	FILE *file = fopen(filename, mode);
	if(file == NULL) {
		fprintf(stderr, "fopen error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return file;
}

//wrappper for fclose that throws an error if the fclose function is unsuccessful in closing the file
void Fclose(FILE *stream) {
	if (stream && fclose(stream)) {
		fprintf(stderr, "fclose error(%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
}

//wrapper for pipe to check if it returns an error
int Pipe(int filedes[2]) {
	int p;
	if((p = pipe(filedes)) == -1) {
		fprintf(stderr, "pipe error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return 0;
}


//wrapper for fork to check if it returns an error
pid_t Fork(void) {
	pid_t pid;
	if((pid = fork()) == -1) {
		fprintf(stderr, "fork error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pid;
}

//wrapper for wait that checks for errors
pid_t Wait(int *wstatus) {
	pid_t pid;
	if((pid = wait(wstatus)) == -1) {
		fprintf(stderr, "wait error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return pid;
}

//wrapper for open
int Open(const char *path, int oflag, mode_t mode) {
	int fd;
	if((fd = open(path, oflag, mode)) == -1) {
		fprintf(stderr, "Open error on path %s with flags %d and mode %d - %s", path, oflag, mode, strerror(errno));
		exit(errno);
	}
	return fd;
}

//wrapper for close
int Close(int pfd) {
	if(close(pfd) == -1) {
		fprintf(stderr, "Close error on descriptor %d - %s\n", errno, strerror(errno));
		exit(errno);
	}
	return 0;
}

//wrapper for write
ssize_t Write(int pfd, const void *buffer, size_t nbytes) {
	ssize_t numBytes;
	if((numBytes = write(pfd, buffer, nbytes)) == -1) {
		fprintf(stderr, "Write error %d -%s", errno, strerror(errno));
		exit(errno);
	}
	return numBytes;
}

ssize_t Read(int pfd, void *buffer, size_t nbytes) {
	ssize_t numBytes;
	if((numBytes = read(pfd, buffer, nbytes)) == -1) {
		fprintf(stderr, "Read error %d - %s\n", errno, strerror(errno));
		exit(errno);
	}
	return numBytes;
}

//wrapper functon for socketpair that checks for errors
int Socketpair(int domain, int type, int protocol, int socket_vector[2]) {
	int returnVal;
	if((returnVal = socketpair(domain, type, protocol, socket_vector)) == -1) {
		fprintf(stderr, "socketpair error (%d): %s\n", errno, strerror(errno));
		exit(errno);
	}
	return returnVal;
}

//wrapper for fseek
int Fseek(FILE *fp, long offset, int whence) {
	if(fseek(fp, offset, whence) == -1) {
		fprintf(stderr, "Unable to seek in file descriptor %d using offset %ld with whence %d - %s", fileno(fp), offset, whence, strerror(errno));
		exit(errno);
	}
	return 0;
}

//wrapper for ftell
long Ftell(FILE *fp) {
	long offset;
	if((offset = ftell(fp)) == -1) {
		fprintf(stderr, "Unable to tell position in file descriptor %d - %s\n", fileno(fp), strerror(errno));
		exit(errno);
	}
	return offset;
}

//wrapper for unlink
int Unlink(const char *pathname) {
	int rc = 0;
	if((rc = unlink(pathname)) == -1) {
		fprintf(stderr, "Unlink error %s\n", strerror(errno));
		exit(errno);
	}
	return rc;
}
