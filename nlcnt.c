/*
Author: Mohammad Hossein Zarifi
ID:213320437

This program make use of shared libraries(mapping.so or reading.so) to
count the number of new_lines in the file provided by the user.
In this program there is a call 'dlopen' to open the required shared 
library(if user writes 'reading' as first argument this program use
shared library reading.so and if user writes 'mapping' as first argument 
this program uses mapping.so library.)

The second program is the filename of the file that user wants to count its
number of new_lines.

*/

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include "my_cnt.h"

int main(int argc, char *argv[])
{
	
	int result; // stores the number of new_lines of the file 
	int (*my_cnt)(char *);// pointer to the function my_cnt in the shared library
	void *handle; // handler for dynamic library
	char *error; // store the error returned from dlerror
	
	/* if user does not provide two arguments (three including the name of 
	the program) program should reutrns an error. */
	if(argc != 3)
	{
		fprintf(stderr, "there should be two argumments");
		exit(EXIT_FAILURE);
	}
	
	/* If the second argument is 'reading' or any leading substring 
	load the shared library 'reading.so' */ 
	if(strncmp(argv[1],"reading",strlen("reading")) == 0)
	{
		// loading the reading.so by performing lazy binding and check for error
		handle = dlopen("./reading.so",RTLD_LAZY);
		if (!handle) 
		{
			fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		dlerror();    /* Clear any existing error */
		
		/* obtain address of the symbol(my_cnt) in shared object*/ 
		*(void **) (&my_cnt) = dlsym(handle, "my_cnt");
		
		/* check for any error returned by 'dlsym'*/
	    error = dlerror();
	    if (error != NULL) {
	    	fprintf(stderr, "%s\n", error);
	    	exit(EXIT_FAILURE);
	    }
	    
	    /* store number of new_lines in the file in result by calling my_cnt
	    in shared object reading.so*/
	    result = my_cnt(argv[2]);
	    printf("Number of new line in the file provided is: %d\n",result);
	    
	    dlerror();    /* Clear any existing error */  
	    // close the handle and check for error
	    if(dlclose(handle) != 0){
	    	fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
	    }  	
	    exit(EXIT_SUCCESS);
	    
	}
	
	/* If the second argument is 'mapping' or any leading substring 
	load the shared library 'mapping.so' */ 
	if(strncmp(argv[1],"mapping",strlen("mapping")) == 0)
	{
		// loading the mapping.so by performing lazy binding and check for error
		handle = dlopen("./mapping.so",RTLD_LAZY);
		if (!handle) 
		{
			fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		
		dlerror();    /* Clear any existing error */
		
		/* obtain address of the symbol(my_cnt) in shared object*/ 
		*(void **) (&my_cnt) = dlsym(handle, "my_cnt");
		
		
		/* check for any error returned by 'dlsym'*/
	    error = dlerror();
	    if (error != NULL) {
	    	fprintf(stderr, "%s\n", error);
	    	exit(EXIT_FAILURE);
	    }
	    
	    /*store the number of new_lines in file in result by calling my_cnt in 
	    shared object mapping.so*/
	    result = my_cnt(argv[2]); 
	    
	    printf("Number of new line in the file provided is: %d\n",result);
	    
	    dlerror();    /* Clear any existing error */  
	    // close the handle and check for error
	    if(dlclose(handle) != 0){
	    	fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
	    }  	
	    
	    exit(EXIT_SUCCESS);
	    
	}
	
	return 0;
	
}
