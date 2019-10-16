#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(char** arr) {
pwd ; mkdir test ; cd test

	char *arr1 = "pwd";
        char **arr = &arr1;
	
	int ctr = 0;
	/* Get total count of valid entries */
	//for (int i=0; i<sizeof(arr); i++) {
	//	if (arr[i] != NULL) {
	//		ctr++;
	//	}
	//}

	int i = 0;
	do {
		char *check = arr[i];
		if (check == NULL) {
			exit(1);
		}
		ctr++;
		i++;
	} while (i<sizeof(arr));

	/* checkCommand returns how many strings should be in the line depending 
	   on the command that is called. If this value does not equal ctr, the 
	   call is invalid */
	//int check = checkCommand(arr[0]);
	int check = 1;
	if (check != ctr) {
		printf("Error: Command not valid: ");
		for (int i=0; i<ctr; i++){
			printf("%s ", arr[i]);
		}
		printf("\n");
	}
	else{
		char *command = arr[0];
		if (strcmp(command, "ls") == 0 || strcmp(command, "ls") == 13) {
			printf(">>> %s\n", command);
		//	listDir();
		}
		else if (strcmp(command, "pwd") == 0 || strcmp(command, "pwd") == 13) {
			printf(">>> %s\n", command);
		//	showCurrentDir();
		}
		else if (strcmp(command, "mkdir") == 0 || strcmp(command, "mkdir") == 13) {
			char *newDir = arr[1];
			printf(">>> %s %s\n", command, newDir);
		//	makeDir(newDir);
		}
		else if (strcmp(command, "cd") == 0 || strcmp(command, "cd") == 13) {
			char *newDir = arr[1];
			printf(">>> %s %s\n", command, newDir);
		//	changeDir(newDir);
		}
		else if (strcmp(command, "cp") == 0 || strcmp(command, "cp") == 13) {
			char *fileSrc = arr[1];
			char *fileDst = arr[2];
			printf(">>> %s %s %s\n", command, fileSrc, fileDst);
		//	copyFile(fileSrc, fileDst);
		}
		else if (strcmp(command, "mv") == 0 || strcmp(command, "mv") == 13) {
			char *fpSrc = arr[1];
			char *fpDst = arr[2];
			printf(">>> %s %s %s\n", command, fpSrc, fpDst);
		//	moveFile(fpSrc, fpDst);
		}
		else if (strcmp(command, "rm") == 0 || strcmp(command, "rm") == 13) {
			char *filename = arr[1];
			printf(">>> %s %s\n", command, filename);
		//	deleteFile(filename);
		}
		else if (strcmp(command, "cat") == 0 || strcmp(command, "cat") == 13) {
			char *filename = arr[1];
			printf(">>> %s %s\n", command, filename);
		//	displayFile(filename);
		}
	}

	return 1;
}
