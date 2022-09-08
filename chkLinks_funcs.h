#ifndef CHKLINKS_FUNCS
#define CHKLINKS_FUNCS

void parseArgs(int, char *[]);
int ftpDownload(char *, char *, char *, char *);
size_t ftpWrite(void *, size_t, size_t, void *);
int chkLinks(char *, char *, char *, char *);





#endif
