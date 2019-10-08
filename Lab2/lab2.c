#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int input(char *s, int length);

int main(int args, char *argv[])  {
	char *buffer;
	size_t bufsize = 100;
	size_t num_char;

	const char s[2]= " ";
	char *token;

	buffer = (char *)malloc(bufsize * sizeof(char));
	num_char = getline(&buffer, &bufsize, stdin);

	// Get the first token.
	token = strtok(buffer, s);

	// Walk through other tokens.
	int ctr = 0;
	while (token != NULL) {
		printf("T%d: %s\n", ctr, token);
		token = strtok(NULL, s);
		ctr++;
	}

	// Deallocate memory
	free(buffer);
	return(0);

}
