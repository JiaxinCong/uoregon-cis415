#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[]) {
	char *sourcePath = argv[1];
	char *destinationPath = argv[2];
	
	FILE *fpSrc = fopen(sourcePath, "r");
	if (fpSrc == NULL) {
		printf("File Not Found: %s\n", sourcePath);
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

