#ifndef GLOBAL_DEFS
#define GLOBAL_DEFS
#include <stdint.h>

struct ftpfile {
	const char *filename;
	FILE *stream;
};
typedef struct ftpfile ftpFile_t;

#endif
