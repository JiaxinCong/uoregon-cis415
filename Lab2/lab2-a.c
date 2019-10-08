/*
* Description: User input is required before the program may proceed. After
* the user enters a string of text, said string is broken up into a series of 
* tokens using white space as the delimiter. These tokens are then displayed
* line by line.
*
* Author: Kylie Quan
*
* Date: 10/07/2019
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int args, char *argv[])  {

	/* Main Function Variables */
	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[2]= " ";
	char *token;

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufsize * sizeof(char));

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

	/*Free the allocated memory*/
	free(buffer);
	return 1;
}
/*-----------------------------Program End-----------------------------------*/
