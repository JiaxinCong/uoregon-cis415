#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("File Not Found\n");
    }
    char *buffer;
    size_t bufsize = 100;
    size_t num_char; 

    while ((num_char = getline(&buffer, &bufsize, fp)) != -1) {
        printf("%s", buffer);
    }
    fclose(fp);
}
