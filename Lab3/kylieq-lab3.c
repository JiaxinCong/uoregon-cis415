/*
* Description: <write a brief description of your lab>
*
* Author: <your name>
*
* Date: <today's date>
*
* Notes: 
* 1. <add notes we should consider when grading>
*/

/*-------------------------Preprocessor Directives---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "command.h"
/*---------------------------------------------------------------------------*/

/*----------------------------Function Definitions---------------------------*/
void lfcat()
{
	/* Define your variables here */
	
	/* Open the file output.txt for writing */
	FILE *output = fopen("output.txt", "w");
	
	/* Get the current directory*/
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		printf("Error: Directory not found.\n");
		exit(1);
	}

	/* Open the dir using opendir() */
	DIR *dir = opendir(".");
	struct dirent *dirEntry = readdir(dir);

	/* use a while loop to read the dir */
	while (dirEntry != NULL) {
	
		/* Hint: use an if statement to skip any names that are not readable files (e.g. ".", "..", "lab-3.c", "lab3.exe", "output.txt" */
		if (strcmp(dirEntry->d_name, ".") == 0) {
			printf("File is not readable: %s\n", dirEntry->d_name);
			break;
		}
		else if (strcmp(dirEntry->d_name, "lab3.exe") == 0) {
			printf("File is not readable: %s\n", dirEntry->d_name);
			break;
		}
		else if (strcmp(dirEntry->d_name, "output.txt") == 0) {
			printf("File is not readable: %s\n", dirEntry->d_name);
			break;
		}
		else {
			/* Open the file */
			FILE *input = fopen(dirEntry->d_name, "r");
			
			/* Read in each line using getline() */
			char *buffer;
			size_t bufferSize = 0;
			size_t inputSize;

			while ((inputSize = getline(&buffer, &bufferSize, input)) != -1) {
				/* Write each line to output.txt */
				fprintf(output, "%s", buffer);
			}
			
			/* print 80 "-" characters to output.txt */
			for (int i=0; i<80; i++) {
				fprintf(output, "-");
			}
			
			/* close the read file and frre/null assign your line buffer */
			fclose(input);
			free(buffer);
		}
	
	}
	/*close both the output file and the directory you were reading from using closedir() and fclose() */
	closedir(dir);
	fclose(output);
}
/*---------------------------------------------------------------------------*/

/*-----------------------------Program Main----------------------------------*/
int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	
	/* Main Function Variables */
	FILE *fp;
	fp = fopen(argv[1], "r");

	char *buffer;
	size_t bufferSize = 100;
	size_t inputSize;

	const char s[2]= " \n";
	char *token;
	
	char exitStr[4];
	strcpy(exitStr, "exit");

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufferSize * sizeof(char));
	if (buffer== NULL) {
		printf("Error: Unable to allocate input buffer.\n");
		exit(1);
	}

	/*main run loop*/
	while(1) {
		/* Print >>> then get the input string */
		printf(">>> %s\n", buffer);
		inputSize = getline(&buffer, &bufferSize, fp);

		token = strtok(buffer, s);
		while (token != NULL) {
			/* If the user entered <exit> then exit the loop */
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}

			if (strcmp(token, "lfcat\n") == 0) {
				lfcat();
			}
			else {
				printf("Error: Unrecognized command.\n");
				break;
			}
			token = strtok(NULL, s);
		}

		/* If the user entered <exit> then exit the loop */
		if (strcmp(exitStr, buffer) == 0) {
			break;
		}
	}

	/*Free the allocated memory*/
	fclose(fp);
	free(buffer);
	return 1;
}