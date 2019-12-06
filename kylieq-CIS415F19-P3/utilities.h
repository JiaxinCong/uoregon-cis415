#ifndef UTILITIES_H
#define UTILITIES_H

struct FileLines {
	char *FileName;
	char **Lines;
	int LineCount;
};

int GetLineCount(char *filename);

int CompareFileLines(struct FileLines *f0, struct FileLines *f1);

struct FileLines *MakeEmptyLines(char *name,int length);

struct FileLines *LoadAFile(char *filename);

void FreeFile(struct FileLines *file);

#endif
