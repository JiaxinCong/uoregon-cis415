/*
* Description: Project 1 file that is referenced from the main file in order to
* implement a number of UNIX system commands.
*
* Author: Kylie Quan
*
* Date: 10/20/2019
*/

/*-----------------------------Preprocessor Directives----------------------------*/
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
/*--------------------------------------------------------------------------------*/

void listDir() { /*for the ls command*/
	DIR *dir = opendir(".");
	struct dirent *dirEntry;

	if (dir == NULL) {
		char *error = "Error! Directory not valid.\n";
		write(1, error, strlen(error));
	}

	while ((dirEntry = readdir(dir)) != NULL) {
		write(1, dirEntry->d_name, strlen(dirEntry->d_name));
		write(1, " ", 1);
	}
	write(1, "\n", 1);

	closedir(dir);
}

void showCurrentDir() {/*for the pwd command*/

	char *output = "output.txt";
	int file = open(output, O_WRONLY | O_APPEND);

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		write(file, cwd, strlen(cwd));
		write(file, "\n", 1);
	}
	else {
		char *error = "Error! Directory not valid.\n";
		write(file, error, strlen(error));
	}

	close(file);
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

	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	
	/* check signals whether to change directory back */
	int check;

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

		check = 0;
	}
	else {
		int i;
		for (i=0; i<strlen(sourcePath); i++) {
			newSrc[i] = sourcePath[i];
		}
		newSrc[i] = '\0';
		check = 1;
	}

	FILE *fpSrc = fopen(newSrc, "r");
	if (fpSrc == NULL) {
		char *error = "Error! Source file not found.\n";
		write(1, error, strlen(error));
	}
	else if (strcmp(destinationPath, ".") == 0) {
		char *error = "Error! Destination file not valid.\n";
		write(1, error, strlen(error));
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

	if (check == 0) {
		chdir(cwd);
	}
}

void moveFile(char *sourcePath, char *destinationPath) { /*for the mv command*/
	int check = rename(sourcePath, destinationPath);
	if (check == -1) {
		char *error = "Error! File not found.\n";
		write(1, error, strlen(error));
	}
}

void deleteFile(char *filename) { /*for the rm command*/
    int check = unlink(filename);
    if (check == 0) {
    	char *message = "File deleted successfully.\n";
    	write(1, message, strlen(message));
    }
    else {
    	char *error = "Error! File not found.\n";
    	write(1, error, strlen(error));
    }
}

void displayFile(char *filename) { /*for the cat command*/
	char *buffer = (char *)calloc(300, sizeof(char));
	int file = open(filename, O_RDONLY);

	if (file == -1) {
		char *error = "Error! File not found.\n";
		write(1, error, strlen(error));
	}
	else {
		read(file, buffer, 300);
		write(1, buffer, 300);
	}

	free(buffer);
}
