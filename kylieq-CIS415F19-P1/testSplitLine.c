#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int splitLine(char** arr) {
	int ctr = 0;
	/* Get total count of valid entries */
	
	//for (int i=0; i<sizeof(arr); i++) {
	//	char *check = arr[i];
	//	if (arr[i] != NULL) {
	//	ctr++;
	//}
	int i=0;
	do {
		char *check = arr[i];
		if (check == NULL) {
			//break;
			exit(1);
		}
		ctr++;
		i++;
	} while (i<sizeof(arr));

	/* checkCommand returns how many strings should be in the line depending 
	   on the command that is called. If this value does not equal ctr, the 
	   call is invalid */
	int check = checkCommand(arr[0]);
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

int splitFile(char** arr) {
	int i = 0;
	char** ptr = NULL;
	while (i < sizeof(arr)) {
		int ctr = 0;
		ptr = (char**)malloc(10*sizeof(char*));
		while ((strcmp(arr[i], ";") != 0) && (strcmp(arr[i], "NULL") != 0)) {
			ptr[ctr] = arr[i];
			ctr++;
			i++;
		}

		splitLine(ptr);

		if (strcmp(arr[i], "NULL") == 0) {
			break;
		}

		i++;
	}

	return 1;
}

int main() {
	char file_name[] = "input.txt";
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Error: File not found: %s\n", file_name);
		exit(1);
	}

	char *buffer = NULL;
	size_t bufsize = NULL;
	size_t num_char = 0;

	const char s[3]= " \n";
	char *token;

	char **ptr;
	while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
		int ctr = 0;
		ptr = (char**)malloc(20*sizeof(char*));

//		printf("\n%s\n", buffer);

		token = strtok(buffer, s);
		ptr[0] = token;
		ctr = 1;

	        while (token != NULL) {
        	   	token = strtok(NULL, s);
          		ptr[ctr++] = token;
        	}

        	ptr[ctr-1] = "NULL";
        	splitFile(ptr);
	}

	/*Free the allocated memory*/
	free(ptr);
	fclose(fp);
	return 1;
}
