#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "command.h"

void listDir() { /*for the ls command*/
	DIR *dir = opendir(".");
	struct dirent *dirEntry;

	if (dir == NULL) {
		printf("Error: Directory not valid\n");
	}

	while ((dirEntry = readdir(dir)) != NULL) {
		printf("%s ", dirEntry->d_name);
	}
	printf("\n");

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
		mkdir(dirName, 1000);
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
	int check = rename(sourcePath, destinationPath);
	if (check == -1) {
		printf("Error! File not found.\n");
	}
}

void deleteFile(char *filename) { /*for the rm command*/
    int check = unlink(filename);
    if (check == 0) {
		printf("File deleted successfully\n");
    }
    else {
    	printf("Error: File not found: %s\n", filename);
    }
}

void displayFile(char *filename) { /*for the cat command*/
	char *buffer = (char *)calloc(300, sizeof(char));
	int file = open(filename, O_RDONLY);
	
	if (file == -1) {
		printf("Error! File not found.\n");
	}
	else {
		read(file, buffer, 300);
		printf("%s\n", buffer);
	}

	close(file);
	free(buffer);
}
