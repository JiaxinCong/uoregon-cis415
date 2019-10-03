#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int len = 100;
    char *pStr = malloc(len);

    if (pStr != NULL) {
        int c;
        int i = 0;

        while ((c = getchar()) != '\n') {
            pStr[i++] = (char) c;
        }
 
    printf("%s\n", pStr);
    free(pStr);
    }

    return 0;
}
