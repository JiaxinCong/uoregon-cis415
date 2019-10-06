#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) { /*for the mkdir command*/
	char *dirName = argv[1];
	struct stat st = {0};
	if (stat(dirName, &st) == -1) {
		mkdir(dirName, 1000);
	}
}

