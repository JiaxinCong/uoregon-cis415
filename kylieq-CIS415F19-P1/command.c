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
		printf("Directory Not Valid\n");
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
		printf("Directory Not Valid\n");
	}
}

void makeDir(char *dirName) { /*for the mkdir command*/
	struct stat st = {0};
	if (stat(dirName, &st) == -1) {
		mkdir(dirName, 0700);
	}
}

void changeDir(char *dirName) { /*for the cd command*/
	char dir[100];
	chdir(dirName);
	printf("%s\n", getcwd(dir, 100));
}

void copyFile(char *sourcePath, char *destinationPath) { /*for the cp command*/
	FILE *fpSrc = fopen(sourcePath, "r");
	if (fpSrc == NULL) {
		printf("File Not Found\n");
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
		printf("File Not Found: %s\n", sourcePath);		
	}
	else {
		FILE *fpDst = fopen(destinationPath, "w");

		char *buffer;
		size_t bufsize = 0;
		ssize_t num_char;

		while ((num_char = getline(&buffer, &bufsize, fpSrc)) != -1) {
			fprintf(fpDst, "%s", buffer);
		}

		deleteFile(sourcePath);
		fclose(fpDst);
	}
}

void deleteFile(char *filename) { /*for the rm command*/
    int check = remove(filename);
    if (check != 0) {
    	printf("File Not Found: %s\n", filename);
    }
}

void displayFile(char *filename) { /*for the cat command*/
	FILE  *fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File Not Found: %s\n", filename);
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