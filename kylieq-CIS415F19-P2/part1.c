#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "command.h"

int makeCall(struct ProcessControlBlock **PCBS) {
    for (int i=0; i<PCBS_pos; i++) {

        PCBS[i]->pid = fork();

        if (PCBS[i]->pid < 0) {
            printf("Unable to fork process.\n");
            exit(1);
        }
        if (PCBS[i]->pid == 0) { /* child */
            /* Launch workload programs */
            printf("Process: %d - Joined\n", getpid());
            execvp(PCBS[i]->cmd, PCBS[i]->args);
            exit(-1);
        }
    }
    for (int i=0; i<PCBS_pos; i++) {
        wait(NULL);
        printf("Process %d - Ended\n", PCBS[i]->pid);
    }

    return 1;
}

int main(int argc, char *argv[]) {

	char *filename = argv[1];

	char *buffer = NULL;
    size_t bufferSize = 300;
    ssize_t inputSize = 0;

    /* Allocate memory for the input buffer. */
    buffer = (char *)malloc(bufferSize * sizeof(char));

    /* Read text file given by the user. */
    inputSize = get_line(filename, buffer, bufferSize);

    /* Place '\0' at the end of the string held in the input buffer 
       to signify the end of the string. */
    if (inputSize > 0) {
   		buffer[strlen(buffer)] = '\0';
    }
    else {
    	buffer[0] = '\0';
    }

    char *token;

    size_t ptrSize = 300;
    char **ptr = (char **)malloc(ptrSize * sizeof(char*));
 
    /* Initialize values of the ptr to NULL */
    for (int i=0; i<ptrSize; i++) {
        ptr[i] = NULL;
    }  

    /* Tokenize the input string with the delimiters ';', newline character '\n'
       and carriage return '\r', and place each token in ptr. This collection of
       tokens represents a single command and its arguments. */
    token = strtok(buffer, "\n\r");
    ptr[0] = token;
    int line_ctr = 1;

    while (token != NULL) {
        token = strtok(NULL, "\n\r");
        ptr[line_ctr] = token;
        line_ctr++;
    }   

    /* Collection of PCB's */
    PCBS_pos = 0;
	struct ProcessControlBlock **PCBS = malloc(line_ctr * sizeof(struct ProcessControlBlock*));

    /* Send the command and its arguments (held in ptr) to parseCommand_File */
    parseCommand(ptr, line_ctr, PCBS);

    /* Make calls */
 	makeCall(PCBS);

 	freePCB(PCBS);
    free(ptr);
    free(buffer);
    return 0;
}
