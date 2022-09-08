/*
 * Course: CSE109
 * Assignment: Prog3
 * Purpose: To 
 * Author: Steven Kravitz
 * User ID: swk324
 */
                    
#include <stdio.h>       /* for fprintf, etc. */
#include <stdlib.h>      /* for exit */
#include <string.h>      /* for strerror */
#include <errno.h>       /* for errno */
#include <curl/curl.h>   /* for curl, baby! */
#include "syscalls.h"    /* for wrapped system calls */
#include "global_defs.h"
#include "chkLinks_funcs.h"
#include <unistd.h>



int chkLinks(char *userid, char *password, char *server, char *pathname) {
	char c;
	char junk[1000];
	char url[1000];
	ftpFile_t FTPfile = {pathname, NULL};
	int crc = ftpDownload(userid, password, server, pathname);
	if(crc) {
		fprintf(stderr, "\n%s (%d) - %s on %s\n\n", curl_easy_strerror(crc), crc, pathname, server);
	}
	else {
		FILE *fp = Fopen(pathname, "r");
		do{
			c = fgetc(fp);
			if(feof(fp)) {
				break;
			}
			if(c != '<') {
				continue;
			}
			c = fgetc(fp);
			if(c == '!') {
				char tmp1 = fgetc(fp);
				char tmp2 = fgetc(fp);
				if((tmp1 = fgetc(fp)) == '-' && (tmp2 = fgetc(fp)) == '-') {
					fscanf(fp, "%[^-]->", junk); 
				}
				else{
					Fseek(fp, -2, 1);
				}
			}
			if(c != 'a') {
				continue;
			}
			fscanf(fp, "%[^>]", url);
			if(!(strstr(url, "http"))) {
				fprintf(stderr, "No \"http[s]\" found in URL (%d) - %s\n", 202, url);
				continue;
			}
			FTPfile.filename = strchr(FTPfile.filename, 58);
			if(!FTPfile.filename || (strncmp(FTPfile.filename, "://", 3) != 0)) {
				fprintf(stderr, "No \"://\" found in URL (%d) - %s\n", 203, url);
			}
			else{
				FTPfile.filename = strchr(FTPfile.filename + 3, 47);
				if(FTPfile.filename) {
					crc = chkLinks(userid, password, server, url);
				}
				else{
					crc = chkLinks(userid, password, server, url);
					if(crc) {
						fprintf(stderr, "error with suffix (%d) - %s\n", 202, url);
					}
				}
			}	
		}while(1);
		Fclose(fp);
		Unlink(FTPfile.filename);
	}
	return crc;
}

//function to download the files
int ftpDownload(char *userid, char *password, char *server, char *pathname) {
  char str[128];
  CURLcode crc;
  CURL *cp = NULL;
  ftpFile_t FTPfile = {"downloadedFile", NULL};
  curl_global_init(CURL_GLOBAL_ALL);
  cp = curl_easy_init();                                    
  if (cp) {
    sprintf(str, "%s:%s", userid, password);
    curl_easy_setopt(cp, CURLOPT_USERPWD, str);
    sprintf(str, "sftp://%s/%s", server, pathname);
    curl_easy_setopt(cp, CURLOPT_URL, str);
    curl_easy_setopt(cp, CURLOPT_WRITEFUNCTION, ftpWrite);
    curl_easy_setopt(cp, CURLOPT_WRITEDATA, (void *)&FTPfile);
    crc = curl_easy_perform(cp);
    curl_easy_cleanup(cp);
    Fclose(FTPfile.stream);
    curl_global_cleanup();
  } else {
  	fprintf(stderr, "Initialization of curl session/transfer handle was unsuccessful\n");
    exit(202);
  }
  return (int)crc;
}

size_t ftpWrite(void *buffer, size_t size, size_t nmemb, void *stream) {
ftpFile_t *oFile = (ftpFile_t *)stream;
  if(!oFile->stream)
    oFile->stream = Fopen(oFile->filename, "w");
  return Fwrite(buffer, size, nmemb, oFile->stream);
}

void parseArgs(int argc, char *argv[]) {
	if(argc == 1 || (argc == 2 && ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)))) {
		fprintf(stdout, "\nUsage: curlFTP <userid> <password> <server> <fully-qualified filename>\n\n");
		exit(0);
	}
	else if (argc != 5) {
		fprintf(stdout, "Expecting 4 arguments to be passed\n");
		fprintf(stdout, "\nUsage: curlFTP <userid> <password> <server> <fully-qualified filename>\n\n");
		exit(0);
	}
	
}

