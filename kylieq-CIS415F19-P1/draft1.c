#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkCommand(char *token) {

    if (strcmp(token, "ls") == 0 || strcmp(token, "ls") == 13) {
    	return 1;
   	}
    else if (strcmp(token, "pwd") == 0 || strcmp(token, "pwd") == 13) {
    	return 1;
    }
    else if (strcmp(token, "mkdir") == 0 || strcmp(token, "mkdir") == 13) {
    	return 1;
    }
    else if (strcmp(token, "cd") == 0 || strcmp(token, "cd") == 13) {
    	return 1;
    }
    else if (strcmp(token, "cp") == 0 || strcmp(token, "cp") == 13) {
    	return 1;
    }
    else if (strcmp(token, "mv") == 0 || strcmp(token, "mv") == 13) {
    	return 1;
    }
    else if (strcmp(token, "rm") == 0 || strcmp(token, "rm") == 13) {
    	return 1;
    }
    else if (strcmp(token, "cat") == 0 || strcmp(token, "cat") == 13) {
    	return 1;
    }
    else {
        return 0; // Command not valid.
    }
}

int printArr(char* arr[]) {
	int ctr = 0;
	while (ctr < 100) {
		while (strcmp(arr[ctr], ";") != 0) {
			printf("%s ", arr[ctr]);
			ctr++;
		}
		printf("\n");
		ctr++;
	}
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

	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		char *arr[100];
		int idx = 0;

		printf("%s\n", buffer);
		token = strtok(buffer, s);

		arr[idx] = token;
		idx = 1;

        while (token != NULL) {
        	checkCommand(token);
           	token = strtok(NULL, s);
           	arr[idx++] = token;
        }
        printArr(arr);
	}

	/*Free the allocated memory*/
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
	printf(">>>");
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
