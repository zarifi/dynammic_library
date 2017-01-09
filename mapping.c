/*
Author: Mohammad Hossein Zarifi
ID:213320437
EECS 3221, Assignment 3

It accepts one null terminated string as representing a file name as argument.
This program implements the function 'my_cnt'. In this implementation my_cnt 
counts the number of newlines in the file provided by mmapping the file to
memory and operating on resulting array.

*/

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* handl_error is a function for handaling error in system calls*/
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

int my_cnt(char *filename)
{
	
	int i = 0;      // Index of the buffer return by mmap
	int count = 0;  // Line counter (result)
	char *addr;		// The buffer returned by mmap
    int fd;			// it stores file descriptor of the provided file
    struct stat sb;		// stores stat structure of the file provided by the user
    char c;  		// To store a character read from the file
    
    /* open the file with filename provided by user*/
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    	handle_error("open");
    
    /* To obtain file size */
    if (fstat(fd, &sb) == -1) 
        handle_error("fstat");
    
    /* mmaping the file into memory */
    addr = mmap(NULL, sb.st_size, PROT_READ,MAP_SHARED, fd,0);
    if (addr == MAP_FAILED)
        handle_error("mmap");
    
    // check all characters in buffer(with size = sb.st_size) and counts the number of new_lines
    while (i <= sb.st_size)
    {
    	c = addr[i];
    	if (c == '\n') // Increment count if this character is newline
    		count = count + 1;
    	i++; // go to the next character in the buffer
    }
    printf("chars are %d\n",i);
    
    // close the file and check for error
    if(close(fd) < 0){
    	fprintf(stderr,"Failed to close the file: %s\n",strerror(errno));
    	exit(1);
    }
    
    return count;
}



