#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int splitFile(char** arr, int mode) {
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

//		splitLine(ptr, mode);

		if (strcmp(arr[i], "NULL") == 0) {
			break;
		}

		i++;
	}

	return 1;
}

int main() {
	/* Main Function Variables */
	char *buffer = NULL;
	size_t bufsize = NULL;
	size_t num_char = 0;

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
		ptr = (char**)malloc(bufsize * sizeof(char*));

		/* Print >>> then get the input string */
		printf(">>> ");
		num_char = getline(&buffer, &bufsize, stdin);

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
        //	splitFile(ptr, -2);
        }

		if (token != NULL) {
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}
		}
	}

	/*Free the allocated memory*/
	//free(buffer);
	return 1;
}
