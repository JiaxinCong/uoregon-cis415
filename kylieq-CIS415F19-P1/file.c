#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void copyFile(char *sourcePath, char *destinationPath) { /*for the cp command*/
//	char newSrc[strlen(sourcePath)-1];
//	printf("src: %s dst: %s\n", sourcePath, destinationPath);
	// First check if working directory needs to be changed.
	// Get rid of unneccesary white-space characters at end of string.
//	if (sourcePath[0] == '.' && sourcePath[1] == '.') {
//		chdir("..");
//		int i;
//		for (i=0; i<strlen(sourcePath); i++) {
//			newSrc[i] = sourcePath[i];
//		}
//		newSrc[i] = '\0';
//		memmove(newSrc, newSrc+3, strlen(newSrc));
//	}
//	else {
//		int i;
//		for (i=0; i<strlen(sourcePath); i++) {
//			newSrc[i] = sourcePath[i];
//		}
//		newSrc[i] = '\0';
//	}

	FILE *fpSrc = fopen(sourcePath, "r");
	if (fpSrc == NULL) {
		printf("Error: Source file not found: %s\n", sourcePath);
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

int makeCall(char** arr, int mode) {
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

int printtoken(char **arr) {
	for (int i=0; i<sizeof(arr); i++) {
		if (arr[i] != NULL) {
			printf("CHECK: %s\n", arr[i]);
		}
	}
	return 0;
}

int splitTokens(char** arr, int mode) {
	int i = 0;
	char** ptr = NULL;
	while (i < sizeof(arr)) {
		int ctr = 0;
		ptr = (char**)malloc(10*sizeof(char*));

		for (int i=0; i<10; i++) {
			ptr[i] = NULL;
		}
		
		char *token = arr[i];
		
		while ((strcmp(token, ";") != 0) && (token != NULL)) {
				ptr[ctr++] = token;
				printf("check: %s\n", token);
				//ctr++;
				token = arr[i++];
				//i++;
		}

		printf("CHECK1\n");
		makeCall(ptr, mode);

		if (token == NULL) {
			break;
		}

		i++;
		free(ptr);
	}
	free(ptr);
	return 1;
}

int main() {
	char file_name[] = "input2.txt";
	FILE *fp = fopen(file_name, "r");

	if (fp == NULL) {
		printf("Error: File not found: %s\n", file_name);
		exit(1);
	}

	char *buffer = NULL;
	size_t bufsize = 100;
	size_t num_char = 0;

	const char *s = " ";
	char *token;

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

		printf("\n%s\n", buffer);

		token = strtok(buffer, s);

		ptr[0] = token;
		ctr = 1;

        while (token != NULL) {
           	token = strtok(NULL, s);
          	ptr[ctr++] = token;
        }

        while (ctr<sizeof(ptr)) {
        	ptr[ctr++] = NULL;
        }
        //ptr[ctr-1] = "NULL";
        //makeCall(ptr, -1);
        ///splitTokens(ptr, -1);
        char **send;
        int i = 0;
        while(strcmp(ptr[i], "\n") != 0) {
        	send = (char**)malloc(10*sizeof(char*));
        	int count = 0;
        	while (strcmp(ptr[i], ";") != 0) {
        		send[count] = ptr[i];
        		i++;
        		count++;
        	}
        	if (send != NULL) { 
        		printtoken(send); 
        		//free(send);
        	}
        	i++;
        	free(send);
        }

        free(ptr);
	}

	/*Free the allocated memory*/
	free(buffer);
	fclose(fp);
	return 1;
}
