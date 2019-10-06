#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *sourcePath = argv[1];
	char *destinationPath = argv[2];

	FILE *fpSrc = fopen(sourcePath, "r");
	if (fpSrc == NULL) {
		printf("Error: Source file not found: %s\n", sourcePath);		
	}
	else {
		FILE *fpDst = fopen(destinationPath, "w");

		char *buffer = NULL;
		size_t bufsize = 0;

		while (getline(&buffer, &bufsize, fpSrc) != -1) {
			fprintf(fpDst, "%s", buffer);
		}

		fclose(fpSrc);
		unlink(sourcePath);
		fclose(fpDst);
		free(buffer);
	}
}

