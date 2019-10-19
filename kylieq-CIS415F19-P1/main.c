#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "command.h"

/*--------------------------Start of File Mode Functions--------------------------*/
int checkCommand_File(char *token) {
    // If command requires 0 args, return 1
    // If command requires 1 arg, return 2
    // If commmand requires 2 args, return 3
    // If command not valid, return 0

    if (strcmp(token, "ls") == 0) { // 0 args
        return 1;
    }
    else if (strcmp(token, "pwd") == 0) { // 0 args
        return 1;
    }
    else if (strcmp(token, "mkdir") == 0) { // 1 arg
        return 2;
    }
    else if (strcmp(token, "cd") == 0) { // 1 arg
        return 2;
    }
    else if (strcmp(token, "cp") == 0) { // 2 args
        return 3;
    }
    else if (strcmp(token, "mv") == 0) { // 2 args
        return 3;
    }
    else if (strcmp(token, "rm") == 0) { // 1 arg
        return 2;
    }
    else if (strcmp(token, "cat") == 0) { // 1 arg
        return 2;
    }
    else {
        return 0; 
    }
}

int print_File(char *command, char **arr, size_t arrSize) {

    if (strcmp(command, "ls") == 0) {
        printf(">>> %s\n", command); 
        listDir();
    }
    else if (strcmp(command, "pwd") == 0) {
        printf(">>> %s\n", command); 
        showCurrentDir();
    }
    else if (strcmp(command, "mkdir") == 0) {
        char *newDir = arr[0];
        printf(">>> %s %s\n", command, newDir); 
        makeDir(newDir);
    }
    else if (strcmp(command, "cd") == 0) {
        char *newDir = arr[0];
        printf(">>> %s %s\n", command, newDir); 
        changeDir(newDir);
    }
    else if (strcmp(command, "cp") == 0) {
        char *fileSrc = arr[0];
        char *fileDst = arr[1];
        printf(">>> %s %s %s\n", command, fileSrc, fileDst); 
        copyFile(fileSrc, fileDst);
    }
    else if (strcmp(command, "mv") == 0) {
        char *fileSrc = arr[0];
        char *fileDst = arr[1];
        printf(">>> %s %s %s\n", command, fileSrc, fileDst); 
        moveFile(fileSrc, fileDst);
    }
    else if (strcmp(command, "rm") == 0) {
        char *filename = arr[0];
        printf(">>> %s %s\n", command, filename); 
        deleteFile(filename);
    }
    else if (strcmp(command, "cat") == 0) {
        char *filename = arr[0];
        printf(">>> %s %s\n", command, filename); 
        displayFile(filename);
    }
    return 1;
}

int parseCommand_File(char **arr, size_t arrSize) {

    const char *s = " ";
    char **args;

    for (int i=0; i<arrSize; i++) {

        if (arr[i] == NULL) {
            continue;
        }

        else {
            int ctr = 0;
            char *line = arr[i];
            char *token = strtok(line, s);
            char *command = token;

            int check = checkCommand_File(command);

            size_t argSize = 2;
            args = (char**)malloc(argSize * sizeof(char*));

            for (int i=0; i<argSize; i++) {
                args[i] = NULL;
            }

            int idx = 0;
            while (token != NULL) {
                token = strtok(NULL, s);
                args[idx] = token;
                ctr++;
                idx++;
            }
            
            if (ctr == check) {
                print_File(command, args, argSize);

            }
        }
    }
    return 1;
}

int getline_File(char *filename, char *buffer, size_t bufferSize){

    int file = open(filename, O_RDONLY);
    if (file == -1) {
        printf("Error: unable to open file '%s'\n", filename);
        return -1;
    }

    if (read(file, buffer, bufferSize) == -1) {
        printf("Error: unable to read file '%s'\n", filename);
        return -1;
    }

    close(file);

    return 1;
}

/* File Mode */
int filemode(char filename[]) {
    char *buffer = NULL;
    size_t bufferSize = 300;
    ssize_t inputSize = 0;

    buffer = (char *)malloc(bufferSize * sizeof(char));
    inputSize = getline_File(filename, buffer, bufferSize);

    char *token;

    size_t ptrSize = 300;
    char **ptr = (char **)malloc(ptrSize*sizeof(char*));
    for (int i=0; i<ptrSize; i++) {
        ptr[i] = NULL;
    }

    token = strtok(buffer, ";\n");
    ptr[0] = token;
    int i = 1;

    while (token != NULL) {
        token = strtok(NULL, ";\n");
        ptr[i] = token;
        i++;
    }   

    printf("\n");
    parseCommand_File(ptr, ptrSize);

    free(ptr);
    free(buffer);
    return 0;
}
/*---------------------------End of File Mode Functions---------------------------*/

/*-----------------------Start of Interactive Mode Functions----------------------*/
int checkCommand_Interactive(char *token) { /* for interactive mode */
	// If command requires 0 args, return 1
	// If command requires 1 arg, return 2
	// If commmand requires 2 args, return 3
	// If command not valid, return 0

    if (strcmp(token, "ls") == 0 || strcmp(token, "ls") == 13) { // 0 args
    	return 1;
   	}
    else if (strcmp(token, "pwd") == 0 || strcmp(token, "pwd") == 13) { // 0 args
    	return 1;
    }
    else if (strcmp(token, "mkdir") == 0 || strcmp(token, "mkdir") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cd") == 0 || strcmp(token, "cd") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cp") == 0 || strcmp(token, "cp") == 13) { // 2 args
    	return 3;
    }
    else if (strcmp(token, "mv") == 0 || strcmp(token, "mv") == 13) { // 2 args
    	return 3;
    }
    else if (strcmp(token, "rm") == 0 || strcmp(token, "rm") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cat") == 0 || strcmp(token, "cat") == 13) { // 1 arg
    	return 2;
    }
    else {
        return 0; 
    }
}

int makeCall_Interactive(char** arr, int mode) { /* for interactive mode */
	int ctr = 0;
	/* Get total count of valid entries */
	for (int i=0; i<sizeof(arr); i++) {
		if (arr[i] != NULL) {
			ctr++;
		}
	}

	/* checkCommand returns how many strings should be in the line depending 
	   on the command that is called. If this value does not equal ctr, the 
	   call is invalid */
	char *command = arr[0];
	int check = checkCommand_Interactive(command);

	/* If command is not recoginzed */
	if (ctr == 1 && check == 0) {
		if (mode == -1) { printf(">>> %s\n", command); }
		printf("command: %s check: %d ctr: %d\n", command, check, ctr);
		printf("Error! Unrecognized command: %s\n", command);
	}
	else if (check != ctr) {
		if (mode == -1) { printf(">>> %s\n", command); }
		printf("Error! Unsupported parameters found for command: %s\n", command);
	}
	else {
		if (strcmp(command, "ls") == 0 || strcmp(command, "ls") == 13) {
			if (mode == -1) { printf(">>> %s\n", command); }
			listDir();
		}
		else if (strcmp(command, "pwd") == 0 || strcmp(command, "pwd") == 13) {
			if (mode == -1) { printf(">>> %s\n", command); }
			showCurrentDir();
		}
		else if (strcmp(command, "pwd\n") == 0 || strcmp(command, "pwd\n") == 13) {
			if (mode == -1) { printf(">>> %s\n", command); }
			showCurrentDir();
		}
		else if (strcmp(command, "mkdir") == 0 || strcmp(command, "mkdir") == 13) {
			char *newDir = arr[1];
			if (mode == -1) { printf(">>> %s %s\n", command, newDir); }
			makeDir(newDir);
		}
		else if (strcmp(command, "cd") == 0 || strcmp(command, "cd") == 13) {
			char *newDir = arr[1];
			if (mode == -1) { printf(">>> %s %s\n", command, newDir); }
			changeDir(newDir);
		}
		else if (strcmp(command, "cp") == 0 || strcmp(command, "cp") == 13) {
			char *fileSrc = arr[1];
			char *fileDst = arr[2];
			if (mode == -1) { printf(">>> %s %s %s\n", command, fileSrc, fileDst); }
			copyFile(fileSrc, fileDst);
		}
		else if (strcmp(command, "mv") == 0 || strcmp(command, "mv") == 13) {
			char *fpSrc = arr[1];
			char *fpDst = arr[2];
			if (mode == -1) { printf(">>> %s %s %s\n", command, fpSrc, fpDst); }
			moveFile(fpSrc, fpDst);
		}
		else if (strcmp(command, "rm") == 0 || strcmp(command, "rm") == 13) {
			char *filename = arr[1];
			if (mode == -1) { printf(">>> %s %s\n", command, filename); }
			deleteFile(filename);
		}
		else if (strcmp(command, "cat") == 0 || strcmp(command, "cat") == 13) {
			char *filename = arr[1];
			if (mode == -1) { printf(">>> %s %s\n", command, filename); }
			displayFile(filename);
		}
	}

	return 1;
}

int splitTokens_Interactive(char** arr, int mode) { /* for interactive mode */
	int i = 0;
	char** ptr = NULL;
	while (i < sizeof(arr)) {
		int ctr = 0;
		ptr = (char**)malloc(10*sizeof(char*));

		while ((strcmp(arr[i], ";") != 0) && (strcmp(arr[i], "NULL") != 0)) {
			ptr[ctr] = arr[i];
			ctr++;
			i++;
		}

		makeCall_Interactive(ptr, mode);

		if (strcmp(arr[i], "NULL") == 0) {
			break;
		}

		i++;
		free(ptr);
	}
	free(ptr);
	return 1;
}

/* Interactive Mode */
int intermode() {
	/* Main Function Variables */
	char *buffer = NULL;
	size_t bufsize = 100;

	const char *s = " \n";
	char *token = NULL;

	char *exitStr = "exit";

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL) {
		printf("Error: Unable to allocate input buffer.\n");
		exit(1);
	}
	
	char **ptr = NULL;
	while(1) {
		int ctr = 0;
		ptr = (char**)malloc(20 * sizeof(char*));

		/* Print >>> then get the input string */
		printf(">>> ");
		getline(&buffer, &bufsize, stdin);

		/* Tokenize the input string */
		token = strtok(buffer, s);
		ptr[0] = token;
		ctr = 1;

		while (token != NULL) {
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}

           	token = strtok(NULL, s);
          	ptr[ctr++] = token;
		}

		ptr[ctr-1] = "NULL";

		/* Check if user entered anything on the command line at all */
		if (strcmp(ptr[0], "NULL") != 0) {
        	splitTokens_Interactive(ptr, -2);
        }

		if (token != NULL) {
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}
		}
		free(ptr);
	}
	free(buffer);
	return 1;
}
/*------------------------End of Interactive Mode Functions-----------------------*/

int main(int argc, char *argv[]) {

	char check2[] = "-command";
	char check3[] = "-f";

	char *command = NULL;
	char *file = NULL;

	/* Check command */
	if (argc == 2) {
		if (strcmp(argv[1], check2) == 0) {
			command = argv[1];
			intermode();
		}
		else{
			printf("Error! Command unknown.\n");
			exit(0);
		}
	}
	else if (argc == 3) {
		if (strcmp(argv[1], check3) == 0) {
			command = argv[1];
			file = argv[2];
			filemode(file);
		}
		else{
			printf("Error! Command unknown.\n");
			exit(0);
		}
	}
	else {
		printf("Error! Command unknown.\n");
		exit(0);
	}

	return 1;
}
