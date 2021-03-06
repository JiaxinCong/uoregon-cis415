/*
* Description: User input is required before the program may proceed. After
* the user enters a string of text, said string is broken up into a series of 
* tokens using white space as the delimiter. If the user enters "exit", the 
* program will terminate. Otherwise, if the user enters "lfcat", the program
* will read from accessible files in the current working directory. The contents 
* of each of these files are copied over into a new text file, output.txt.
*
* Author: Kylie Quan
*
* Date: 10/17/19
*
* Notes: 
* 1. When compiling the program, enter "gcc kylieq-lab3.c -o lab3". 
*    And then "./lab3" to run it. 
*    The program checks for a file named "lab3" when determining whether the
*    files are readable.
*/

/*-------------------------Preprocessor Directives---------------------------*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "command.h"
/*---------------------------------------------------------------------------*/

/*----------------------------Function Definitions---------------------------*/
void lfcat()
{
	printf("<<In lfcat(): Step-01: Function called>>\n");
	printf("<<In lfcat(): Step-02: Listing all files in current dir.>>\n");
	/* Define your variables here */
	FILE *output = NULL;
	DIR *dir = NULL;
	struct dirent *dirEntry = NULL;

	/* Open the file output.txt for writing */
	output = fopen("output.txt", "w");
	
	/* Get the current directory*/
	char cwd[300];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		printf("Error: Directory not found.\n");
		exit(1);
	}

	/* Open the dir using opendir() */
	dir = opendir(".");

	if (dir == NULL) {
		printf("Directory can not be found.\n");
		exit(1);
	}

	/* use a while loop to read the dir */
	while ((dirEntry = readdir(dir)) != NULL) {
		
		char *filename = dirEntry->d_name;

		/* Hint: use an if statement to skip any names that are not readable files (e.g. ".", "..", "lab-3.c", "lab3.exe", "output.txt" */
		if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
			printf("%s\n", filename);		
		}
		else if (strcmp(filename, "output.txt") == 0) {
			printf("%s\n", filename);
		}
		else if (strcmp(filename, "kylieq-lab3.c") == 0) {
			printf("%s\n", filename);
		}
		else if (strcmp(filename, "command.h") == 0){
			printf("%s\n", filename);
		}
		else if (strcmp(filename, ".DS_Store") == 0){
			printf("%s\n", filename);
		}
		else if (strcmp(filename, "lab3") == 0){
			printf("%s\n", filename);
		}
		else {
			printf("%s\n", filename);
			/* Open the file */
			FILE *input = fopen(filename, "r");
			
			/* Read in each line using getline() */
			char *buffer = NULL;
			size_t bufferSize = NULL;
			size_t inputSize = 0;

			fprintf(output, "File: %s\n", filename);
			while ((inputSize = getline(&buffer, &bufferSize, input)) != -1) {
				/* Write each line to output.txt */
				fprintf(output, "%s", buffer);
			}
			
			/* print 80 "-" characters to output.txt */
			fprintf(output, "\n---------------------------------------------------------------------------------------------------------------\n");
			
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
int main() {
	setbuf(stdout, NULL);

	char *buffer = NULL;
	size_t bufferSize = NULL;
	size_t inputSize = 0;

	const char *s = " \n";
	char *token = NULL;
	
	char *exitStr = "exit";

	/* Allocate memory for the input buffer. */
	buffer = (char *)malloc(bufferSize * sizeof(char));
	if (buffer == NULL) {
		printf("Error: Unable to allocate input buffer.\n");
		exit(1);
	}
	free(buffer);
	/*main run loop*/
	while(1) {
		/* Print >>> then get the input string */
		printf(">>> ");
		inputSize = getline(&buffer, &bufferSize, stdin);

		token = strtok(buffer, s);
		while (token != NULL) {
			/* If the user entered <exit> then exit the loop */
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}

			if (strcmp(token, "lfcat") == 0) {
				lfcat();
			}
			else {
				printf("Error: Unrecognized command.\n");
				break;
			}
			token = strtok(NULL, s);
		}

		/* If the user entered <exit> then exit the loop */
		if (token != NULL) {
			if (strcmp(exitStr, buffer) == 0) {
				break;
			}
		}
	}
	free(buffer);
	return 1;
}
