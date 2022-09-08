#include <stdio.h>       /* for fprintf, etc. */
#include <stdlib.h>      /* for exit */
#include <string.h>      /* for strerror */
#include <errno.h>       /* for errno */
#include <curl/curl.h>   /* for curl, baby! */
#include "syscalls.h"    /* for wrapped system calls */
#include "global_defs.h"
#include "chkLinks_funcs.h"
#include <unistd.h>


int main(int argc, char *argv[]) {
	int rc = 0;
	parseArgs(argc, argv);
	rc = chkLinks(argv[1], argv[2], argv[3], argv[4]);       
	return rc;
}
