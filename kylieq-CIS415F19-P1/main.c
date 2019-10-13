#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command.h"

int checkCommand(char *token) {
	// If command requires 0 args, return 1
	// If command requires 1 arg, return 2
	// If commmand requires 2 args, return 3
	// If not valid command, return 0

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

int splitLine(char** arr) {
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
	int check = checkCommand(arr[0]);
	if (check != ctr) {
		printf("Command not valid: ");
		for (int i=0; i<ctr; i++){
			printf("%s ", arr[i]);
		}
		printf("\n");
	}
	else{
		char *command = arr[0];
		if (strcmp(command, "ls") == 0 || strcmp(command, "ls") == 13) {
			printf(">>> %s\n", command);
			listDir();
		}
		else if (strcmp(command, "pwd") == 0 || strcmp(command, "pwd") == 13) {
			printf(">>> %s\n", command);
			showCurrentDir();
		}
		else if (strcmp(command, "mkdir") == 0 || strcmp(command, "mkdir") == 13) {
			char *newDir = arr[1];
			printf(">>> %s %s\n", command, newDir);
			makeDir(newDir);
		}
		else if (strcmp(command, "cd") == 0 || strcmp(command, "cd") == 13) {
			char *newDir = arr[1];
			printf(">>> %s %s\n", command, newDir);
			changeDir(newDir);
		}
		else if (strcmp(command, "cp") == 0 || strcmp(command, "cp") == 13) {
/*			printf(">>> %s\n", command);
			char *fileSrc = arr[1];
			char *fileDst = arr[2];

			while (1) {
				if (isalpha(fileSrc[0]) || isdigit(fileSrc[0])) {
					continue;
				}
				if (isalpha(fileSrc[0]) || isdigit(fileSrc[0])) {
					continue;
				}
				else {
					printf("One Or Both Files Are Invalid\n");
					break;
				}
				copyFile(fileSrc, fileDst);
			}
*/		}
		else if (strcmp(command, "mv") == 0 || strcmp(command, "mv") == 13) {
			char *fpSrc = arr[1];
			char *fpDst = arr[2];
			printf(">>> %s %s %s\n", command, fpSrc, fpDst);
			moveFile(fpSrc, fpDst);
		}
		else if (strcmp(command, "rm") == 0 || strcmp(command, "rm") == 13) {
			printf(">>> %s\n", command);
			char *filename = arr[1];
			deleteFile(filename);
		}
		else if (strcmp(command, "cat") == 0 || strcmp(command, "cat") == 13) {
			char *filename = arr[1];
			printf(">>> %s %s\n", command, filename);
			displayFile(filename);
		}
	}

	return 1;
}

int splitFile(char** arr) {
	int i = 0;
	char** ptr;
	while (i < sizeof(arr)) {
		int ctr = 0;
		ptr = (char**)malloc(10*sizeof(char*));
		while ((strcmp(arr[i], ";") != 0) && (strcmp(arr[i], "NULL") != 0)) {
			ptr[ctr] = arr[i];
			ctr++;
			i++;
		}

		splitLine(ptr);

		if (strcmp(arr[i], "NULL") == 0) {
			break;
		}

		i++;
	}

	free(ptr);
	return 1;
}

/* File Mode */
int filemode(char file_name[]) {
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		perror("File Not Found");
		exit(1);
	}

	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[3]= " \n";
	char *token;
	
	char exitStr[100];
	strcpy(exitStr, "exit");

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

		printf("%s\n", buffer);

		token = strtok(buffer, s);
		ptr[0] = token;
		ctr = 1;

        while (token != NULL) {
        	checkCommand(token);
           	token = strtok(NULL, s);
          	ptr[ctr++] = token;
        }
        ptr[ctr-1] = "NULL";
        splitFile(ptr);
	}

	/*Free the allocated memory*/
	free(ptr);
	fclose(fp);
	return 1;
}

/* Interactive Mode */
int intermode(char file_name[]) {
	/* Main Function Variables */
	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[2]= " \n";
	char *token;

	char exitStr[] = "exit";

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufsize * sizeof(char));

	while(1) {
		/* Print >>> then get the input string */
		printf(">>> ");
		num_char = getline(&buffer, &bufsize, stdin);

		/* Tokenize the input string */
		token = strtok(buffer, s);

		/* Display each token */
		int ctr = 0;
		while (token != NULL) {
			printf("T%d: %s\n", ctr, token);
			token = strtok(NULL, s);
			ctr++;
		}
		/* If the user entered <exit> then exit the loop */
		printf(">>> ");
		num_char = getline(&buffer, &bufsize, stdin);
		token = strtok(buffer, s);

        /* Check user input */
		if (strcmp(exitStr, buffer) == 0) {
			break;
		}
		/* REMOVE OPTION TO PRINT TOKENS */
		else {
			/* Display each token */
			int ctr = 0;
			while (token != NULL) {
				printf("T%d: %s\n", ctr, token);
				token = strtok(NULL, s);
				ctr++;
			}
		}
	}

	/*Free the allocated memory*/
	free(buffer);
	return 1;
}

int main(int argc, char *argv[]) {

	/* Main function variables */
	char *buffer;
	size_t bufsize = 300;
	size_t num_char;

	const char s[2] = " \n";
	char *token;

	char check1[] = "./pseudu-shell";
	char check2[] = "-f";
	char check3[] = "-command";

	/* Allocate memory for the input buffer */
	buffer = (char *)malloc(bufsize * sizeof(char));

	/* print >>> then get the input string */
	printf(">>> ");
	num_char = getline(&buffer, &bufsize, stdin);

	/* Tokenize the input string */
	token = strtok(buffer, s);
	if (strcmp(token, check1) != 0) {
		fprintf(stderr, "Command Unknown\n");
		exit(-1);
	}

	int ctr = 0;
	while (token != NULL) {
		token = strtok(NULL, s);
		ctr++;
		if (ctr == 1) {
			if (strcmp(token, check2) == 0) {
				token = strtok(NULL, s);
				filemode(token);
				break;
			}
			else if (strcmp(token, check3) == 0) {
				token = strtok(NULL, s);
				intermode(token);
				break;
			}
			else {
				fprintf(stderr, "Command Unknown\n");
				exit(-1);
			}
		}
	}
 
	/*Free the allocated memory*/
	free(buffer);
	return 1;
}
