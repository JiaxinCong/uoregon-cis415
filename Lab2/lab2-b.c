/*
* Description: The function opens the file input.txt for reading only. A 
* buffer is allocated to hold the contents of said file. This new string is 
* broken up into a series of tokens using white space as the delimiter, and 
* then displayed line by line. Once the end of the file has been reached, the 
* user may either enter text to be split into tokens, or end the program.
*
* Author: Kylie Quan
*
* Date: 10/072019
*
* Notes: 
* 1. After the end of the file has been reached, user input is required before 
*    the program may proceed. Enter a line of text for the program to then break 
*    it up into a series of tokens. Otherwise, type "exit" to terminate the 
*    program.
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main() {
	setbuf(stdout, NULL);
	
	/* Main Function Variables */
	FILE *fp = fopen("input.txt", "r");

	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[2]= " \n";
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
	fclose(fp);
	free(buffer);
	return 1;
}
/*-----------------------------Program End-----------------------------------*/
