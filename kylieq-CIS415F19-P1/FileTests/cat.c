#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File Not Found\n");
	exit(1);
    }
    char *buffer = NULL;
    size_t bufsize = 100;
//    size_t num_char = 0; 

    while (getline(&buffer, &bufsize, fp) != -1) {
        printf("%s", buffer);
    }
    fclose(fp);
    free(buffer);
}
