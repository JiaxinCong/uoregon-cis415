#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int splitFile(char** arr) {
	int i = 0;
	char** ptr;
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

	free(ptr);
	return 1;
}
