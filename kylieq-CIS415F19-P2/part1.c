#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int PCBS_pos;

struct ProcessControlBlock {
	pid_t pid;
	char *cmd;
	char **args;
	int count;
};

/* Read file */
int get_line(char *filename, char *buffer, size_t bufferSize) {

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

/* Split line read from file into individual commands */
int parseCommand(char **arr, size_t arrSize, struct ProcessControlBlock **PCBS) {

    const char *s = " ";

    /* The purpose of args is to store the arguments corrresponding to the 
       command that was given. This will be sent to makeCall_File along with
       the string containing the actual function call (e.g. mkdir). */ 
    char **args;

    for (int i=0; i<arrSize; i++) {

        if (arr[i] == NULL) {
            continue;
        }

        else {
        	/* Process Control Block made for each command */
        	struct ProcessControlBlock *pcb;

            char *line = arr[i];
            char *token = strtok(line, s);

            /* Save the first token in the variable command, because it will be
               used to indicate which UNIX system call is being referenced. */
            char *command = token;

            /* Allocate memory for the arguments. */
            size_t argSize = 5;
            args = (char**)malloc(argSize * sizeof(char*));

            /* Initialize values of args to NULL in case there are not enough 
               arguments given to occupy all of the allocated memory. */
            for (int i=0; i<argSize; i++) {
                args[i] = NULL;
            }

            /* Remove white space from the arguments of the call and then assign 
            the pointer 'args' */
            int idx = 0;
            while (token != NULL) {
                token = strtok(NULL, s);
              	args[idx++] = token;
            }

            /* Get rid of './' characters from command string */
            char *split_command = strtok(command, "/");
			command = strtok(NULL, "");
       	
       		int pcbSize = idx + 1;
        	pcb = malloc(pcbSize * sizeof(struct ProcessControlBlock));
        	pcb->cmd = command;
        	pcb->args = args;
        	pcb->count = idx;

        	/* Assign new PCB to PCBS & increment PCBS position */
        	PCBS[PCBS_pos] = pcb;
        	PCBS_pos++;
        }
    }
    return 1;
}

int makeCall(struct ProcessControlBlock **PCBS) {
	for (int i=0; i<PCBS_pos; i++) {
		printf("cmd%d: %s\n", i, PCBS[i]->cmd);
		for (int j=0; j<PCBS[i]->count; j++) {
			printf("arg%d: %s\n", j, PCBS[i]->args[j]);
		}
/*		int status;
		pid_t pid = fork();
		PCBS[i]->pid = pid;

		if (pid < 0) {
			printf("Unable to fork process.\n");
			status = -1;
			exit(1);
		}
		else if (pid == 0) {
			if (PCBS[i]->count > 1) {
				printf("Child process %d started.\n", PCBS[i]->pid);
				execvp(PCBS[i]->cmd, PCBS[i]->args);
				exit(-1);
			}
			else {
				printf("Child process %d started.\n", PCBS[i]->pid);
				execvp(PCBS[i]->cmd, NULL);
				exit(-1);
			}
		}
		else {
			wait(NULL);
			//if (waitpid(pid, &status, 0) != pid) {
			//	status = -1;
			//}
		}
		printf("Done\n");
*/	}

	return 1;
}

int freePCB(struct ProcessControlBlock **PCBS) {
	for (int i=0; i<PCBS_pos; i++) {
		free(PCBS[i]->args);
		free(PCBS[i]);
	}
	free(PCBS);
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
    printf("buffer: %s\n", buffer);

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
	int pcbsSize = line_ctr;
	struct ProcessControlBlock **PCBS = malloc(line_ctr * sizeof(struct ProcessControlBlock*));

    /* Send the command and its arguments (held in ptr) to parseCommand_File */
    parseCommand(ptr, ptrSize, PCBS);

    /* Make calls */
// 	makeCall(PCBS);

 	freePCB(PCBS);
    free(ptr);
    free(buffer);
    return 0;
}
