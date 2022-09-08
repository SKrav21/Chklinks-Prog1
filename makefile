CFLAGS = -DDEBUG -g -c -Wall -Wextra -Wwrite-strings
CFLAGS = -g -c -Wall -Wextra -Wwrite-strings
LFLAGS = -g

default: chkLinks

clean:
	rm -f *.o
	rm -f chkLinks
	
chkLinks.o: chkLinks.c global_defs.h
	gcc ${CFLAGS} chkLinks.c
	
chkLinks_funcs.o: chkLinks_funcs.c chkLinks_funcs.h
	gcc ${CFLAGS} chkLinks_funcs.c
	
syscalls.o: syscalls.c syscalls.h
	gcc ${CFLAGS} syscalls.c
	
chkLinks: chkLinks.o chkLinks_funcs.o syscalls.o
	gcc ${LFLAGS} -lcurl -o chkLinks chkLinks.o chkLinks_funcs.o syscalls.o
