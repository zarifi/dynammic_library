/* 
Author: Mohammad Hossein Zarifi
ID:213320437

EECS 3221, Assignment 3

It accepts one null terminated string as representing a file name as argument.
This program implements the function 'my_cnt'. In this implementation my_cnt 
counts the number of newlines in the file provided by reading page_size chunks
from the file.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* handl_error is a function for handaling error in system calls*/
#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
	
	
	int my_cnt(char *filename)
{
	
    
    int i = 0;		//Index of the buffer return by read()
    int count = 0;  // Line counter (result)
    int fd;			// it stores file descriptor of the provided file
    long page;		// stores the size of the page in current system
    char c;  		// To store a character read from file
    
    /* open the file with filename provided by user*/
    fd = open(filename,O_RDONLY);
    if (fd == -1)
    	handle_error("open");
    
    /* Find the page_size in the system and store it in 'page'*/
    page = sysconf(_SC_PAGESIZE); 
    
    /* allocate a buffer with size = page_size*/
    char *buffer = (char*) malloc(sizeof(char)*page);
    
    /* error checking for malloc*/
    if (buffer == NULL){
    	fprintf(stderr, "failed to allocate memory.\n");
    	return -1;
    }
    
    /* read from the file(in page_size chunks) to the buffer until end of the file*/ 
    while(read(fd,buffer,sizeof(page)) > 0)
    {
    	/* check from the buffer until null terminated character to count
    	new_lines*/
    	while (buffer[i] != '\0')
    	{
    		c = buffer[i];
	       	if (c == '\n') // Increment count if this character is newline
	       		count = count + 1;
	       	i++;
	    }
		i = 0;	// reset the index buffer to be used for next chunk 
    }
    
    // close the file and check for error
    if(close(fd) < 0){
    	fprintf(stderr,"Failed to close the file: %s\n",strerror(errno));
    	exit(1);
    }
    
    return count;
    
}

