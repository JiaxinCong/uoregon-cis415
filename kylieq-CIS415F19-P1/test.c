#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {

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
		fprintf(stderr, "Error: Command unknown\n");
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
				fprintf(stderr, "Error: Command unknown\n");
				exit(-1);
			}
		}
	}
 
	/*Free the allocated memory*/
	free(buffer);
	return 1;
}
