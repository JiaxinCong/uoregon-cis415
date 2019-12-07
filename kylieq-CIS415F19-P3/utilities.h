#ifndef UTILITIES_H
#define UTILITIES_H

struct FileLines {
	char *FileName;
	char **Lines;
	int LineCount;
};

struct LineArguments {
	int count;
	char **args;
};

int CompareFileLines(struct FileLines *f0, struct FileLines *f1); /* Not used in 1,2,3 */

struct FileLines *MakeEmptyLines(char *name,int length); /* Not used in 1,2,3 */

struct FileLines *LoadAFile(char *filename);

void FreeFile(struct FileLines *file);

#endif
