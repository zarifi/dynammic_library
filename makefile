
all: nlcnt mapping.so reading.so

nlcnt: nlcnt.o
	gcc -Wall -o nlcnt nlcnt.c -ldl
	
mapping.o: mapping.c
	gcc -c -Wall -Werror -fpic mapping.c
	
mapping.so: mapping.o
	gcc -shared -o mapping.so mapping.o
	
reading.o: reading.c
	gcc -c -Wall -Werror -fpic reading.c
	
reading.so: reading.o
	gcc -shared -o reading.so reading.o
	
clean:
	/bin/rm -f *.so *.o nlcnt