#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	const char s[3]= " ;\n";
	char *token;
	
	char exitStr[100];
	strcpy(exitStr, "exit");

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufsize * sizeof(char));
	
	/*main run loop*/
	while(1) {
		/* Print >>> then get the input string */
		num_char = getline(&buffer, &bufsize, fp);
		printf(">>> %s\n", buffer);

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

/* Interactive Mode */
int intermode(char file_name[]) {
	
	return 1;
}

int main(int argc, char *argv[]) {

	/* Main function variables */
	char *buffer;
	size_t bufsize = 300;
	size_t num_char;

	const char s[2] = " \n";
	char *token;

	char check1[] = "-f";
	char check2[] = "-command";

	/* Allocate memory for the input buffer */
	buffer = (char *)malloc(bufsize * sizeof(char));

	/* print >>> then get the input string */
	printf(">>>");
	num_char = getline(&buffer, &bufsize, stdin);

	/* Tokenize the input string */
	token = strtok(buffer, s);

	int ctr = 0;
	while (token != NULL) {
		token = strtok(NULL, s);
		ctr++;
		if (ctr == 1) {
			if (strcmp(token, check1) == 0) {
				token = strtok(NULL, s);
				filemode(token);
				break;
			}
			else if (strcmp(token, check2) == 0) {
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
