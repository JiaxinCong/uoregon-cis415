#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

	char *sourcePath = argv[1];
	char *destinationPath = argv[2];

	char newSrc[strlen(sourcePath)-1];

	// First check if working directory needs to be changed.
	// Get rid of unneccesary white-space characters at end of string.
	if (sourcePath[0] == '.' && sourcePath[1] == '.') {
		changeDir("..");
		int i;
		for (i=0; i<strlen(sourcePath); i++) {
			newSrc[i] = sourcePath[i];
		}
		newSrc[i] = '\0';
		memmove(newSrc, newSrc+3, strlen(newSrc));
	}
	else {
		int i;
		for (i=0; i<strlen(sourcePath); i++) {
			newSrc[i] = sourcePath[i];
		}
		newSrc[i] = '\0';
	}

	FILE *fpSrc = fopen(newSrc, "r");
	if (fpSrc == NULL) {
		printf("Error: Source file not found: %s\n", newSrc);
	}
	else if (strcmp(destinationPath, ".") == 0) {
		printf("Error: Destination file name not valid.\n");
	}
	else {
		FILE *fpDst = fopen(destinationPath, "w");
		char input;

		while ((input = fgetc(fpSrc)) != EOF) {
			fputc(input, fpDst);
		}
		fclose(fpSrc);
		fclose(fpDst);
	}
}
