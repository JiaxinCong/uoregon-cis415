#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int checkCommand(char *token) {
	// If command requires 0 args, return 1
	// If command requires 1 arg, return 2
	// If commmand requires 2 args, return 3
	// If command not valid, return 0

    if (strcmp(token, "ls") == 0 || strcmp(token, "ls") == 13) { // 0 args
    	return 1;
   	}
    else if (strcmp(token, "pwd") == 0 || strcmp(token, "pwd") == 13) { // 0 args
    	return 1;
    }
    else if (strcmp(token, "mkdir") == 0 || strcmp(token, "mkdir") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cd") == 0 || strcmp(token, "cd") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cp") == 0 || strcmp(token, "cp") == 13) { // 2 args
    	return 3;
    }
    else if (strcmp(token, "mv") == 0 || strcmp(token, "mv") == 13) { // 2 args
    	return 3;
    }
    else if (strcmp(token, "rm") == 0 || strcmp(token, "rm") == 13) { // 1 arg
    	return 2;
    }
    else if (strcmp(token, "cat") == 0 || strcmp(token, "cat") == 13) { // 1 arg
    	return 2;
    }
    else {
        return 0; 
    }
}

int main() {
	int mode = -1;
	char **arr; 
	arr[0] = "pwd";
	arr[1] = ";"; 
	arr[2] = "mkdir";
	arr[3] = "test";
	arr[4] = ";";
	arr[5] = "cd";
	arr[6] = "test";

	int i = 0;
	char **ptr = NULL;
	while(i < sizeof(arr)) {
		int ctr2 = 0;
		ptr = (char**)malloc(10*sizeof(char*));

		while(strcmp(arr[i], ";") != 0) {// && arr[i] != NULL) {
			printf("arr val: %s bool: %d\n", arr[i], strcmp(arr[i], ";") != 0);
			ptr[ctr2] = arr[i];
			ctr2++;
			i++;
		}

		int ctr = 0;
		/* Get total count of valid entries */
		for (int i=0; i<sizeof(ptr); i++) {
			if (ptr[i] != NULL) {
				ctr++;
			}
		}

		/* checkCommand returns how many strings should be in the line depending 
	       on the command that is called. If this value does not equal ctr, the 
	       call is invalid */
		int check = checkCommand(ptr[0]);
		if (check != ctr) {
			printf("Error: Command not valid: ");
			for (int i=0; i<ctr; i++){
				printf("%s ", ptr[i]);
			}
			printf("\n");
		}
		else{
			char *command = ptr[0];
			if (strcmp(command, "ls") == 0 || strcmp(command, "ls") == 13) {
				if (mode == -1) { printf(">>> %s\n", command); }
//				listDir();
			}
			else if (strcmp(command, "pwd") == 0 || strcmp(command, "pwd") == 13) {
				if (mode == -1) { printf(">>> %s\n", command); }
//				showCurrentDir();
			}
			else if (strcmp(command, "mkdir") == 0 || strcmp(command, "mkdir") == 13) {
				char *newDir = ptr[1];
				if (mode == -1) { printf(">>> %s %s\n", command, newDir); }
//				makeDir(newDir);
			}
			else if (strcmp(command, "cd") == 0 || strcmp(command, "cd") == 13) {
				char *newDir = ptr[1];
				if (mode == -1) { printf(">>> %s %s\n", command, newDir); }
//				changeDir(newDir);
			}
			else if (strcmp(command, "cp") == 0 || strcmp(command, "cp") == 13) {
				printf("MADE IT\n");

				char *fileSrc = ptr[1];
				char *fileDst = ptr[2];

				char src[strlen(fileSrc)];
				char dst[strlen(fileDst)];
				int i;
				for (i=0; i<strlen(fileSrc)-4; i++) {
					src[i] = fileSrc[i];
				}
				int j;
				for (j=0; j<strlen(fileDst)-4; j++) {
					dst[j] = fileDst[j];
				}
				src[i++] = '.';
				src[i++] = 't';
				src[i++] = 'x';
				src[i++] = 't';
				src[i++] = '\0';
	
				dst[j++] = '.';
				dst[j++] = 't';
				dst[j++] = 'x';
				dst[j++] = 't';
				dst[j++] = '\0';

				if (mode == -1) { printf(">>> %s %s %s\n", command, fileSrc, fileDst); }
				copyFile(src, dst);
			}
			else if (strcmp(command, "mv") == 0 || strcmp(command, "mv") == 13) {
				char *fpSrc = ptr[1];
				char *fpDst = ptr[2];
				if (mode == -1) { printf(">>> %s %s %s\n", command, fpSrc, fpDst); }
//				moveFile(fpSrc, fpDst);
			}
			else if (strcmp(command, "rm") == 0 || strcmp(command, "rm") == 13) {
				char *filename = ptr[1];
				if (mode == -1) { printf(">>> %s %s\n", command, filename); }
//				deleteFile(filename);
			}
			else if (strcmp(command, "cat") == 0 || strcmp(command, "cat") == 13) {
				char *filename = ptr[1];
				if (mode == -1) { printf(">>> %s %s\n", command, filename); }
//				displayFile(filename);
			}
		}	
	}

		return 1;
}
