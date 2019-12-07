#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

struct FileLines *LoadAFile(char *filename) {
    FILE *file = fopen(filename,"r");
    struct FileLines *lines = NULL;
    char buffer[300];
    int counter = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        counter += 1;   
    }

    fseek(file, 0, SEEK_SET);

    lines = (struct FileLines*)malloc(sizeof(struct FileLines));
    lines->FileName = strdup(filename);
    lines->LineCount = counter;
    lines->Lines = (char **)malloc((lines->LineCount+1) * sizeof(char *));
    lines->Lines[lines->LineCount] = NULL;

    for(int i=0; i<lines->LineCount; i++) {
        fgets(buffer, sizeof(buffer), file);
        int len = strlen(buffer);
        for (int j=0; j<len; j++) {
            char c = buffer[j];
            if (c == '\n' || c == '\r') {
                buffer[j] = 0;
            }
        }
        lines->Lines[i] = strdup(buffer);
    }

    fclose(file);
    return lines;
}

struct FileLines *MakeEmptyLines(char *name, int length) {
    struct FileLines *lines = (struct FileLines*)malloc(sizeof(struct FileLines));
    lines->FileName = strdup(name);
    lines->LineCount = length;
    lines->Lines = (char **) malloc(sizeof(char *)*(lines->LineCount+1));
    for(int i=0; i<lines->LineCount+1; i++) {
        lines->Lines[i] = NULL;
    }
    return lines;
}

int CompareFileLines(struct FileLines *f0, struct FileLines *f1) {
    if (f0->LineCount != f1->LineCount)
        return -1;
    if (strcmp(f0->FileName, f1->FileName) != 0)
        return -1;
    for (int i=0; i<f0->LineCount; i++) {
        if (f0->Lines[i] == NULL && f1->Lines[i] != NULL) {
            return -1;
        }
        if (f0->Lines[i] != NULL && f1->Lines[i] == NULL) {
            return -1;
        }
        if (f0->Lines[i] != NULL && f1->Lines[i] != NULL) {
            if (strcmp(f0->Lines[i], f1->Lines[i])!=0) {
                return -1;
            }
        }
    }
    return 0;
}

void FreeFile(struct FileLines *file) {
    free(file->FileName);             
    for (int i=0; i < file->LineCount; i++) {
        if ((file->Lines[i]) != NULL) {
            free(file->Lines[i]);
        }
    }    
    free(file->Lines); 
    free(file);         
}

