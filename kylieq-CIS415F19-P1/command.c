#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

#include "command.h"

void listDir() { /*for the ls command*/
	DIR *dir = opendir(".");
	struct dirent *dirEntry;

	if (dir == NULL) {
		printf("Error: Directory not valid\n");
	}

	while ((dirEntry = readdir(dir)) != NULL) {
		printf("%s\n", dirEntry->d_name);
	}

	closedir(dir);
}

void showCurrentDir() {/*for the pwd command*/
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	}
	else {
		printf("Error: Directory not valid\n");
	}
}

void makeDir(char *dirName) { /*for the mkdir command*/
	struct stat st = {0};
	if (stat(dirName, &st) == -1) {
		mkdir(dirName, 0700);
	}
}

void changeDir(char *dirName) { /*for the cd command*/
	chdir(dirName);
}

void copyFile(char *sourcePath, char *destinationPath) { /*for the cp command*/
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

void moveFile(char *sourcePath, char *destinationPath) { /*for the mv command*/
	FILE *fpSrc = fopen(sourcePath, "r");
	if (fpSrc == NULL) {
		printf("Error: Source file not found: %s\n", sourcePath);		
	}
	else {
		FILE *fpDst = fopen(destinationPath, "w");

		char *buffer = NULL;
		size_t bufsize = 0;
		ssize_t num_char;

		while ((num_char = getline(&buffer, &bufsize, fpSrc)) != -1) {
			fprintf(fpDst, "%s", buffer);
		}

		free(buffer);
		deleteFile(sourcePath);
		fclose(fpDst);
	}
}

void deleteFile(char *filename) { /*for the rm command*/
    int check = remove(filename);
    if (check != 0) {
    	printf("Error: File not found: %s\n", filename);
    }
}

void displayFile(char *filename) { /*for the cat command*/
//	char *token = strtok(filename, " ");
	char newFn[strlen(filename)-1];
	int i;
	for (i=0; i<strlen(filename); i++) {
		newFn[i] = filename[i];
	}
	newFn[i] = '\0';
	memmove(newFn, newFn, strlen(newFn));

	//TEST
	for (int j=0; j<strlen(newFn); j++) {
		printf("CHECK: %c\n", newFn[j]);
	}
	//END TEST

	FILE  *fp = fopen(newFn, "r");

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
	}

	fclose(fp);
}