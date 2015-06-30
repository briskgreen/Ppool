all:libppool.a libppool.so

libppool.a:ppool.o ppool_queue.o ppool_errno.o
	mkdir -p include/ppool lib
	cp ppool.h ppool_queue.h ppool_errno.h include/ppool
	ar rcs libppool.a ppool.o ppool_queue.o ppool_errno.o
	cp libppool.a lib/

libppool.so:ppool.o ppool_queue.o ppool_errno.o
	gcc -O2 -shared -fPIC -o libppool.so ppool.o ppool_queue.o ppool_errno.o -lpthread
	cp libppool.so lib/

ppool.o:ppool.c ppool.h ppool_queue.h
	gcc -O2 -c ppool.c

ppool_queue.o:ppool_queue.c ppool_queue.h ppool_errno.h
	gcc -O2 -c ppool_queue.c

ppool_errno.o:ppool_errno.c ppool_errno.h
	gcc -O2 -c ppool_errno.c

clean:
	rm -rfv lib include *.o *.a *.so

install:
	cp -r include/ppool /usr/include
	cp lib/libppool.a lib/libppool.so /usr/lib/ 

uninstall:
	rm -rfv /usr/include/ppool /usr/lib/libppool.a /usr/lib/libppool.so
