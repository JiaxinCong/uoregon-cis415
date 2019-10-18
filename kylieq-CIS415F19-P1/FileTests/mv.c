#include <stdio.h>
#include <string.h>

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
		ssize_t num_char;

		while ((num_char = getline(&buffer, &bufsize, fpSrc)) != -1) {
			fprintf(fpDst, "%s", buffer);
		}

		//free(buffer);
		remove(sourcePath);
		fclose(fpDst);
	}
}

