#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
/*    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File Not Found\n");
    }
    char *buffer = NULL;
    size_t bufsize = 100;

    while (getline(&buffer, &bufsize, fp) != -1) {
        printf("%s", buffer);
    }
    fclose(fp);
    free(buffer);
}*/

    int fd, sz;
    char *c = (char *)calloc(300, sizeof(char));
    fd = open("input.txt", O_RDONLY);
    if (fd < 0) { perror("error\n"); exit(1); }
    sz = read(fd, c, 300);
    c[sz] = '\0';
    printf("%s\n", c);
    free(c);
}
