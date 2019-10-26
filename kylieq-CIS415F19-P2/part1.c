#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


/* Read file */
int getline_File(char *filename, char *buffer, size_t bufferSize) {

    int file = open(filename, O_RDONLY);
    if (file == -1) {
    	char *error = "Error: Unable to open file '";
    	write(1, error, strlen(error));
    	write(1, filename, strlen(filename));
    	write(1, "'\n", 2);

        return -1;
    }

    if (read(file, buffer, bufferSize) == -1) {
    	char *error = "Error: Unable to read file '";
    	write(1, error, strlen(error));
    	write(1, filename, strlen(filename));
    	write(1, "'\n", 2);

        return -1;
    }
    close(file);
    return 1;
}

int main(int argc, char *argv[]) {

	char *filename = argv[1];

	char *buffer = NULL;
	size_t bufferSize = 100;
	ssize_t inputSize = 0;

	buffer = (char *)malloc(bufferSize * sizeof(char));

	inputSize = getline_File(filename, buffer, bufferSize);

    /* Place '\0' at the end of the string held in the input buffer 
       to signify the end of the string. */
	if (inputSize > 0) {
		buffer[bufferSize] = '\0';
	}
	else {
		buffer[0] = '\0';
	}

	char *token;

	size_t ptrSize = 100;
	char **ptr = (char **)malloc(ptrSize * sizeof(char *));

    /* Initialize values of the ptr to NULL */
	for (int i=0; i<ptrSize; i++) {
		ptr[i] = NULL;
	}

	int ctr = 0; /* keep track of how many commands there are in file */

    /* Tokenize the input string with the delimiters '/', newline character '\n'
       and carriage return '\r', and place each token in ptr. This will be a 
       collection of executable files. */
	token = strtok(buffer, "/");

	while (token != NULL) {
		token = strtok(NULL, "/\n\r");
		ptr[ctr] = token;
		ctr++;
	}

	for (int i=0; i<ctr; i++) {
		printf("token: %s\n", ptr[i]);
	}

	for (int i=0; i<ctr-1; i++) {
		pid_t pid = fork();
		if (pid == 0 && strstr(ptr[i], "exe")) {
			execvp(ptr[i], NULL);
			exit(-1);
		}
		printf("Done\n");
	}

	free(ptr);
	free(buffer);
	return 0;
}