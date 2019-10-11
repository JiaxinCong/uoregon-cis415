#include <stdio.h>
#include <dirent.h>

#include "command.h"

void listDir() { /*for the ls command*/
	// Pointer to directory entry
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

//void showCurrentDir(); /*for the pwd command*/

//void makeDir(char *dirName); /*for the mkdir command*/

//void changeDir(); /*for the cd command*/

//void copyFile(char *sourcePath, char *destinationPath); /*for the cp command*/

//void moveFile(char *sourcePath, char *destinationPath); /*for the mv command*/

//void deleteFile(char *filename); /*for the rm command*/

//void displayFile(char *filename); /*for the cat command*/
