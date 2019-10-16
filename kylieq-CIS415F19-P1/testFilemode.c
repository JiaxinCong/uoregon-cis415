#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char file_name[] = "input.txt";
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error: File not found: %s\n", file_name);
		exit(1);
	}

	char *buffer = NULL;
	size_t bufsize = NULL;
	size_t num_char = 0;

	const char *s = " \n";
	char *token;

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

//		printf("\n%s\n", buffer);

		token = strtok(buffer, s);
		ptr[0] = token;
		ctr = 1;

	        while (token != NULL) {
        	   	token = strtok(NULL, s);
          		ptr[ctr++] = token;
        	}

        	ptr[ctr-1] = "NULL";
//        	splitFile(ptr);
	}

	/*Free the allocated memory*/
	free(ptr);
	fclose(fp);
	return 1;
}
