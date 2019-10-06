#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

int main() { /*for the cat command*/
	char *filename = "input.txt";
	char newFn[strlen(filename)-1];
	int i;
	for (i=0; i<strlen(filename)-1; i++) {
		newFn[i] = filename[i];
	}
	newFn[i] = '\0';

	FILE *fp = fopen(newFn, "r");

	if (fp == NULL) {
		printf("Error: File not found: %s\n", filename);
	}
	else {
		char *buffer;
		size_t bufsize = 100;
		size_t num_char;

		while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
			printf("%s", buffer);			
		}
		fclose(fp);
	}

	return 0;
}
